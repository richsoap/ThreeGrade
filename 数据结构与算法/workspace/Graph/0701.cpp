#include<stdio.h>

struct node{
  int x,y;
  node(int _x = 0,int _y = 0):x(_x),y(_y) {}
};
bool map[100][100];
node stack[100];
int stack_point;
int counter,total;
int dy[] = {-2,-2,-1,-1,1,1,2,2};
int dx[] = {-1,1,-2,2,-2,2,-1,1};

void reset(int w,int h) {
  for(int p = 0;p < w + 4;p ++) {
    map[p][0] = false;
    map[p][1] = false;
    map[p][h+2] = false;
    map[p][h+3] = false;
  }
  for(int q = 2;q < h + 2;q ++) {
    map[0][q] = false;
    map[1][q] = false;
    map[w+2][q] = false;
    map[w+3][q] = false;
  }
  for(int p = 2;p < w + 2;p ++) {
    for(int q = 2;q < h + 2;q ++) {
      map[p][q] = true;
    }
  }
}

bool gotoNext(int x,int y) {
  map[x][y] = false;
  counter ++;
  if(counter == total) {
    stack[stack_point ++] = node(x,y);
    return true;
  }
  for(int i = 0;i < 8;i ++) {
    if(map[x + dx[i]][y + dy[i]] && gotoNext(x + dx[i],y + dy[i])) {
      stack[stack_point ++] = node(x,y);
      return true;
    }
  }
  map[x][y] = true;
  counter --;
  return false;
}

void printTrack() {
  while((-- stack_point) >= 0) {
    printf("%c%d",stack[stack_point].y + 'A' - 2,stack[stack_point].x - 1);
  }
  printf("\n");
}

int main() {
  int t;
  int p,q;
  scanf("%d",&t);
  for(int i = 1;i <= t;i ++) {
    scanf("%d %d",&p,&q);
    if(i != 1) {
      printf("\n");
    }
    printf("Scenario #%d:\n",i);
    reset(p,q);
    counter = 0;
    total = p * q;
    stack_point = 0;
    for(int x = 0;x < p && stack_point == 0;x ++) {
      for(int y = 0;y < q;y ++) {
        if(gotoNext(x+2,y+2)) {
          break;
        }
      }
    }
    if(stack_point == total) {
      printTrack();
    }
    else {
      printf("impossible\n");
    }
  }
  return 0;
}

/*
3
1 1
2 3
4 3
*/
