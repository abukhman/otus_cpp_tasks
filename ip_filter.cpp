#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

typedef std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> ip_t;
ip_t get_ip(const std::string s)
{
    std::vector<std::string> v = split(s, '.');
    return std::make_tuple(std::stoi(v[0]), std::stoi(v[1]),
		    std::stoi(v[2]), std::stoi(v[3]));
}

void printIpPool(std::vector<ip_t>& ip_pool)
{
        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            std::cout << (unsigned) std::get<0>(*ip) << ".";
            std::cout << (unsigned) std::get<1>(*ip) << ".";
            std::cout << (unsigned) std::get<2>(*ip) << ".";
            std::cout << (unsigned) std::get<3>(*ip);
            std::cout << std::endl;
        }
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<ip_t> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(get_ip(v[0]));
        }

	std::sort(ip_pool.begin(), ip_pool.end(), [](auto x, auto y){ if (std::get<0>(x)!=std::get<0>(y)) return std::get<0>(x) > std::get<0>(y); else if (std::get<1>(x)!=std::get<1>(y)) return std::get<1>(x) > std::get<1>(y); else if (std::get<2>(x)!=std::get<2>(y)) return std::get<2>(x) > std::get<2>(y); else if (std::get<3>(x)!=std::get<3>(y)) return std::get<3>(x) > std::get<3>(y); else return false;});

	printIpPool(ip_pool);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
	decltype(ip_pool) ip;

	auto filter1 = [&ip_pool](uint8_t x) {
            std::vector<ip_t> ip;
            auto checker = [x](ip_t param) {
	        return std::get<0>(param) == x;
            };
            std::copy_if (ip_pool.begin(), ip_pool.end(),
		  std::back_inserter(ip), checker);
	    return ip;
	};
        ip = filter1(1);
	printIpPool(ip);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
	
	ip.clear();
	auto filter2 = [&ip_pool](uint8_t x, uint8_t y) {
            std::vector<ip_t> ip;
            auto checker = [x, y](ip_t param) {
	        return std::get<0>(param) == x && std::get<1>(param) == y;
            };
            std::copy_if (ip_pool.begin(), ip_pool.end(),
		  std::back_inserter(ip), checker);
	    return ip;
	};
	ip = filter2(46, 70);
	printIpPool(ip);


        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
	
	ip.clear();
	auto filter_any = [&ip_pool](uint8_t x) {
            std::vector<ip_t> ip;
            auto checker = [x](ip_t param) {
	        return std::get<0>(param) == x 
		       || std::get<1>(param) == x
		       || std::get<2>(param) == x
		       || std::get<3>(param) == x;
            };
            std::copy_if (ip_pool.begin(), ip_pool.end(),
		  std::back_inserter(ip), checker);
	    return ip;
	};
	ip = filter_any(46);
	printIpPool(ip);


        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
