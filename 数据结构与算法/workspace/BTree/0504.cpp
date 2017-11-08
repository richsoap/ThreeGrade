#include <stdio.h>
#include <cstring>
#define low(a) a&(-a)
#define N 32010
int count[N];
int sum[N];
int n;
int getsum(int x) {
  int result = 0;
  while(x > 0) {
    result += count[x];
    x -= low(x);
  }
  return result;
}

void update(int x) {
  while(x < N) {
    count[x] ++;
    x += low(x);
  }
}

int main() {
  int x,y;
  while(scanf("%d",&n) != EOF) {
    memset(count,0,sizeof(count));
    memset(sum,0,sizeof(sum));
    for(int i = 0;i < n;i ++) {
      scanf("%d %d",&x,&y);
      x++;
      sum[getsum(x)] ++;
      update(x);
    }
    for(int i = 0;i < n;i ++) {
      printf("%d\n",sum[i]);
    }
  }
  return 0;
}
