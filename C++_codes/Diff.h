#ifndef DIFF_H
#define DIFF_H
class Diff{
public:
	Diff(string one_, string two_);
	void isValid_in(int arg);
	void isValid_take();
	int isValid_open();
	void Mainoperation();
private:
	string one;
	string two;
};
#endif