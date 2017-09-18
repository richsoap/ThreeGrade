#include <stdio.h>
#include <list>
using namespace std;

int main() {
  int N,K,P,count;
  while(scanf("%d %d %d",&N,&K,&P) != EOF) {
  list<int> cards,result;
  list<int>::iterator it;
  cards.clear();
  result.clear();
  for(int i = 1;i <= K;i ++) {
    cards.push_back(i);
  }
  it = cards.begin();
  count = 0;
  while(!cards.empty()) {
        if((++count %= N) == 0)
          result.push_back(*it);
        it = cards.erase(it);
        if(it == cards.end())
          it = cards.begin();
        for(int i = 0;i < P;i ++) {
            it ++;
            if(it == cards.end())
              it = cards.begin();
        }
  }
  result.sort();
  for(it = result.begin();it != result.end();it ++) {
    printf("%d\n",*it);
  }
}
  return 0;
}
