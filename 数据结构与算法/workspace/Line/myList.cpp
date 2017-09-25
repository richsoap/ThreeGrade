#include <stdio.h>
struct list{
  static int length;
  list* before;
  list* after;
  int value;
  list(int _value = 0):value(_value),before(NULL),after(NULL) {}
  bool add(int _value) {
    list* point = this->after;
    while(point->after != NULL) {
      point = point->after;
    }
    point->after = new list(_value);
    point->after->before = point;
    return true;
  }
  bool erease(int position) {
    list* point = this->after;
    for(int i = 0;i < position;i ++) {
      if(point == NULL) {
        return false;
      }
      else {
        point = point->after;
      }
    }
    if(point->after == NULL) {
      point->before->after = NULL;
    }
    else {
      point->before->after = point->after;
      point->after->before = point->before;
    }
    delete point;
    return true;
  }
};
