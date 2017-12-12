#include<stdio.h>

int map[27][27];
int graph[27];

void remove(int node) {
  for(int p = 0;p < 26;p ++) {
    map[p][node] = 200;
  }
}

int main() {
  int n,k;
  char* buffer = new char[10];
  char* target = new char[10];
  int dic;
  int minDic,to;
  int sum;
  while(scanf("%d",&n) != EOF) {
    for(int p = 0;p < 27;p ++) {
      graph[p] = -1;
      for(int q = 0;q < 27;q ++) {
        map[p][q] = 200;
      }
    }
    for(int i = 1;i < n;i ++) {
      scanf("%s %d",buffer,&k);
      while (k--) {
        scanf("%s %d",target,&dic);
        //printf("set %s->%d\n",target,dic);
        map[buffer[0]-'A'][target[0]-'A'] = dic;
        map[target[0]-'A'][buffer[0]-'A'] = dic;
      }
    }
    for(int p = 0;p < 26 && graph[0] == -1;p ++) {
      for(int q = 0;q < 26;q ++) {
          if(map[p][q] != -1){
            graph[0] = p;
            break;
          }
      }
    }
    sum = 0;
    remove(graph[0]);
    for(int p = 1;p < n;p ++) {
      minDic = 200;
      for(int q = 0;q < p;q ++) {
        for(int i = 0;i < 27;i ++) {
          if(map[graph[q]][i] < minDic) {
            minDic = map[graph[q]][i];
            to = i;
          }
        }
      }
      graph[p] = to;
      sum += minDic;
      remove(to);
    }
    printf("%d\n",sum);
  }
  return 0;
}

/*
9
A 2 B 12 I 25
B 3 C 10 H 40 I 8
C 2 D 18 G 55
D 1 E 44
E 2 F 60 G 38
F 0
G 1 H 35
H 1 I 35
*/
