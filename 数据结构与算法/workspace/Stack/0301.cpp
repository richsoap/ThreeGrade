#include <stdio.h>
#include <list>
using namespace std;
struct datapair {
  int location,value;
  datapair(int _location = 0,int _value = 0):location(_location),value(_value) {}
};
int main() {
  list<datapair> maxData,minData;
  list<int> maxOut,minOut;
  list<int>::iterator it;
  int K,N,temp;
  scanf("%d %d",&N,&K);
  for(int i = 0;i < N;i ++) {
    scanf("%d",&temp);
    while(!maxData.empty()) {
      if(i - maxData.front().location >= K) {
        maxData.pop_front();
        continue;
      }
      else if((maxData.back()).value <= temp) {
        maxData.pop_back();
      }
      else {
        break;
      }
    }
    while(!minData.empty()) {
      if(i - minData.front().location >= K) {
        minData.pop_front();
        continue;
      }
      else if(minData.front().value >= temp) {
        minData.pop_front();
      }
      else {
        break;
      }
    }
    maxData.push_back(datapair(i,temp));
    minData.push_back(datapair(i,temp));
    maxOut.push_back(maxData.front().value);
    minOut.push_back(minData.front().value);
  }
  for(int i = 0;i < K - 1;i ++) {
    maxOut.pop_front();
    minOut.pop_front();
  }
  printf("%d",minOut.front());
  minOut.pop_front();
  for(it = minOut.begin();it != minOut.end();it ++) {
    printf(" %d",*it);
  }
  printf("\n%d",maxOut.front());
  maxOut.pop_front();
  for(it = maxOut.begin();it != maxOut.end();it ++) {
    printf(" %d",*it);
  }
  return 0;
}
