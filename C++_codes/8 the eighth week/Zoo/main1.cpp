#include <iostream>
using namespace std;
class gameobject {
public:
	gameobject(double x_, double y_){
		x = x_;
		y = y_;
		hp = 10;
	}
	virtual void select() = 0;
	virtual void move() = 0;
	int get_hp(){
		return hp;
	}
	void change_hp(int _hp){
		hp = _hp;
	}
protected:
	int hp;
	double x;
	double y;
};

class worker:public gameobject{
public:
	worker(double x_, double y_):gameobject(x_, y_){}
	virtual void select(){
		cout << "Scv good to go, sir!" << endl;
	}
	virtual void move(){
		cout << "Worker moves to (" << x+1 << ", " << y+1 << ")" << endl;
	}
	void repair(gameobject* z){
		z->change_hp(10);
	}
	void build(int num){
		for(int i=0;i<num;i++){
			for(int j=0;j<num-i-1;j++)
				cout << " ";
			for(int k=0;k<2*(i+1)-1;k++)
				cout << "*";
			cout << endl;
		}
	}
};

class zealot:public gameobject{
public:
	zealot(double x_, double y_):gameobject(x_, y_){}
	virtual void select(){
		cout << "My life for Aiur!" << endl;
	}
	virtual void move(){
		cout << "Zealot moves to (" << x+2 << ", " << y+2 << ")" << endl;
	}
	void attack(gameobject* tow){
		hp--;
	}
};

class tower:public gameobject{
public:
	tower(double x_, double y_):gameobject(x_, y_){}
	virtual void select(){
		cout << "~" << endl;
	}
	virtual void move(){
		cout << "Tower cannot move" << endl;
	}
	void attack(gameobject* tow){
		hp--;
	}
};

int main() {
    gameobject* g;  // gameobject是一个抽象类
    worker* w;  // worker zealot tower是派生类
    zealot* z;
    tower* t;
    double x, y;  // (x, y)表示坐标
    cin >> x >> y;
    w = new worker(x, y);
    cin >> x >> y;
    z = new zealot(x, y);
    cin >> x >> y;
    t = new tower(x, y);
    // test for select
    cout << "test for select:\n";

    g = w;
    g->select();
    g = z;
    g->select();
    g = t;
    g->select();
    // test for move
    cout << "\ntest for move:\n";

    g = w;
    g->move();
    g = z;
    g->move();
    g = t;
    g->move();
    // test for others
    cout << "\ntest for attack:\n";
    z->attack(t);
    t->attack(z);
    cout << "Zealot's hp is " << z->get_hp() << endl;
    cout << "Tower's hp is " << t->get_hp() << endl;
    cout << "\ntest for repair:\n";
    w->repair(z);  // worker将zealot的HP修复至10
    cout << "Zealot's hp is " << z->get_hp() << endl;
    int h;
    cin >> h;
    cout << "\ntest for build:\n";
    w->build(h);
    delete w;
    delete z;
    delete t;
    return 0;
    
}

