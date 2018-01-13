#include <fstream>
#include <sstream>
using namespace std;
int main(int argc, char** argv) {
  if(argc == 1) {
    printf("This function is used to reshape caffemodle, which has too many channels for wino_conv_wrapper\n usage:filename input_channel output_channel");
    return 0;
  }
  else if(argc != 4) {
    printf("Wrong input.\n");
    return 1;
  }
  char* name = argv[1];
  stringstream ss;
  ss<<argv[2];
  int input_channel;
  ss>>input_channel;
  int output_channel;
  ss<<argv[3];
  ss>>output_channel;
  uint16_t* buffer = (uint16_t*)malloc(input_channel*output_channel*3*3*sizeof(uint16_t));
  uint16_t** points = (uint16_t**)malloc(input_channel*output_channel/64*sizeof(uint16_t*));
  uint16_t** result = (uint16_t**)malloc(input_channel*output_channel/64*sizeof(uint16_t*));
  ifstream putin_file;
  ofstream output_file;
  putin_file.open(name,ios::binary);
  if(!putin_file) {
    printf("cannot open file %s\n",name);
    return 1;
  }
  for(int  i = 0;i < input_channel*output_channel/64;i ++) {
    points[i] = buffer + i*3*3*64;
    putin_file.read((char*)points[i],3*3*64*sizeof(uint16_t));
  }
  putin_file.close();
  for(int p = 0;p < input_channel / 64;p ++) {
    for(int q = 0;q < output_channel/64;q ++) {
      for(int index = 0;index < 64;index ++) {
        result[index+q*64+p*output_channel] = points[index*output_channel/64 +  q + p*output_channel];
      }
    }
  }
  output_file.open(name,ios::binary|ios::out);
  if(!output_file) {
    printf("output error\n");
    return 1;
  }
  for(int i = 0;i < input_channel*output_channel/64;i ++) {
    output_file.write((char*)result[i],3*3*sizeof(uint16_t)*64);
  }
  free(buffer);
  free(points);
  free(result);
  return 0;
}
