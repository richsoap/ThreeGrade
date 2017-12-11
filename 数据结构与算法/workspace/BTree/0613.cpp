#include<stdio.h>
#include<list>
using namespace std;

int counter;
int left[10010];
int right[10010];
char* data;
int point;
int tempH;
int maxH;

struct node{
  int value;
  list<node> children;
  node():value(counter ++) {}
  ~node() {
    children.clear();
  }
  void insert() {
    point ++;
    while(data[point] == 'd') {
      children.push_back(node());
      children.back().insert();
      if(data[point] == '\0') {
        return;
      }
      point ++;
    }
  }
  int trans() {
    int outH = 0;
    int tempH = 0;
    int leftOne,rightOne;
    list<node>::iterator it;
    if(children.empty()){
      return 0;
    }
    it = children.begin();
    leftOne = it->value;
    left[value] = leftOne;
    tempH = it->trans();
    outH = outH<tempH?tempH:outH;
    it ++;
    for(;it != children.end();it ++) {
      rightOne = it->value;
      right[leftOne] = rightOne;
      leftOne = rightOne;
      tempH = it->trans();
      outH = outH<tempH?tempH:outH;
    }
    return outH + 1;
  }
};

int getH(int i) {
  if(0 == i)
  return -1;
  int depthLeft,depthRight;
  depthLeft = getH(left[i]);
  depthRight = getH(right[i]);
  if(depthLeft > depthRight)
  return depthLeft + 1;
  else
  return depthRight + 1;
}

int main() {
  data = new char[50010];
  int number = 0;
  int treeH,bTreeH;
  node* root;
  while(true) {
    number ++;
    scanf("%s",data);
    if(data[0] == '#') {
      return 0;
    }
    counter = 1;
    point = -1;
    root = new node();
    root->insert();
    for(int i = 0;i <= counter;i ++) {
      left[i] = 0;
      right[i] = 0;
    }
    treeH = root->trans();
    bTreeH = getH(1);
    printf("Tree %d: %d => %d\n",number,treeH,bTreeH);
  }
}
