#include<stdio.h>

int main() {
  int number;
  int point;
  char* buffer = new char[300];
  while(scanf("%d",&number)) {
    if(number == 0) {
      return 0;
    }
    point = 0;
    while(number != 0) {
      switch (number % 10) {
        case 0:
        case 1:
          buffer[point ++] = number % 10 + '0';
          break;
        case 2:
        case 4:
        case 6:
        case 8:
          buffer[point ++] = '0';
          number *= 5;
          break;
        case 3:
          buffer[point ++] = '1';
          number *= 7;
          break;
        case 5:
          buffer[point ++] = '0';
          number *= 2;
          break;
        case 7:
          buffer[point ++] = '1';
          number *= 3;
          break;
        case 9:
          buffer[point ++] = '1';
          number *= 9;
          break;
        default:
          break;
      }
      number /= 10;
    }
    while((-- point) >= 0) {
      printf("%c",buffer[point]);
    }
    printf("\n");
  }
}
/*
6
0:30
1:21


*/
