#include <iostream>
#include <boost/asio/io_context.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/streambuf.hpp>
#include "Server.h"
namespace asio = boost::asio;
using asio::ip::tcp;

class EchoServer : public std::enable_shared_from_this<EchoServer> {
public:
    EchoServer(tcp::socket socket)
        : m_socket{std::move(socket)} {
    }

    void start_read() {
        auto self = shared_from_this();
        asio::async_read_until(m_socket, buffer_, '\n',
            [this, self](std::error_code ec, std::size_t length) mutable {
                if (!ec) {
                    std::string msg(asio::buffer_cast<const char*>(buffer_.data()), length);
                    std::cout << "Received: " << msg;
                    buffer_.consume(length);
                    auto tmp = S_.parse_command(msg);
                    start_write(tmp);
		    //start_read();
                }
            });
    }

    void start_write(const std::string& msg) {
        auto self = shared_from_this();
        asio::async_write(m_socket, asio::buffer(msg),
            [this, self](std::error_code ec, std::size_t lengsth) mutable {
                if (!ec) {
                    start_read();
                }
            });
    }

    tcp::socket m_socket;
    asio::streambuf buffer_;
    DBServer S_;
};

void accept(tcp::acceptor &acceptor) {
  acceptor.async_accept(
      [&acceptor](const boost::system::error_code error, tcp::socket socket) {
        if (!error) {
          const std::shared_ptr<EchoServer> connection{
              new EchoServer{std::move(socket)}};
          connection->start_read();
        }
        accept(acceptor);
      });
}
int main(int argc, char* argv[]) {
    try {
        asio::io_context io_context;
        short port = argc > 1 ? std::atoi(argv[1]) : 12345;
        //EchoServer server(io_context, port);
	tcp::acceptor acceptor{io_context, tcp::endpoint(tcp::v4(), port)};
	accept(acceptor);

        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

