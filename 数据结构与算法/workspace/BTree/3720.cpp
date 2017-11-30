#include<stdio.h>
#include<stack>
using namespace std;

struct node {
  int level;
  char value;
  node* left;
  node* right;
  node(int _level = -1,char _value = '*'):level(_level),value(_value),left(NULL),right(NULL){}
  node(const node& newNode):level(newNode.level),value(newNode.value),left(newNode.left),right(newNode.right) {}
  void front() {
    if(value == '*')
      return;
    printf("%c",value);
    if(left != NULL)
      left->front();
    if(right != NULL)
      right->front();
  }
  void mid() {
    if(value == '*')
      return;
    if(left != NULL)
      left->mid();
    printf("%c",value);
    if(right != NULL)
      right->mid();
  }
  void back() {
    if(value == '*')
      return;
    if(left != NULL)
      left->back();
    if(right != NULL)
      right->back();
    printf("%c",value);
  }
  bool insNode(node * newNode) {
    if(newNode->level != level + 1) {
      return false;
    }
    if(left == NULL) {
      left = newNode;
      return true;
    }
    else if(right == NULL) {
      right = newNode;
      return true;
    }
    else {
      return false;
    }
  }

};

node* string2node(char * string) {
  int i = 0;
  for(;string[i] == '-';i ++) {}
  node* outNode = new node(i,string[i]);
  return outNode;
}

int main() {
  stack<node*> nodeStack;
  int treeNum;
  char* string = new char[1000];
  node* tempNode;
  node* topNode;
  node* rootNode;
  scanf("%d",&treeNum);
  while(treeNum --) {
    scanf("%s",string);
    rootNode = string2node(string);
    topNode = rootNode;
    nodeStack.push(rootNode);
    while(true) {
      scanf("%s",string);
      if(string[0] == '0')
        break;
      tempNode = string2node(string);
      while(!topNode->insNode(tempNode)) {
        nodeStack.pop();
        topNode = nodeStack.top();
      }
      nodeStack.push(tempNode);
      topNode = tempNode;
    }
    rootNode->front();
    printf("\n");
    rootNode->back();
    printf("\n");
    rootNode->mid();
    printf("\n\n");
    while(!nodeStack.empty()) {
      nodeStack.pop();
    }
  }
  return 0;
}
