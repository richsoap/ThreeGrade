# include<stdio.h>
int priority[256];
int numbers[1024];
char operate[1024];
int operateLoc,numberLoc;
int main() {
  char str[1025];
  scanf("%s", str);
  int i = -1;
  int intBuffer = 0;
  operateLoc = 0;
  numberLoc = 0;
  priority['+'] = priority['-'] = 1;
  priority['*'] = priority['/'] = 2;
  priority[')'] = priority['('] = -1;
  while(str[++i] != '\0') {
    switch(priority[str[i]]) {
      case 2:operate[operateLoc ++] = str[i];
      break;
      case 1:
      if(priority[operate[operateLoc]] > priority[str[i]]) {
        cacu();
      }
      else {
        operate[operateLoc ++] = str[i];
      }
      case -1:
      if(str[i] == '(') {
        operate[operateLoc ++] = str[i];
      }
      else {
        cacu();
        operateLoc --;
      }
      default:
      
    }
  }
}
