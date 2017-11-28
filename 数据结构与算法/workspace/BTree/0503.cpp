#include <algorithm>
#include <stdio.h>
using namespace std;
class node{
  public:
    long int x,y,c;

  public:
  node(long int _x = 0,long int _y = 0,long int _c = 0):x(_x),y(_y),c(_c) {}
  bool operator < (const node& n) {
    if(y == n.y) {
      return c < n.c;
    }
    else
      return y < n.y;
  }
};

bool cmp(const node& n1,const node& n2) {
  return n1.x < n2.x;
}
int main() {
  int maxBrightness,tempBrightness,n,w,h,x,y,c,subN;
  int pointFro,pointBeh,subPoint,p,q;
  node* buffer = new node[10010];
  node* subBuffer = new node[20010];
  while(scanf("%d %d %d",&n,&w,&h) != EOF) {
    maxBrightness = 0;
    for(int i = 0;i < n;i ++) {
      scanf("%ld %ld %ld",&(buffer[i].x),&(buffer[i].y),&(buffer[i].c));
    }
    sort(buffer,buffer + n,cmp);//read and sort data
    for(pointFro = pointBeh = 0;pointBeh < n;) {
      while(pointBeh < n && buffer[pointBeh].x - buffer[pointFro].x < w) {
        pointBeh ++;
      }//move right point to the limit location
      subN = pointBeh - pointFro;
      tempBrightness = 0;
      for(int i = 0,p = pointFro,q=subN;i < subN;i ++,p++,q++) {
        subBuffer[i] = buffer[p];
        subBuffer[q].y = subBuffer[i].y + h;
        subBuffer[q].c = -subBuffer[i].c;
      }
      sort(subBuffer,subBuffer + 2*subN);
      tempBrightness = 0;
      for(subPoint = 0;subPoint < 2 * subN;subPoint ++) {
        tempBrightness += subBuffer[subPoint].c;
        maxBrightness = tempBrightness>maxBrightness?tempBrightness:maxBrightness;
      }
      while(buffer[pointBeh].x - buffer[pointFro].x >= w) {
        pointFro ++;
      }
    }
    printf("%d\n",maxBrightness);
  }
}
