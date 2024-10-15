#include "block.h"

#include <boost/algorithm/string/trim_all.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/streambuf.hpp>

#include <iostream>
#include <memory>
#include <optional>
#include <thread>

int port;
int bs;

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

namespace {

class Connection : public std::enable_shared_from_this<Connection> {
 public:
  explicit Connection(tcp::socket socket) : m_socket{std::move(socket)}, m_block(bs) {}

  Connection(const Connection &) = delete;
  Connection(Connection &&) = delete;

  ~Connection() {
    try {
      std::cout << std::this_thread::get_id() << " Client \"" << m_clientName
                << "\": Disconnected." << std::endl;
    } catch (...) {
      assert(false);
    }
  }

  Connection &operator=(const Connection &) = delete;
  Connection &operator=(Connection &&) = delete;

  void startReading() {
    auto self = shared_from_this();

    asio::async_read_until(
        m_socket, m_buffer, "\n",
        [this, self](const boost::system::error_code error,
                     const std::size_t length) { handleRead(error, length); });
  }

 private:
  void handleRead(const boost::system::error_code error,
                  const std::size_t length) {
    if (error) {
      std::cout << std::this_thread::get_id() << " Client \"" << m_clientName
                << "\": Reading error: \"" << error << "\"." << std::endl;
      return;
    }

    if (length != 0) {
      handleData(length);
      m_buffer.consume(length);
    }

    startReading();
  }

  void handleData(const std::size_t length) {
    const std::string_view logRecord{
        asio::buffer_cast<const char *>(m_buffer.data()), length};

    m_block.add(logRecord);
  }

  tcp::socket m_socket;
  boost::asio::streambuf m_buffer;

  std::string m_clientName;
  Block m_block;
  std::vector<std::string> block_buffer;
};

void accept(tcp::acceptor &acceptor) {
  acceptor.async_accept(
      [&acceptor](const boost::system::error_code error, tcp::socket socket) {
        if (!error) {
          const std::shared_ptr<Connection> connection{
              new Connection{std::move(socket)}};
          connection->startReading();
        }

        accept(acceptor);
      });
}

void runServer() {
  std::cout << std::this_thread::get_id() << " Running server..." << std::endl;

  asio::io_context ioContext;

  std::cout << std::this_thread::get_id() << " Listing TCP v4 port " << port
            << " for new log clients..." << std::endl;

  tcp::acceptor acceptor{ioContext, tcp::endpoint(tcp::v4(), port)};
  accept(acceptor);

  asio::signal_set signals{ioContext, SIGINT, SIGTERM};
  signals.async_wait([&](auto, auto) { ioContext.stop(); });

  std::vector<std::thread> threads;
  const auto nThreads = std::thread::hardware_concurrency();
  threads.reserve(nThreads);
  for (unsigned int i = 0; i < nThreads; ++i) {
    threads.emplace_back([&ioContext]() { ioContext.run(); });
  }
  for (auto &th : threads) {
    th.join();
  }

  std::cout << std::this_thread::get_id() << " Server stopped." << std::endl;
}

}  // namespace

int main(int argc, char* argv[])
{
  if (argc != 3) {
    std::cout<<"Usage " << argv[0] << " <port> <block size>" <<std::endl;
    return -1;
  }
  port = std::stoi(argv[1]);
  bs = std::stoi(argv[2]);
  try {
    runServer();
    return EXIT_SUCCESS;
  } catch (const std::exception &ex) {
    std::cerr << "Fatal error \"" << ex.what() << "\"." << std::endl;
  } catch (...) {
    std::cerr << "Fatal UNKNOWN error." << std::endl;
  }

  return EXIT_FAILURE;
}
