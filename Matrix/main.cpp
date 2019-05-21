#include <iostream>
#include <vector>
#include "matrix.h"

int main () {
    
    // assign a 7x5 matrix to the variable initial_grid
    // all values in the matrix are 0.4
	std::vector <std:: vector <float> > 
	    initial_grid (7, std::vector <float>(5, 0.4));

  Matrix matrixa = Matrix(initial_grid);

  matrixa.matrix_print();

  std::cout << matrixa.getRows() << std::endl;

  std::cout << matrixa.getCols() << std::endl;

  Matrix transposea = matrixa.matrix_transpose();

  transposea.matrix_print();
    
  // 7x5 2-dimensional vector with values 0.2
	std::vector <std:: vector <float> > 
	    second_grid (7, std::vector <float>(5, 0.2));
    
  Matrix matrixb = Matrix(second_grid);

  Matrix matrixsum = matrixa.matrix_addition(matrixb);

  matrixsum.matrix_print();
    
  return 0;
}