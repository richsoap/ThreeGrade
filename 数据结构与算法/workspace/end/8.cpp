#include<stdio.h>

const long int max = 1<<17;
long int N;
long int map[max];

long int lowBit(int x) {
  return (-x)&x;
}

void add(long int x) {
  while(x < max) {
    map[x] ++;
    x += lowBit(x);
  }
}

int getSum(long int x) {
  long int out = 0;
  while(x > 0) {
    out += map[x];
    x -= lowBit(x);
  }
  return out;
}

int main() {
  scanf("%ld",&N);
  long int total = 0;
  long int temp;
  for(long int i = 0;i < max;i ++) {
    map[i] = 0;
  }
  for(int i = 0;i < N;i ++) {
    scanf("%ld",&temp);
    total += getSum(temp);
    add(temp);
  }
  printf("%ld",total);
  scanf("%d\n",&temp);
  return 0;
}


/*
5
1 3 10 8 5

7
*/
