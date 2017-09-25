#include<stdio.h>
int main() {
  char* s = new char[1000002];
  int* next = new int[1000002];
  int flag = 0;
  int p,j;
  while(scanf("%s",s)) {
    if(s[0] == '.' && s[1] == '\0')
      return 0;
    if(flag ++)
      printf("\n");
    next[0] = -1;
    p = 0;
    j = -1;
    while(s[p] != '\0') {
      if(j == -1 || s[p] == s[j])
        next[++ p] = ++j;
      else
        j = next[j];
    }
    if(p % (p-next[p]) == 0)
    printf("%d",p/(p - next[p]));
    else
    printf("1");
  }
}
