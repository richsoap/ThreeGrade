#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
int main() {
  char str[21];
  int result[21];
  int p,q,flag;
  flag = 0;
  while(gets(str)) {
    if(str == NULL) {
      return 0;
    }
    if(flag++) {
      printf("\n" );
    }
    for(p = q = 0;p < 21 && str[p] != '\0';p ++) {
      if(str[p] >= '0' && str[p] <= '9') {
        result[q ++] = str[p] - '0';
      }
    }
    sort(result,result + q);
    for(p = 0;p < q;p ++) {
      printf("   %d",result[p]);
    }
  }
}
