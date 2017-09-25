#include <stdio.h>
int main() {
  char* s = new char[100002];
  char* t = new char[100002];
  char* point_s;
  char* point_t;
  int flag = 0;
  while(scanf("%s %s",s,t) != EOF) {
    point_s = s;
    point_t = t;
    while(*point_s != '\0' && *point_t != '\0') {
      if(*point_s == *point_t) {
        point_s ++;
        point_t ++;
      }
      else {
        point_t ++;
      }
    }
    if(flag ++) {
      printf("\n");
    }
    if(*point_s == '\0') {
      printf("Yes");
    }
    else {
      printf("No");
    }
  }
}
