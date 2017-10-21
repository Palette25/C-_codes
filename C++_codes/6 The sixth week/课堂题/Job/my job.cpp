#include <iostream> 
#include <cstdio>
#include <string>
static int number = 0;
using namespace std;
class Job {
    public:
        explicit Job(int priority = 0);
        void setId(int id);
        int getId() const;
        void setPriority(int priority);
        int getPriority() const;
        void setNext(Job *job);
        Job *getNext() const;
        string toString();
    private:
        static int number;
        int id;
        int priority;
        Job *nextJob;
};
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

class JobManager {
    public:
        // get the unique instance
        static JobManager* getInstance();
        static bool deleteInstance();

        void addJob(int priority = 0);
        void finishOneJob();
        void sortJob();
        void printJob();
        int getNumOfJob();
        void clear();

    private:
        Job * jobFrontPointer;
        ~JobManager();
        JobManager();
        static JobManager* instance;
        DISALLOW_COPY_AND_ASSIGN(JobManager);
};

int Job::number = 0;
Job::Job(int priority_){
	priority = priority_;
	nextJob = NULL;
	id = 0;
}
void Job::setId(int id_){
	id = id_;
}
int Job::getId() const{
	return id;
}
void Job::setPriority(int priority_){
	priority = priority_;
}
int Job::getPriority() const{
	return priority;
}
void Job::setNext(Job *job){
	nextJob = job;
}
Job* Job::getNext() const{
    return nextJob;
}
string Job::toString(){
	string str = "[";
	char arr[50]={0};
	sprintf(arr, "%d", getId());
	str += arr;
	str += ":";
	sprintf(arr, "%d", getPriority());
	str += arr;
	str += "]";
	return str;
}
JobManager* JobManager::instance = NULL;
JobManager* JobManager::getInstance(){
	if(instance!=NULL) return instance;
	else {
		instance = new JobManager;
		return instance;
	}
}
bool JobManager::deleteInstance(){
	if(instance==NULL) return 0;
	else {
		delete instance;
		instance = NULL;
		return 1;
	}
}
void JobManager::addJob(int priority){
	Job* ptr = new Job;
	ptr->setPriority(priority);
	ptr->setId(number);
	if(jobFrontPointer==NULL) {
		jobFrontPointer = ptr;
	}
	else {
		Job* pre = jobFrontPointer;
		while(pre->getNext()!=NULL){
			pre = pre->getNext();
		}
		pre->setNext(ptr);
	}
	number++;
}
void JobManager::finishOneJob(){
	if(jobFrontPointer!=NULL){
	Job* ptr = jobFrontPointer->getNext();
    delete jobFrontPointer;
	jobFrontPointer = ptr;
}
}
void JobManager::sortJob(){
	int arr1[1000], arr2[1000], i = 0, j = 0, sum = 0;
	Job* ptr = jobFrontPointer;
	while(ptr!=NULL){
		arr1[i++] = ptr->getPriority();
		arr2[j++] = ptr->getId();
		ptr = ptr->getNext();
		sum++;
	}
	for(i=0;i<sum-1;i++){
		for(j=i+1;j<sum;j++){
			if(arr1[i]<arr1[j]) {
				int temp = arr1[i];
				arr1[i] = arr1[j];
				arr1[j] = temp;
				temp = arr2[i];
				arr2[i] = arr2[j];
				arr2[j] = temp;
			}
			if(arr1[i]==arr1[j]) {
				if(arr2[i]>arr2[j]) {
					int temp = arr1[i];
				    arr1[i] = arr1[j];
				    arr1[j] = temp;
				    temp = arr2[i];
				    arr2[i] = arr2[j];
			    	arr2[j] = temp;
				}
			}
		}
	}
	ptr = jobFrontPointer;
	i = 0;
	j = 0;
	while(ptr!=NULL){
		ptr->setPriority(arr1[i++]);
		ptr->setId(arr2[j++]);
		ptr = ptr->getNext();
	}
	ptr = NULL;
}
void JobManager::printJob(){
	Job* ptr = jobFrontPointer;
	while(ptr!=NULL){
		if(ptr->getNext()!=NULL) cout << ptr->toString() << "->";
		else cout << ptr->toString() << endl;
		ptr = ptr->getNext();
	}
	ptr = NULL;
	if(getNumOfJob()==0) cout << "empty!" << endl;
}
int JobManager::getNumOfJob(){
	int num = 0;
	Job* ptr = jobFrontPointer;
	while(ptr!=NULL){
		ptr = ptr->getNext();
		num++;
	}
	return num;
}
void JobManager::clear(){
	Job* ptr = jobFrontPointer, *pre = NULL;
	while(ptr!=NULL){
		pre = ptr;
		ptr = ptr->getNext();
		delete pre;
	}
	ptr = NULL;
    jobFrontPointer = NULL;
}
JobManager::~JobManager(){
		Job* ptr = jobFrontPointer, *pre = NULL;
	while(ptr!=NULL){
		pre = ptr;
		ptr = ptr->getNext();
		delete pre;
	}
	ptr = NULL;
    jobFrontPointer = NULL;
}
JobManager::JobManager(){
	jobFrontPointer = NULL;
}

int main() {
    JobManager *manager1 = JobManager::getInstance();
    JobManager *manager2 = JobManager::getInstance();
    int pris[5] = {234, 23, 23432, 1, 5};
    for (int i = 0; i < 5; i++) {
        manager1->addJob(pris[i]);
    }
    manager2->printJob();
    cout << "The number of job is: " << manager1->getNumOfJob() << endl;
    manager1->finishOneJob();
    cout << "The number of job is: " << manager1->getNumOfJob() << endl;
    manager2->finishOneJob();
    cout << "The number of job is: " << manager1->getNumOfJob() << endl;
    manager1->addJob();
    manager1->addJob(6666);
    manager1->printJob();
    cout << "The number of job is: " << manager1->getNumOfJob() << endl;
    manager2->clear();
    manager1->printJob();
    cout << "The number of job is: " << manager1->getNumOfJob() << endl;

    int jobNum, jobPriority, deleteNum;
    cin >> jobNum;
    for (int i = 0; i < jobNum; i++) {
       cin >> jobPriority;
        manager2->addJob(jobPriority);
    }
    manager1->sortJob();
    manager2->printJob();
    cin >> deleteNum;
    while (deleteNum--) {
        manager1->finishOneJob();
    }
    manager1->printJob();
    cout << "The number of job is: " << manager2->getNumOfJob() << endl;

    if (JobManager::deleteInstance()) cout << "Delete successfully!\n";
    else cout << "Delete failure!\n";

    if (JobManager::deleteInstance()) cout << "Delete successfully!\n";
    else cout << "Delete failure!\n";
}
