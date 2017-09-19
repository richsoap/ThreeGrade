#include <stdio.h>
#include <string>
#include <map>
using namespace std;
string keys[] = {"negative","zero","one","two","three","four","five","six","seven","eight","nine","ten","eleven",
                "twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen","twenty",
                "thirty","forty","fifty","sixty","seventy","eighty","ninety","hundred","thousand","million"};
int values[] = {-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,30,40,50,60,70,80,90,-100,-1000,-1000000};
int main() {
  map<string,int> dictionary;
  for(int i = 0;i < 32;i ++) {
    dictionary.insert(pair<string,int>(keys[i],values[i]));
  }
  char* buffer = new char[40];
  char* start;
  char* end;
  int flag;
  while(scanf("%s\n"),buffer) {
    for(end = buffer;(*end) != '\0';end ++) {
      if(*end == ' ') {
        *end = '\0';
        end ++;
      }
    }
    flag = 0;
    for(start = buffer;start != end;start ++) {
      if(*start == '\0') {
        flag = 0;
      }
      else if(flag == 0) {
        printf("%s:",start );
        printf("%d ",dictionary.find(start)->second);
      }
    }
  }
}
