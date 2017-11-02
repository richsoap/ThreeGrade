#include <algorithm>
#include <stdio.h>
#include <list>
using namespace std;
class node{
  public:
    int x,y,c;

  public:
  node(int _x = 0,int _y = 0,int _c = 0):x(_x),y(_y),c(_c) {}
  bool operator < (const node& n) {
    return y < n.y;
  }
};

bool cmp(const node& n1,const node& n2) {
  return n1.x < n2.x;
}
int main() {
  int maxBrightness,n,w,h,x,y,c;
  list<node> queue;
  node* buffer = new node[10000];
  while(scanf("%d %d %d",&n,&w,&h) != EOF) {
    maxBrightness = 0;
    for(int i = 0;i < n;i ++) {
      scanf("%d %d %d",&x,&y,&c);
      buffer[i] = node(x,y,c);
    }
    sort(buffer,buffer + n,cmp);

  }
}
