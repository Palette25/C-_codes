#include <iostream>
using namespace std;
using std::cout;
using std::endl;
int ID = 0;
struct person{
	int friends[100];
	int size;
	int id;
	person(int size_ = 0){size = size_;id = ID++;}
};
 class group {
 public:
 	group(bool flag);
    void displayGroup();
    bool addMember(person &p);
    bool deleteMember(person &p);
    bool makeFriend(person &p1, person &p2);
    bool breakRelation(person &p1, person &p2);
private:
	person humans[990];
	int size;
	bool flag;
};

group::group(bool flag_){
	size = 0;
	flag = flag_;
}
void group::displayGroup(){
	for(int i=0;i<size;i++){
		cout << "Person_" << humans[i].id << ": ";
		if(humans[i].size==0) cout << "null";
		for(int j=0;j<humans[i].size;j++){
			if(j!=humans[i].size-1) cout << humans[i].friends[j] << ", ";
			else  cout << humans[i].friends[j];
		}
		cout << endl;
	}
}
bool group::addMember(person &p){
	humans[size] = p;
	size++;
	if(flag==1){
		for(int i=0;i<size;i++)
		if(i!=size-1) makeFriend(humans[i], humans[size-1]);
	}
    return 1;
}
bool group::deleteMember(person &p){
	int i = 0;
	for(i=0;i<size;i++)
		if(i==p.id) break;
	for(;i<size-1;i++)
		humans[i] = humans[i+1];
	size--;
	return 1;
}
bool group::makeFriend(person &p1, person &p2){
	int i = 0, j = 0;
	while(1){
		if(p1.id==humans[i].id) break;
		i++;
	}
	while(1){
		if(p2.id==humans[j].id) break;
		j++;
	}
	humans[i].friends[humans[i].size] = p2.id;
	humans[j].friends[humans[j].size] = p1.id;
	humans[i].size++;
	humans[j].size++;
	return 1;
}
bool group::breakRelation(person &p1, person &p2){
	int k = 0;
	int i = 0, j = 0;
	while(1){
		if(p1.id==humans[i].id) break;
		i++;
	}
	while(1){
		if(p2.id==humans[j].id) break;
		j++;
	}
	for(k=0;k<humans[i].size;k++)
		if(humans[i].friends[k]==p2.id) break;
	for(;k<humans[i].size-1;k++)
		humans[i].friends[k] = humans[i].friends[k+1];
	humans[i].size--;
	for(k=0;k<humans[j].size;k++)
		if(humans[j].friends[k]==p1.id) break;
	for(;k<humans[j].size-1;k++)
		humans[j].friends[k] = humans[j].friends[k+1];
	humans[j].size--;
	return 1;
}

 void test_1() {
    person mike, jack, lily, carson, sucie;
    group school(0), family_1(1), family_2(1);
    // make group (act as a society)
    school.addMember(mike);
    school.addMember(jack);
    school.addMember(lily);
    family_1.addMember(mike);
    family_1.addMember(carson);
    family_2.addMember(jack);
    family_2.addMember(lily);
    family_2.addMember(sucie);
    // construct relationship in the society
    school.makeFriend(mike, jack);
    school.makeFriend(mike, lily);
    // display the society
    cout << "\n------ SCHOOL -----\n";
    school.displayGroup();
    cout << "\n------ FAMILY_1 -----\n";
    family_1.displayGroup();
    cout << "\n------ FAMILY_2 -----\n";
    family_2.displayGroup();
}
 void test_2() {
    person Baidu, Alibaba, Tencent, NTES, Kingsoft_Antivirus, _360safe;
    group BAT(1), ECommerce(1), Security(1);
    // make group (act as a society)
    BAT.addMember(Baidu);
    BAT.addMember(Alibaba);
    BAT.addMember(Tencent);
    ECommerce.addMember(Baidu);
    ECommerce.addMember(Alibaba);
    ECommerce.addMember(Tencent);
    ECommerce.addMember(NTES);
    Security.addMember(Kingsoft_Antivirus);
    Security.addMember(_360safe);
    // display the society
    cout << "\n------ BAT -----\n";
    BAT.displayGroup();
    cout << "\n------ ECommerce -----\n";
    ECommerce.displayGroup();
    cout << "\n------ Security -----\n";
    Security.displayGroup();
}
 void test_3() {
    person p0, p1, p2, p3, p4;
    group g0(0), g1(0), g2(1);
    // make group (act as a society)
    g0.addMember(p0);
    g0.addMember(p1);
    g0.addMember(p2);
    g1.addMember(p0);
    g1.addMember(p3);
    g2.addMember(p3);
    g2.addMember(p4);
    // construct relationship in the society
    g1.makeFriend(p0, p3);
    g2.breakRelation(p3, p4);
    g0.deleteMember(p2);
    // display the society
    cout << "\n------ G0 -----\n";
    g0.displayGroup();
    cout << "\n------ G1 -----\n";
    g1.displayGroup();
    cout << "\n------ G2 -----\n";
    g2.displayGroup();
}
 void test_4() {
    person p[50];
    group g0(0), g1(1);
    int p_count;
    cin >> p_count;
    // make group (act as a society)
    for (int i = 0; i < p_count/2; i++)
        g0.addMember(p[i]);
    for (int i = p_count/2; i < p_count; i++)
        g1.addMember(p[i]);
    // construct relationship in the society
    for (int i = 0; i < p_count/5; i += 2)
        g0.makeFriend(p[i], p[i+1]);
    for (int i = p_count/2; i < p_count*3/4-1; i += 2)
        g1.breakRelation(p[i], p[i+1]);
    for (int i = p_count/4; i < p_count/2; i++)
        g0.deleteMember(p[i]);
    for (int i = p_count*3/4; i < p_count; i++)
        g1.deleteMember(p[i]);
    // display the society
    cout << "\n------ G0 -----\n";
    g0.displayGroup();
    cout << "\n------ G1 -----\n";
    g1.displayGroup();
}
 int main() {
    int test_id;
    cin >> test_id;
    switch (test_id) {
        case 1:
        test_1();
        break;
        case 2:
        test_2();
        break;
        case 3:
        test_3();
        break;
        case 4:
        test_4();
        break;
        default:
        cout << "wrong input\n";
    }
    return 0;
}
 /* ---------- structure for 'world.h' ----------
 * define the struct and the class functions by yourself #(^_^)#
 * the member function is not complete, add something as you need
 struct person;
 class group {
    void displayGroup();
    bool addMember(person &p);
    bool deleteMember(person &p);
    bool makeFriend(person &p1, person &p2);
    bool breakRelation(person &p1, person &p2);
};
 */
 
