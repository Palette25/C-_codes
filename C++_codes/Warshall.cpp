#include <iostream>
using namespace std;
int main() {
	int closure[10][10], len = 0, num = 0;
	cin >> len;
	for(int i=0;i<len;i++){
		for(int j=0;j<len;j++)
			cin >> closure[i][j];
	}
	for(int k=0;k<len;k++){
		for(int i=0;i<len;i++)
			for(int j=0;j<len;j++)
				closure[i][j] = closure[i][j] | (closure[i][k]&closure[k][j]);
	}
	int a, b;
    cin >> num;
    for(int i=0;i<num;i++){
    	cin >> a >> b;
    	cout << closure[a][b] << " ";
    }
    cout << endl;
    return 0;
}
