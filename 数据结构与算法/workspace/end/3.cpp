#include<stdio.h>

char* key;
struct node{
  char* value;
  node* subNode[26];
  node():value(NULL) {
    for(int i = 0;i < 26;i ++)
    subNode[i] = NULL;
  }
  node* getNode(int position) {
    if(key[position] == '\0') {
      return this;
    }
    else if(subNode[key[position] - 'a'] == NULL) {
      return NULL;
    }
    else {
      return subNode[key[position] - 'a']->getNode(position + 1);
    }
  }
  node* makeNode(int position) {
    if(key[position] == '\0') {
      return this;
    }
    else if(subNode[key[position] - 'a'] == NULL) {
      subNode[key[position] - 'a'] = new node();
      return subNode[key[position] - 'a']->makeNode(position + 1);
    }
    else {
      return subNode[key[position] - 'a']->makeNode(position + 1);
    }
  }
};

int main() {
  char* buffer;
  char* tempBuffer;
  int operate,pointA,pointB;
  buffer = new char[40];
  node* theEnd;
  node* root = new node();
  key = new char[20];
  while(true) {
    fgets(buffer,40,stdin);
    if(buffer[0] == '\n') {
      break;
    }
    operate = 0;
    pointA = 0;
    pointB = 0;
    tempBuffer = new char[12];
    for(int i = 0;i < 23 && buffer[i] != '\0';i ++) {
      if(buffer[i] == ' ') {
        operate++;
        tempBuffer[pointA] = '\0';
        continue;
      }
      else if(buffer[i] == '\n') {
        key[pointB] = '\0';
        break;
      }
      if(operate == 0) {
        tempBuffer[pointA ++] = buffer[i];
      }
      else {
        key[pointB ++] = buffer[i];
      }
    }
    theEnd = root->makeNode(0);
    theEnd->value = tempBuffer;
  }
  while(scanf("%s",key) != EOF) {
    theEnd = root->getNode(0);
    if(theEnd == NULL || theEnd->value == NULL) {
      printf("eh\n");
    }
    else {
      printf("%s\n",theEnd->value);
    }
  }
  return 0;
}

/*
dog ogday
cat atcay
pig igpay
froot ootfray
loops oopslay

atcay
ittenkay
oopslay

cat
eh
loops
*/
