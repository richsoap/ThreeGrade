#include <stdio.h>
int main() {
  int* goods;
  int* point;
  int flag = 0;
  goods = new int[6];
  while(scanf("%d %d %d %d %d %d",goods,goods+1,goods+2,goods+3,goods+4,goods+5)) {
    if(!(goods[0]||goods[1]||goods[2]||goods[3]||goods[4]||goods[5])) {
      return 0;
    }
    if(flag ++) {
      printf("\n");
    }
  }

}
