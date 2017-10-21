#include "BooleanMatrix.hpp"
BooleanMatrix::BooleanMatrix(const BooleanMatrix & new_one):Matrix(new_one){
}
BooleanMatrix::BooleanMatrix(int r, int c):Matrix(r, c){
}
    
bool BooleanMatrix::replace(matrix_element_type e, int r, int c){
   return  Matrix::replace(e, r, c);

}
    
BooleanMatrix BooleanMatrix::operator&(const BooleanMatrix & new_one){
	BooleanMatrix m1(row, columns);
	for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= columns; j++) 
               if(getElement(i, j)&&new_one.getElement(i, j)) m1.Matrix::matirx[ELEMENT_POS(i, j)] = 1;
       }
       return m1;
}
BooleanMatrix BooleanMatrix::operator|(const BooleanMatrix & new_one){
	BooleanMatrix m1(row, columns);
	for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= columns; j++) 
               if(getElement(i, j)||new_one.getElement(i, j)) m1.Matrix::matirx[ELEMENT_POS(i, j)] = 1;
       }
       return m1;
}
BooleanMatrix BooleanMatrix::BooleanProduct(const BooleanMatrix & new_one) const{
	BooleanMatrix m1(row, new_one.getColums());
	for(int i=1;i<= row;i++){
		for (int j = 1; j <= columns; j++) {
			for (int k = 1; k <= new_one.columns; k++)
				if (getElement(i, j) == 1&&new_one.getElement(j, k)==1)
					m1.replace(1, i, k);
		}
	}
	return m1;
}