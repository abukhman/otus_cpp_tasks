#include <iostream>
#include <fstream>
#include <sstream>
#include <Eigen/Dense>

using namespace Eigen;

MatrixXd loadMatrix(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    // Read the matrix from the file
    std::vector<std::vector<double>> data;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<double> row;
        double value;
        while (iss >> value) {
            row.push_back(value);
        }
        data.push_back(row);
    }
    
    // Определяем размеры матрицы
    int rows = data.size();
    int cols = data.empty() ? 0 : data[0].size();
    
    MatrixXd mat(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat(i, j) = data[i][j];
        }
    }
    file.close();
    return mat;
}

MatrixXd loadMatrixU(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    // Read the matrix from the file
    std::vector<std::vector<unsigned>> data;
    std::string line;

    while (std::getline(file, line)) {
	std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream iss(line);
        std::vector<unsigned> row;
        unsigned value;
        while (iss >> value) {
            row.push_back(value);
        }
        data.push_back(row);
    }
    
    // Определяем размеры матрицы
    int rows = data.size();
    int cols = data.empty() ? 0 : data[0].size();
    
    MatrixXd mat(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat(i, j) = data[i][j];
        }
    }
    file.close();
    return mat;
}

int main(int argc, char *argv[]) {
    // Load matrix and vector
    if (argc != 3) {
      std::cerr << "Usage: " << argv[0]
	  << "test.csv logreg_coef.txt" << std::endl;
    }
    MatrixXd coeff = loadMatrix(argv[2]);
    MatrixXd samples = loadMatrixU(argv[1]);
    std::vector<double> results;

    //MatrixXd res(rows, cols);
    for (unsigned i=0; i < samples.rows(); i++) {
      results.push_back(samples(i, 0));
      for(unsigned j=1; j < samples.cols(); j++) {
        samples(i, j) /= 256;
      }
      samples(i, 0) = 1.0;
    }

    if (coeff.cols() != samples.cols()) {
        std::cerr << "Matrix and vector dimensions do not match for multiplication!" << std::endl;
        return 1;
    }

    MatrixXd result = coeff * samples.transpose();

    unsigned eq = 0;
    for(unsigned i = 0; i < result.cols(); i++)
    {
      int argmax = 0;
      double maxval = result(0, i);
      for(unsigned j = 0; j < result.rows(); j++) {
	      if(result(j,i) > maxval) {
	        argmax = j;
		maxval = result(j,i);
	      }
      }
      if (argmax == results[i]) {
        eq++;
      }
    }
    std::cout << 1.0 * eq / results.size()  << std::endl;
    return 0;
}
