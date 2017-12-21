#include<stdio.h>

int graph[110][110];
int been[110];

int main() {
  int t;
  int from,to,weight;
  int n,m;
  int minWeight,minCounter;
  int minSum;
  scanf("%d",&t);
  while(t --) {
    scanf("%d %d",&n,&m);
    if(n == 1) {
      printf("0\n");
      continue;
    }
    for(int i = 0;i <= n;i ++) {
      been[i] = false;
      for(int p = 0;p <= n;p ++) {
        graph[i][p] = 0x3f3f3f3f;
      }
    }
    for(int i = 0;i < m;i ++) {
      scanf("%d %d %d",&from,&to,&weight);
      graph[from][to] = weight;
      graph[to][from] = weight;
    }

    for(int p = 1;p <= n;p ++) {
      minWeight = 0x3f3f3f3f;
      minCounter = 1;
      for(int q = 1;q <= n;q ++) {
        if(graph[q][p] < minWeight) {
          minCounter = 1;
          minWeight = graph[q][p];
        }
        else if(graph[q][p] == minWeight) {
          minCounter ++;
        }
      }
      if(minCounter != 1) {
        break;
      }
    }

    if(minCounter != 1) {
      printf("Not Unique!\n");
      continue;
    }
    been[0] = 1;
    for(int i = 0;i <= n;i ++) {
      graph[i][1] = 0x3f3f3f3f;
    }
    minSum = 0;
    for(int i = 1;i < n;i ++) {
      minWeight = 0x3f3f3f3f;
      minCounter = 0;
      for(int p = 0;p < i;p ++) {
        for(int q = 1;q <= n;q ++) {
          if(graph[been[p]][q] < minWeight) {
            minWeight = graph[been[p]][q];
            minCounter = q;
          }
        }
      }
//      printf("selsect:%d %d\n",minCounter,minWeight);
      been[i] = minCounter;
      minSum += minWeight;
      for(int p = 0;p <= n;p ++) {
        graph[p][minCounter] = 0x3f3f3f3f;
      }
    }
    printf("%d\n",minSum);
  }
  return 0;
}


/*
3
3 3
1 2 1
2 3 2
3 1 3
4 4
1 2 2
2 3 2
3 4 2
4 1 2
*/
