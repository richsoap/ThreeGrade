#include<stdio.h>

int group[200010];
int N;
int getRoot(int i) {
  if(group[i] != i)
    return group[i] = getRoot(group[i]);
  else
    return i;
}

void setGroup(int A,int B) {
  int antiA = getRoot(group[A + N]);
  int antiB = getRoot(group[B + N]);
  if(antiA > N)
    group[antiA] = B;
  else
    group[B] = antiA;
  if(antiB > N)
    group[antiB] = A;
  else
    group[A] = antiB;
}

int main() {
    int T,M;
    char* op = new char[5];
    int groupA,groupB;
    scanf("%d",&T);
    while(T --) {
      scanf("%d %d",&N,&M);
      for(int i = 0;i <= 2*N;i ++) {
        group[i] = i;
      }
      for(int i = 0;i < M;i ++) {
        scanf("%s %d %d",op,&groupA,&groupB);
        groupA = getRoot(groupA);
        groupB = getRoot(groupB);
        switch(op[0]) {
          case 'A':
          if(groupA == groupB)
          printf("In the same gang.\n");
          else if(getRoot(group[groupA + N]) == groupB)
          printf("In different gangs.\n");
          else
          printf("Not sure yet.\n");
          break;
          default:
          setGroup(groupA,groupB);
        }
      }
    }
}


/*
1 20 20
D 1 2
D 2 3
D 3 4
D 4 5
D 6 7
D 7 8
D 8 9
D 9 10
D 10 11
A 5 6
D 1 6
A 1 10
A 1 11

*/
