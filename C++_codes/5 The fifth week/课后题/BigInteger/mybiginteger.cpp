#include "Biginteger.h"

BigInteger operator+(const BigInteger& left, const BigInteger& right){
  BigInteger new_one;
  int i = 0, k = 0, j;
  int arr1[1000]={0}, arr2[1000]={0};
  for(i=0, k=0;i<left.size_;i++)
    arr1[k++] = left.data_[i];
  for(j=0, k=0;j<right.size_;j++)
    arr2[k++] = right.data_[j];
  int flag = 0, len = left.size_>right.size_?left.size_:right.size_;
  new_one.size_ = len;
  new_one.data_ = new int [new_one.size_];
  for(i=0;i<len;i++){
    new_one.data_[i] = arr1[i] + arr2[i] + flag;
    flag = new_one.data_[i]/10;
    new_one.data_[i]%=10;
  }
  return new_one;
}
BigInteger operator-(const BigInteger& left, const BigInteger& right){
	BigInteger new_one;
  int i = 0;
  new_one.size_ = left.size_;
  new_one.data_ = new int [new_one.size_];
  for (i = 0; i < left.size_; i++) {
        if (i < right.size_)    new_one.data_[i] = left.data_[i] - right.data_[i];
        else new_one.data_[i] = left.data_[i];
    }
    for (i = 0; i < left.size_; i++) 
        if (new_one.data_[i] < 0) {
            new_one.data_[i+1]--;
            new_one.data_[i] += 10;
        }
  return new_one;
}
ostream& operator<<(ostream& out, const BigInteger& Bint) {
    int flag = 0, k = 0;
    for (int i = Bint.size_-1; i >= 0; i--) {
        if (Bint.data_[i] != 0) flag = 1;
        if(Bint.data_[i]==0&&flag==0) continue;
        out << Bint.data_[i];
    }
    for (k = 0; k < Bint.size_; k++) 
        if (Bint.data_[k] != 0) break;
    if (k == Bint.size_) out << 0;
    return out;
}

BigInteger::BigInteger(){
	size_ = 0;
	data_ = NULL;
}
BigInteger::BigInteger(const string& number){
	int i = 0;
	size_ = 0;
	for(i=0;i<number.size();i++)
		size_++;
	data_ = new int [size_];
	for(i=size_-1;i>=0;i--)
		data_[i] = number[size_-1-i]-'0';
}
BigInteger::BigInteger(const BigInteger& other){
	size_ = other.size_;
	data_ = new int [size_];
	for(int i=0;i<size_;i++)
		data_[i] = other.data_[i];
}
BigInteger::~BigInteger(){
	if(data_!=NULL) delete [] data_;
}