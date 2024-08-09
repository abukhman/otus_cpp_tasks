#include "matrix.h"


void check () {
  Matrix<int, -1> matrix;
  assert(matrix.size() == 0); // все ячейки свободны
  auto a = matrix[0][0];
  assert(a == -1);
  assert(matrix.size() == 0);
  matrix[100][100] = 314;
  assert(matrix[100][100] == 314);
  assert(matrix.size() == 1);
  // выведется одна строка
  // 100100314
  for(auto c: matrix)
  {
    int x;
    int y;
    int v;
    std::tie(x, y, v) = c;
    std::cout << x << y << v << std::endl;
  }
}

int main() {

  check();
  Matrix<int, 0> matrix;
  for (int i=0; i<=9; i++) {
    matrix[i][i] = i;
    matrix[i][9-i] = 9 - i;
  }

  for(int i = 1; i<9; i++) {
    for(int j = 1; j<9; j++) {
      cout<<matrix[i][j]<<" ";
    }
    cout<<endl;
  }

  for(auto c: matrix)
  {
    int x, y, v;
    std::tie(x, y, v) = c;
    std::cout << "matrix[" << x << "][" << y << "]=" << v << std::endl;
  }

  cout<<"Number used cells = " << matrix.size() << endl;
  
  return 0;
}

int main2() {
  
  Matrix<int, -1> matrix;
  matrix[0][1] = 1;
  auto m1 = matrix.begin();
  auto m2 = matrix.end();
  //return 0;
  //
  int x,y,v;
  tie(x, y, v) = *m1;
  cout<<"["<<x<<","<<y<<"]="<<v<<endl;
  cout<<(m1!=m2 ? "true": "false")<<endl;
  ++m1;
  cout<<(m1==m2 ? "true": "false")<<endl;

  for(auto c: matrix)
  {
    int x, y, v;
    std::tie(x, y, v) = c;
    std::cout << x << y << v << std::endl;
  }

  return 0;
}



int main1(int, char**) {
  Matrix<int, -1> matrix;

  assert(matrix.size() == 0); // все ячейки свободны
  auto a = matrix[0][0];
  assert(a == -1);
  assert(matrix.size() == 0);
  matrix[100][100] = 314;
  assert(matrix[100][100] == 314);
  assert(matrix.size() == 1);
  

  auto c = matrix.begin();
  //for(auto c = matrix.begin(); c != matrix.end(); ++c) {
  //}
  //for(auto c: matrix) {
  //	  cout<<"1";
  //}
  return 0;
}

