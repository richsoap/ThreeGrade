#include<stdio.h>
#include<math.h>
#include<list>

using namespace std;

struct node{
  int x,y;
  int kind;
  node(int _x = 0,int _y = 0):x(_x),y(_y),kind(0) {}
  node(const node& _node):x(_node.x),y(_node.y),kind(_node.kind) {}
  double operator - (const node& c) const {
    return sqrt((x-c.x)*(x-c.x)+(y-c.y)*(y-c.y));
  }
};

struct edge{
  node from,to;
  double value;
  edge(const node& _from,const node& _to):from(_from),to(_to),value(_from-_to) {}
};

void initGraph(double** input,int length) {
  for(int i = 0;i < length;i ++) {
    for(int p = 0;p < length;p ++) {
      input[i][p] = -1;
    }
  }
}

node map[110];
double graph[110][110][110];

int main() {
  int N,M;
  int x,y;
  int from,to;
  int counter;
  while(scanf("%d %d",&N,&M) != EOF) {
    for(int i = 1;i <= N;i ++) {
      scanf("%d %d",&x,&y);
      map[i] = node(x,y);
    }
    counter = 0;
    for(int i = 0;i < M;i ++) {
      scanf("%d %d",&from,&to);
    }
  }
}
