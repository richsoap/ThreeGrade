#include<stdio.h>

int workspace[200010];
int data[100010];

int sort(int _start,int _end,int want){
  int start = _start;
  int end = _end;
  int temp = workspace[end];
  for(;start < end;start ++) {
    if(workspace[start] > temp) {
      workspace[end] = workspace[start];
      for(;end > start;end --) {
        if(workspace[end] < temp) {
          workspace[start] = workspace[end];
          break;
        }
      }
    }
  }
  //printf("from %d to %d, end at %d and %d, result is %d\n",_start,_end,start,end,temp);
  //getchar();
  if(end < want)
    return sort(end+1,_end,want);
  else if(end > want)
    return sort(_start,end-1,want);
  else
    return temp;
}

int main() {
  int n,m;
  int start,end,want;
  while(scanf("%d %d",&n,&m) != EOF) {
    for(int i = 1;i <= n;i ++) {
      scanf("%d",data+i);
    }
    for(int i = 0;i < m;i ++) {
      scanf("%d %d %d",&start,&end,&want);
      for(int p = start;p <= end;p ++) {
        workspace[p-start]=data[p];
      }
      printf("%d\n",sort(0,end-start,want-1));
    }
  }
}


/*
7 4
1 5 2 6 3 7 4
2 5 3
4 4 1
1 7 3

5
6
3
*/
