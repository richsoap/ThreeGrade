#include <algorithm>
#include <stdio.h>
using namespace std;
class node{
  public:
    int x,y,c;

  public:
  node(int _x = 0,int _y = 0,int _c = 0):x(_x),y(_y),c(_c) {}
  bool operator < (const node& n) {
    return y < n.y;
  }
};

bool cmp(const node& n1,const node& n2) {
  return n1.x < n2.x;
}
int main() {
  int maxBrightness,tempBrightness,n,w,h,x,y,c,subN;
  int pointFro,pointBeh,subPointFro,subPointBeh;
  node* buffer = new node[10001];
  node* subBuffer = new node[10001];
  while(scanf("%d %d %d",&n,&w,&h) != EOF) {
    maxBrightness = 0;
    for(int i = 0;i < n;i ++) {
      scanf("%d %d %d",&x,&y,&c);
      buffer[i] = node(x,y,c);
    }
    sort(buffer,buffer + n,cmp);//read and sort data
    for(pointFro = pointBeh = 0;pointBeh <= n;) {
      printf("out\n");
      while(pointBeh <= n && buffer[pointBeh].x - buffer[pointFro].x < w) {
        pointBeh ++;
        printf("move right\n");
      }//move right point to the limit location
      subN = pointBeh - pointFro;
      tempBrightness = 0;
      for(int i = 0;i < subN;i ++) {
        subBuffer[i] = buffer[i + pointFro];
        tempBrightness += buffer[i].c;
      }
      if(tempBrightness <= maxBrightness) {
        continue;
      }//if all of the brightness is less than maxBrightness,continue
      sort(subBuffer,subBuffer + subN);
      tempBrightness = 0;
      for(subPointFro = subPointBeh = 0;subPointBeh <= subN;) {
        printf("in\n");
        while(subPointBeh <= subN && subBuffer[subPointBeh].y - subBuffer[subPointFro].y < h) {
          subPointBeh ++;
          printf("move subright\n");
          tempBrightness += subBuffer[subPointBeh].c;
        }
        maxBrightness = tempBrightness>maxBrightness?tempBrightness:maxBrightness;
        while(subBuffer[subPointBeh].y - subBuffer[subPointFro].y >= h) {
          tempBrightness -= subBuffer[subPointFro].c;
          subPointFro ++;
          printf("move subleft\n");
        }
      }
      while(buffer[pointBeh].x - buffer[pointFro].x >= w) {
        pointFro ++;
        printf("move left\n");
      }
    }
    printf("%d\n",maxBrightness);
  }
}
