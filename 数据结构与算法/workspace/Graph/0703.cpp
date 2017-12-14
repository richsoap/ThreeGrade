#include<stdio.h>
#include<stack>
#include<queue>

struct node{
  int add,kind;
  node(int _x = -1,int _y = -1):add(_x),kind(_y) {}
};

int map[210][10];
node marks[60000][2];
int counter;
int basenumber;
std::queue<node> nodeQueue;
std::stack<char> outData;

void initMap() {
  for(int p = 0;p < 210;p ++) {
    for(int i = 0;i < 10;i ++) {
      map[p][i] = -1;
    }
  }
  for(int mul = 1;mul <= 200;mul ++) {
    for(int value = 0;value < 10;value ++) {
      map[mul][(value*mul)%10] = value;
    }
  }
}

node doBFS() {
  node tempNode;
  while(true) {
    tempNode = nodeQueue.front();
    nodeQueue.pop();
    
  }
}


int main() {
  initMap();
  node outNode;
  while(scanf("%d",&basenumber)) {
    if(basenumber == 0) {
      return 0;
    }
    while(!nodeQueue.empty()) {
      nodeQueue.pop();
    }
    for(int i = 0;i < 60000;i ++) {
      marks[i][0] = node();
      marks[i][1] = node();
    }
    nodeQueue.push(node(0,0));
    nodeQueue.push(node(0,1));
    outNode = doBFS();
    while(outNode.add != 0) {
      outData.push(outNode.kind);
      outNode = marks[outNode.add][outNode.kind];
    }
    while(!outData.empty()) {
      printf("%c",outData.top());
      outData.pop();
    }
    printf("\n");
  }
}


/*
2
6
19
0

10
100100100100100100
111111111111111111

*/
