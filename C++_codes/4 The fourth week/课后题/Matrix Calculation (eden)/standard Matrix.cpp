#include "Matrix.h"
#define MAX 1000;
 
Matrix::Matrix(string n, int h, int w, int**m) {
    name = n;
    width = w;
    height = h;
    param = new int*[height];
    for (int i = 0; i < height; i++) {
        param[i] = new int[width];
        for (int j = 0; j < width; j++)
            param[i][j] = m[i][j];
    }
}
 
Matrix::Matrix(const Matrix &otherMat) {
    name = otherMat.name;
    width = otherMat.width;
    height = otherMat.height;
    param = new int*[height];
    for (int i = 0; i < height; i++) {
        param[i] = new int[width];
        for (int j = 0; j < width; j++)
            param[i][j] = otherMat.param[i][j];
    }
}
 
Matrix::~Matrix() {
    for (int i = 0; i < height; i++) {
        delete [] param[i];
    }
    delete [] param;
}
 
bool Matrix::operator ==(const Matrix& matOther) {
    if (name != matOther.name || width != matOther.width
        || height != matOther.height)
        return false;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (param[i][j] != matOther.param[i][j])
                return false;
    return true;
}
 
bool Matrix::operator !=(const Matrix& matOther) {
    if (*this == matOther) return false;
    return true;
}
 
void Matrix::operator +=(const Matrix& matOther) {
    if (height != matOther.height || width != matOther.width) {
        cout << "invalid addition.\n";
        return;
    }
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            param[i][j] += matOther.param[i][j];
}
 
void Matrix::operator -=(const Matrix& matOther) {
    if (height != matOther.height || width != matOther.width) {
        cout << "invalid substraction.\n";
        return;
    }
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            param[i][j] -= matOther.param[i][j];
}
 
Matrix Matrix::operator *(const Matrix& matOther) {
    if (width != matOther.height) {
        cout << "invalid multiplication.\n";
        return Matrix();
    }
    int **mat_arr = new int*[height];
    for (int i = 0; i < height; i++) {
        mat_arr[i] = new int[matOther.width];
        for (int j = 0; j < matOther.width; j++) {
            mat_arr[i][j] = 0;
        }
    }
    Matrix matTemp = Matrix("newMat", height, matOther.width, mat_arr);
    int value = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < matOther.width; j++) {
            value = 0;
            for (int p = 0; p < matOther.height; p++) {
                value += param[i][p]*matOther.param[p][j];
            }
            matTemp.param[i][j] = value;
        }
    }
    for (int i = 0; i < height; i++) {
        delete [] mat_arr[i];
    }
    delete [] mat_arr;
    return matTemp;
}
 
