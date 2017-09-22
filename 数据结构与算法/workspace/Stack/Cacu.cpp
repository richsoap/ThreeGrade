# include<stdio.h>
int priority[256];
int numbers[1024];
char operate[1024];
int operateLoc,numberLoc;
void cacu(int level) {
  int A,B;
  while(operateLoc && priority[(int)operate[--operateLoc]] > level) {
    A = numbers[--numberLoc];
    B = numbers[--numberLoc];
    switch(operate[operateLoc]) {
      case '+':numbers[numberLoc ++] = A + B;
      break;
      case '-':numbers[numberLoc ++] = A - B;
      break;
      case '*':numbers[numberLoc ++] = A * B;
      break;
      case '/':numbers[numberLoc ++] = A / B;
      break;
    }
  }
}
int main() {
  char str[1025];
  scanf("%s", str);
  int i = -1;
  int intBuffer = -1;
  operateLoc = 0;
  numberLoc = 0;
  priority['+'] = priority['-'] = 1;
  priority['*'] = priority['/'] = 2;
  priority[')'] = -1;
  priority['('] = -2;
  while(str[++i] != '\0') {
    if(priority[(int)str[i]] == 0) {
      intBuffer=intBuffer<0?str[i]-'0':intBuffer*10+str[i]-'0';
    }
    else if(intBuffer >= 0) {
      numbers[numberLoc ++] = intBuffer;
      intBuffer = -1;
    }
    switch (priority[(int)str[i]]) {
      case 1: cacu(1);
      operate[operateLoc ++] = str[i];
      break;
      case -1:
      cacu(0);
      break;
      case 0:
      break;
      default:
      operate[operateLoc ++] = str[i];
    }
  }
  if(intBuffer >= 0) {
    numbers[numberLoc ++] = intBuffer;
  }
  cacu(0);
  printf("%d",numbers[0]);
  return 0;
}
