#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;
struct time{
  int h,m;
  time(int _h = 0,int _m = 0):h(_h),m(_m) {}
  int operator -(const time& _time) {
    int result = m - _time.m;
    result += 60*(h + _time.h);
    return result;
  }
  void endTime () {
    m += 29;
    h += m/60;
    m %= 60;
  }
};
int main() {
  list<time> queue[3];
  int temp,index;
  int limit[3];
  int count,deltaTime;
  time tempTime;
  char* buffer = new char[20];
  while(true) {
    scanf("%d %d %d",limit,limit+1,limit+2);
    if(!(limit[0] || limit[1] || limit[2])) {
      return 0;
    }
    count = 0;
    while(true) {
      cin.getline(buffer,15);
      if(buffer[0] == '#') {
        break;
      }
      temp = buffer[0] - '0';
      temp *= 10;
      temp += buffer[1] - '0';
      tempTime.h = temp;
      temp = buffer[3] - '0';
      temp *= 10;
      temp += buffer[4] - '0';
      tempTime.m = temp;
      index = (buffer[6] - '0')/2 + (buffer[6] - '0')%2 - 1;

      if(queue[index].size() < (unsigned)limit[index]) {
        tempTime.endTime();
        queue[index].push_back(tempTime);
        count += index + 1;
      }
      else {
        deltaTime = queue[index].front() - tempTime;
        if(deltaTime < 0) {
          queue[index].pop_front();
          queue[index].push_back(tempTime);
          count += index + 1;
        }
        else {
          
        }
      }
    }
  }
}
