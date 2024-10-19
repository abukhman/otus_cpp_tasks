#include <iostream>
#include <string>
#include <cmath>
#include <iostream>

int main(int argc, char ** argv)
{
    size_t count = 0;
    double avg = 0.0;
    double sumsq = 0.0;
    std::string line;

    while (std::getline(std::cin, line))
    {
	//std::cout << line << std::endl;
	double tmp = std::stof(line);
        avg = avg * (count) / (count + 1) + tmp / (count + 1);
        sumsq = sumsq * (count) / (count + 1) + tmp / (count + 1) * tmp;
	count++;
    }
    std::cout << sqrt(sumsq - avg*avg) << std::endl;
    return 0;
}
