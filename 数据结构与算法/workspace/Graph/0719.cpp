#include<stdio.h>
#include<queue>

bool map[2000][2000];

int main() {
  int v,a;
  int from,to;
  bool flag;
  std::queue<int> outData;
  scanf("%d %d",&v,&a);
  for(int i = 0;i <= v;i ++) {
    for(int p = 0;p <= v;p ++) {
      map[i][p] = false;
    }
  }
  for(int i = 0;i < a;i ++) {
    scanf("%d %d",&from,&to);
    map[from][to] = true;
  }
  for(int i = 0;i < v;i ++) {
    for(int p = 1;p <= v;p ++) {
      flag = false;
      for(int q = 1;q <= v;q ++) {
        flag = flag | map[q][p];
      }
      if(!flag) {
        outData.push(p);
        for(int q = 1;q <= v;q ++) {
          map[p][q] = false;
        }
        map[p][p] = true;
        break;
      }
    }
  }
  printf("v%d",outData.front());
  outData.pop();
  for(int i = 1;i < v;i ++) {
    printf(" v%d",outData.front());
    outData.pop();
  }
  return 0;
}

/*
6 8
1 2
1 3
1 4
3 2
3 5
4 5
6 4
6 5

v1 v3 v2 v6 v4 v5
*/
