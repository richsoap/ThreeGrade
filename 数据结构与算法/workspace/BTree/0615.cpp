#include<stdio.h>
using namespace std;
char* data;
struct node{
  int kind;
  node *children;
  node():kind(0),children(NULL) {  }
  ~node() {
    if(kind == 1) {
      delete []children;
    }
  }
  bool insert(int start) {
    if(kind == 2) {
      return false;
    }
    if(data[start] == '\0') {
      if(kind == 0) {
        kind = 2;
        return true;
      }
      else {
        return false;
      }
    }
    if(kind == 0)
      children = new node[10];
    kind = 1;
    return children[data[start] - '0'].insert(start + 1);
  }
};

int main() {
  int t,n;
  bool flag;
  node* root;
  data = new char[20];
  scanf("%d",&t);
  while(t --) {
    scanf("%d",&n);
    flag = true;
    root = new node;
    while(n --) {
      scanf("%s",data);
      if(!flag)
      continue;
      flag = root->insert(0);
    }
    if(flag) {
      printf("YES\n");
    }
    else {
      printf("NO\n");
    }
  }
}
