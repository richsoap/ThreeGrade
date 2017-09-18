#include <queue>
#include <stdio.h>
using namespace std;
int main() {
  int N,K,max,min,count;
  int *point;
  queue<int> maxs,mins;
  scanf("%d %d",&N,&K);
    point = new int[K];
    for(int i = 0;i < K - 1;i ++) {
      scanf("%d",point + i);
    }
    count = K - 1;
    for(int i = 0;i < N - K + 1;i ++) {
      scanf("%d",point + count);
      count = (count + 1) % K;
      max = min = point[0];
      for(int p = 1;p < K;p ++) {
        max=max<point[p]?point[p]:max;
        min=min>point[p]?point[p]:min;
      }
      maxs.push(max);
      mins.push(min);
    }
    printf("%d",mins.front());
    mins.pop();
    while(!mins.empty()) {
      printf(" %d",mins.front());
      mins.pop();
    }
    printf("\n%d",maxs.front());
    maxs.pop();
    while(!maxs.empty()) {
      printf(" %d",maxs.front());
      maxs.pop();
    }
  return 0;
}
