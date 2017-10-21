#include <iostream>
#include <queue>
using namespace std;
int row, columns, startx, starty;
char maze[25][25];
bool visited[25][25];
int abs(int x){
	if(x<0) return -x;
	else return x;
}

struct node{
	int x;
	int y;
	node(int x1, int y1){x = x1; y = y1;}
};

bool valid(node n1){
	if(n1.x>=0&&n1.x<row&&n1.y>=0&&n1.y<columns) return 1;
	else return 0;
}

int main(){
	cin >> row;
    cin >> columns;
	node end1(0, 0);
	for(int i=0;i<row;i++){
		for(int j=0;j<columns;j++){
			cin >> maze[i][j];
			if(maze[i][j]=='S') {
				startx = i;
				starty = j;
			}
		    if(maze[i][j]=='E') {
		    	end1.x = i;
		    	end1.y = j;
		    }
		}
	}
	node dir[4] = {node(0, 1), node(1, 0), node(0, -1), node(-1, 0)};
	queue<node> way;
	int path = 0;
	node current(startx, starty), with(0, 0);
	way.push(current);
	visited[startx][starty] = 1;
	while(!way.empty()) {
		int flag = 0;
		current = way.front();
		way.pop();
		for(int i=0;i<4;i++){
			with = node(current.x + dir[i].x, current.y + dir[i].y);
			if(with.x==end1.x&&with.y==end1.y) {
				cout << abs(end1.x - startx) + abs(end1.y - starty) << endl;
				return 0;
			}
			if(valid(with)&&!visited[with.x][with.y]&&maze[with.x][with.y]=='.'){
				way.push(with);
				visited[with.x][with.y] = 1;
				path++;
			}
			else if(maze[with.x][with.y]!='E') flag++;
		}
	}
	cout << "-1" << endl;
	return 0;
}
