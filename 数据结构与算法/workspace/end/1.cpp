#include<stdio.h>
#include<list>
using namespace std;

struct node{
  int value;
  int loc;
  node(int _value = 0,int _location = 0):value(_value),loc(_location) {}
};

int data[1000010];
int outMin[1000010];
int outMax[1000010];
int main() {
  list<node> minQue;
  list<node> maxQue;
  int n,k;
  scanf("%d %d",&n,&k);
    for(int i = 0;i < n;i ++) {
      scanf("%d",data+i);
    }
    minQue.clear();
    maxQue.clear();
    for(int i = 0;i < n;i ++) {
      while(!minQue.empty() && i - minQue.front().loc >= k) {
        minQue.pop_front();
      }
//      printf("front min %d\n",i);
      while(!minQue.empty() && minQue.back().value > data[i]) {
        minQue.pop_back();
      }
  //    printf("back min %d\n",i);
      minQue.push_back(node(data[i],i));
      while(!maxQue.empty() && i - maxQue.front().loc >= k) {
        maxQue.pop_front();
      }
    //  printf("front max %d\n",i);
      while(!maxQue.empty() && maxQue.back().value < data[i]) {
        maxQue.pop_back();
      }
      //printf("back max %d\n",i);
      maxQue.push_back(node(data[i],i));
      outMin[i] = minQue.front().value;
      outMax[i] = maxQue.front().value;
    }
    printf("%d",outMin[k-1]);
    for(int i = k;i < n;i ++) {
      printf(" %d",outMin[i]);
    }
    printf("\n");
    printf("%d",outMax[k-1]);
    for(int i = k;i < n;i ++) {
      printf(" %d",outMax[i]);
  }
}
