#include<iostream>
#include <cmath>
#define N 5
using namespace std; 
const int max_length = 32 * N;
class bitset {
    private:
        int a[N];
    public:
        bitset();
        void set(int pos);
        void reset(int pos);
        int count() const;
        bool test(int pos) const;
        bool any() const;
        bool none() const;
        bool all() const;
        bitset& operator&= (const bitset& b);
        bitset& operator|= (const bitset& b);
        bitset& operator^= (const bitset& b);
        bitset& operator= (const bitset& b);
        bitset& operator <<= (int pos);
        bitset& operator >>= (int pos);
        bitset operator~() const;
        bitset operator&(const bitset& b) const;
        bitset operator|(const bitset& b) const;
        bitset operator^(const bitset& b) const;
        bitset operator<<(int pos) const;
        bitset operator>>(int pos) const;
        bool operator== (const bitset& b) const;
        bool operator!= (const bitset& b) const;
        bool operator[] (int pos) const;
        friend std::ostream& operator << (std::ostream& os, const bitset& s) {
            for (int i = N-1; i >= 0; i--) {
                for (int j = 31; j >= 0; j--) {
                    if (s.a[i] & (1 << j)) os << 1;
                    else os << 0;
                }
            }
            return os;
        }
};

bitset::bitset(){
	int i = 0;
	for(i=0;i<N;i++)
	  a[i] = 0;
}
void bitset::set(int pos){
	int num = pos / 32;
	int var = pow(2, pos%32);
	a[num] = a[num] | var;
}
void bitset::reset(int pos){
	int num = pos / 32, var = 0;
	for(int i=0;i<=31;i++)
		if(i!=pos%32) var+=pow(2, i);
	a[num] = a[num] & ~(1 << (pos%32));
}
int bitset::count() const{
	int count = 0;
	for(int i=0;i<32*N;i++){
		if(test(i)==1) count++;
		else continue;
		}
	return count;
}
bool bitset::test(int pos) const{
	int num = pos / 32, var = pos % 32;;
	if((a[num]>>var)&1 == 1) return 1;
	else return 0;
}
bool bitset::any() const{
	for(int i=0;i<N;i++)
		if(a[i]>0) return 1;
	return 0;
}
bool bitset::none() const{
	for(int i=0;i<N;i++)
		if(a[i]>0) return 0;
	return 1;
}
bool bitset::all() const{
	for(int i=0;i<N;i++)
		if(a[i]!=pow(2, 31)) return 0;
	return 1;
}
bitset& bitset::operator&= (const bitset& b){
	int i = 0;
	for(i=0;i<=32*N;i++)
		if(b.test(i)==0) reset(i);
	return *this;
}
bitset& bitset::operator|= (const bitset& b){
	int i = 0;
	for(i=0;i<=32*N;i++)
		if(b.test(i)==1) set(i);
	return *this;
}
bitset& bitset::operator^= (const bitset& b){
	int i = 0;
	for(i=0;i<=32*N;i++){
		if(test(i)!=b.test(i)) set(i);
		else reset(i);
	}
	return *this;
}
bitset& bitset::operator= (const bitset& b){
	int i = 0;
	for(i=0;i<=32*N;i++){
		if(b.test(i)) set(i);
		else reset(i);
	}
	return *this;
}
bitset& bitset::operator <<= (int pos){
	int i = 0;
	while(pos--){
	for(i=32*N;i>=0;i--){
		if(i!=32*N){
           if(test(i)) set(i+1);
		   else reset(i+1);
		}
	}
	reset(0);
}
    return *this;
}
bitset& bitset::operator >>= (int pos){
	int i = 0;
	while(pos--){
		for(i=1;i<32*N;i++){
		  if(test(i)) set(i-1);
		  else reset(i-1);			
		}
	}
	return *this;
}
bitset bitset::operator~() const{
	bitset new_one;
	int i = 0;
	for(i=0;i<32*N;i++){
		if(test(i)) new_one.reset(i);
		else new_one.set(i);
	}
	return new_one;
}
bitset bitset::operator&(const bitset& b) const{
	bitset new_one;
	int i = 0;
	for(i=0;i<32*N;i++){
		if(test(i)&&b.test(i)) new_one.set(i);
		else new_one.reset(i);
	}
	return new_one;
}
bitset bitset::operator|(const bitset& b) const{
	bitset new_one;
	int i = 0;
	for(i=0;i<32*N;i++){
		if(test(i)||b.test(i)) new_one.set(i);
		else new_one.reset(i);
	}
	return new_one;
}
bitset bitset::operator^(const bitset& b) const{
	bitset new_one;
	int i = 0;
	for(i=0;i<32*N;i++){
		if(test(i)!=b.test(i)) new_one.set(i);
		else new_one.reset(i);
	}
	return new_one;
}
bitset bitset::operator<<(int pos) const{
	bitset new_one;
	int i = 0, flag = 0;
	while(pos--){
	for(i=32*N;i>=0;i--){
		if(flag==0) {
		if(i!=32*N){
           if(test(i)) new_one.set(i+1);
		   else new_one.reset(i+1);
		}
		else new_one.reset(0);
	}
	else {
		if(i!=32*N){
           if(new_one.test(i)) new_one.set(i+1);
		   else new_one.reset(i+1);
		}
		else new_one.reset(0);
	}
}
    flag++;
}
    return new_one;
}
bitset bitset::operator>>(int pos) const{
	int i = 0 , flag = 0;
	bitset new_one;
	while(pos--){
		for(i=1;i<32*N;i++){
			if(flag==0){
			if(test(i)) new_one.set(i-1);
			else new_one.reset(i-1);
			if(test(32*N-1)) new_one.set(32*N-1);			
	       }
	else {
	    	if(new_one.test(i)) new_one.set(i-1);
			else new_one.reset(i-1);			
}
}
    flag++;
	}
    return new_one;
}
bool bitset::operator== (const bitset& b) const{
	int i = 0;
	for(i=0;i<32*N;i++)
		if(test(i)!=b.test(i)) return 0;
	return 1;
}
bool bitset::operator!= (const bitset& b) const{
	int i = 0;
	for(i=0;i<32*N;i++)
		if(test(i)!=b.test(i)) return 1;
	return 0;
}
bool bitset::operator[] (int pos) const{
	return test(pos);
}
int main() {
    bitset a, b;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.set(x);
    }
    cout << "a.count() is " << a.count() << "\n";
    cout << "a.test(5) is " << (a.test(5) ? "true" : "false") << "\n";
    cout << "a.any() is " << (a.any() ? "true" : "false") << "\n";
    cout << "a.none() is " << (a.none() ? "true" : "false") << "\n";
    cout << "a.all() is " << (a.all() ? "true" : "false") << "\n";
    b = ~b;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        b.reset(x);
    }
    cout << a << "\n";
    cout << b << "\n";
    if (a == b) {
        cout << "hello\n";
    }
    if (a != b) {
        cout << "world\n";
    }
    bitset c;
    // test &
    c = a;
    c &= b;
    cout << c << "\n";
    c = a & b;
    cout << c << "\n";
    // test |
    c = a;
    c |= b;
    cout << c << "\n";
    c = a | b;
    cout << c << "\n";
    // test ^
    c = a;
    c ^= b;
    cout << c << "\n";
    c = a ^ b;
    cout << c << "\n";
    // test <<
    c = a;
    c <<= 2;
    cout << c << "\n";
    c = a << 2;
    cout << c << "\n";
    // test >>
    c = b;
    c >>= 2;
    cout << c << "\n";
    c = b >> 2;
    cout << c << "\n";
    // test []
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        if (a[i])
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}


