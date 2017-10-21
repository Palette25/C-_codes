#include <iostream>
#include <string.h>
using namespace std;

class Matrix {
    public:
        Matrix() {
            name = "";
            width = height = 0;
            param = NULL;
        }
        Matrix(string, int, int, int**);
        Matrix(const Matrix &);
        ~Matrix();
        void setName(string newName) {
            name = newName;
        }
        string getName() {
            return name;
        }
        void print() {
            cout << name << " = [\n";
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (j == width-1) cout << param[i][j];
                    else cout << param[i][j] << ", ";
                }
                cout << "\n";
            }
            cout << "]\n";
        }
        // overload operator
        bool operator ==(const Matrix&);
        bool operator !=(const Matrix&);
        void operator +=(const Matrix&);
        void operator -=(const Matrix&);
        Matrix operator *(const Matrix&);
    private:
        string name;
        int width, height, **param;
};
Matrix::Matrix(string str, int h, int w, int** mat_arr){
	int i = 0, j = 0;
	name = str;
	width = w;
	height = h;
	param = new int*[h];
	for(i=0;i<h;i++){
		param[i] = new int[w];
		for(j=0;j<w;j++)
			param[i][j] = mat_arr[i][j];
	}
}
Matrix::Matrix(const Matrix & matrix){
	name = matrix.name;
	height = matrix.height;
	width = matrix.width;
	param = new int*[height];
	int** point = matrix.param;
	for(int i=0;i<height;i++){
		param[i] = new int[width];
		for(int j=0;j<width;j++)
			param[i][j] = point[i][j];
	}
}
Matrix::~Matrix(){
	if(param!=NULL){
	int* point = NULL;
	for(int i=0;i<height;i++){
		point = param[i];
		delete [] point;
	}
	delete param;//在delete二重指针时，先delete第一重，再delete第二重！！1！
	param = NULL;
	point = NULL;
}
}
bool Matrix::operator ==(const Matrix& matrix){
	if(height!=matrix.height||width!=matrix.width) return 0;
	int** point = matrix.param;
		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				if(param[i][j]!=point[i][j]) return 0;
				else continue;
			}
		}
	return 1;
}
bool Matrix::operator !=(const Matrix& matrix){
	if(height!=matrix.height||width!=matrix.width) return 1;
	int** point = matrix.param;
		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				if(param[i][j]==point[i][j]) return 1;
				else continue;
			}
		}
	return 0;
}
void Matrix::operator +=(const Matrix& matrix){
	int i = 0, j = 0;
	if(height!=matrix.height||width!=matrix.width) {
		std::cout << "invalid addition.\n";
		return;
	}
	for(i=0;i<height;i++){
		for(j=0;j<width;j++)
			param[i][j]+=matrix.param[i][j];
	}
}
void Matrix::operator -=(const Matrix& matrix){
	int i = 0, j = 0;
	if(height!=matrix.height||width!=matrix.width) {
		std::cout << "invalid substraction.\n";
		return;
	}
	for(i=0;i<height;i++){
		for(j=0;j<width;j++)
			param[i][j]-=matrix.param[i][j];
	}
}
Matrix Matrix::operator *(const Matrix& matrix){
	int i = 0, j = 0;
	Matrix new1;
	if(width!=matrix.height) {
		std::cout << "invalid multiplication.\n";
		return new1;
	}
	int** arr = new int*[height];
	for(i=0;i<height;i++){
	 arr[i] = new int[matrix.width];
		for(j=0;j<matrix.width;j++){
			arr[i][j] = 0;
			for(int k=0;k<width;k++)
				arr[i][j] += param[i][k] * matrix.param[k][j];
		}
	}
	Matrix new_matrix("newMat",height,matrix.width,arr);
	int* point = NULL;
	for(int i=0;i<height;i++){
		point = arr[i];
		delete [] point;
	}
	arr = NULL;
	point = NULL;
	return new_matrix;
}
int main() {
    int h1, w1, h2, w2, n;
    string name1 = "Mat1";
    string name2 = "Mat2";
    cin >> h1 >> w1;
    int **mat1_arr = new int*[h1];
    for (int i = 0; i < h1; i++) {
        mat1_arr[i] = new int[w1];
        for (int j = 0; j < w1; j++) {
            cin >> mat1_arr[i][j];
        }
    }
    cin >> h2 >> w2;
    int **mat2_arr = new int*[h2];
    for (int i = 0; i < h2; i++) {
        mat2_arr[i] = new int[w2];
        for (int j = 0; j < w2; j++) {
            cin >> mat2_arr[i][j];
        }
    }
    Matrix mat1 = Matrix(name1, h1, w1, mat1_arr);
    mat1.print();
    Matrix mat2 = Matrix(name2, h2, w2, mat2_arr);
    mat2.print();
    cout << "\n(Mat1 += Mat2) addition result:\n";
    mat1 += mat2;
    mat1.print();
    cout << "\n(Mat1 -= Mat2) substraction result:\n";
    mat1 -= mat2;
    mat1.print();
    cout << "\n(Mat1 * Mat2) production result:\n";
    Matrix mat3 = mat1 * mat2;
    if (mat3.getName() != "") mat3.print();
    for (int i = 0; i < h1; i++) {
        delete [] mat1_arr[i];
    }
    delete [] mat1_arr;
    for (int i = 0; i < h2; i++) {
        delete [] mat2_arr[i];
    }
    delete []mat2_arr;
    return 0;
}

