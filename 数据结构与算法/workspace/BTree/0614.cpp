#include <stdio.h>

int student[50010];

int getRoot(int i) {
  if(student[i] == i) {
    return i;
  }
  else {
    return student[i] = getRoot(student[i]);
  }
}

int main() {
  int n,m;
  int studentA,studentB;
  int counter;
  int number;
  number = 0;
  while (scanf("%d %d",&n,&m)) {
    if(n == 0 && m == 0) {
      return 0;
    }
    number ++;
    for(int i = 0;i <= n;i ++) {
      student[i] = i;
    }
    counter = 0;
    while(m --) {
      scanf("%d %d",&studentA,&studentB);
      studentA = getRoot(studentA);
      studentB = getRoot(studentB);
      if(studentA != studentB) {
        counter ++;
        student[studentB] = studentA;
      }
    }
    printf("Case %d: %d\n",number,n-counter);
  }
}
