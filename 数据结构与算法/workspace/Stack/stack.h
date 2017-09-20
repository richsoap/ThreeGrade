# include<stdio.h>
template <class T> class stack{
  private:int count;
  int size;
  T* buffer;
  public:
  stack<T>(int _size = 30):size(_size),count(0) {
    buffer = new T[size];
  }
  ~stack<T>() {
    delete buffer;
  }
  bool push(T value) {
    if(count == size)
      return false;
    else
      buffer[count ++] = value;
  }
  T pop() {
    if(count)
      return buffer[count--];
    else
      return NULL;
  }
  T top() {
    if(count)
      return buffer[count - 1];
    else
      return NULL;
  }
  bool isEmpty() {
    return count;
  }
};
