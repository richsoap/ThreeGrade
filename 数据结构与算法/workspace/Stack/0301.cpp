#include <stdio.h>
struct myQueue{
  int* buffer;
  int length,countmax,countmin,max,min,count;
  myQueue(int _length = 1):length(_length),countmax(0),countmin(0),max(0),min(0),count(0) {
    buffer = new int[length];
  }
  int getMax() {
    return max;
  }
  int getMin() {
    return min;
  }
  int add(int number) {
    buffer[count++ % length] = number;
    if(count >= length) {
      if(countmax == 0) {
        max = buffer[0];
        for(int i = 1;i < length;i ++) {
          if(max < buffer[i]) {
            max = buffer[i];
            countmax = i;
          }
        }
        countmax = 
      }
    }
  }
}
