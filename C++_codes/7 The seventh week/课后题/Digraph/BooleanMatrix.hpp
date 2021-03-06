#ifndef BooleanMatrix_hpp
#define BooleanMatrix_hpp

#include <stdio.h>
#include "Matrix.hpp"

class BooleanMatrix: public Matrix {
private:
    typedef bool matrix_element_type;
public:
    BooleanMatrix(const BooleanMatrix &);
    BooleanMatrix(int r, int c);
    
    bool replace(matrix_element_type e, int r, int c);
    
    BooleanMatrix operator&(const BooleanMatrix &);
    BooleanMatrix operator|(const BooleanMatrix &);
    BooleanMatrix BooleanProduct(const BooleanMatrix &) const;
    
};

#endif /* BooleanMatrix_hpp */