#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> split(const std::string& line, char delimiter=',')
{  
  std::vector<std::string> result;
  size_t pred_pos = 0, pos = 0;
  do {
    pos = line.find(",", pred_pos);
    size_t br_pos = line.find("\"", pred_pos);

    if (br_pos!=std::string::npos && br_pos < pos) {
      br_pos = line.find("\"", br_pos + 1);
      pos = line.find(",", br_pos);
    }
    result.push_back(line.substr(pred_pos, pos - pred_pos));
    pred_pos = pos+1;
    
  } while (pos != std::string::npos);
  return result; // Возвращаем список строк
}


int main(int argc, char ** argv)
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::cout << split(line)[9] << std::endl;
    }

    return 0;
}
