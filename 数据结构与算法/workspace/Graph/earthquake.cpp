#include<stdio.h>
#include<math.h>
#include<list>
struct country{
  int x,y;
  std::list<int> nearby;
  country(int _x = 0,int _y = 0):x(_x),y(_y) {}
  double operator - (const country& _country) {
      return sqrt((x-_country.x)*(x-_country.x)+(y-_country.y)*(y-_country.y));
  }
};

country map[110];
bool been[110];
double dic[110][110];
int outList[110];

int main() {
  int N,M,a,b;
  double allDic;
  int counter;
  int minDic;
  int minLoc;
  while(scanf("%d %d",&N,&M )!=EOF) {
    for(int i = 1;i <= N;i ++) {
      map[i].nearby.clear();
      been[i] = false;
      outList[i] = 0;
    }
    outList[0] = 1;
    allDic = 0;
    been[1] = true;
    for(int i = 0;i < M;i ++) {
      scanf("%d %d",&a,&b);
      map[a].nearby.push_back(b);
      map[b].nearby.push_back(a);
      dic[a][b] = dic[b][a] = map[a] - map[b];
    }//建立距离表
    for(counter = 0;counter < N - 1;counter ++) {
      if(outList[counter] == 0)
        break;//如果上一次循环没有更新outList，则说明该图不连通
      minDic = -1;
      for(int i = 0;i <= counter;i ++) {
        for()
      }
    }
  }
}
