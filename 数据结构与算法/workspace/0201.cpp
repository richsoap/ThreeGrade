#include <stdio.h>
char dic[10000][16];
int indexs[10000];
char word[16];
int flag;

int isMatch(char* temp,int dicloc,int wordloc) {
  while(true) {
    if(temp[dicloc] == '\0' && word[wordloc] == '\0') {
      switch (flag) {
        case 1: return 1;
        case 0: return 2;
      }
    }
    if(temp[dicloc] == word[wordloc]) {
        dicloc ++;
        wordloc ++;
    }
    else if(flag) {
      return 0;
    }
    else {
      flag = 1;
      if(isMatch(temp,dicloc + 1,wordloc) || isMatch(temp, dicloc, wordloc + 1) || isMatch(temp, dicloc + 1, wordloc + 1)) {
        return 1;
      }
      else {
        return 0;
      }
    }
  }
}

int main() {
  int length,state,count;
  int* point;
  char* temp;
  while(scanf("%s",dic[0])) {
    length = 1;
    while(scanf("%s",dic[length])) {
      if(dic[length][0] == '#') {
        break;
      }
      else {
        length ++;
      }
    }
    while(scanf("%s",word)) {
      if(word[0] == '#') {
        break;
      }
      else {
        state = count = 0;
        point = indexs;
        printf("%s",word);
        temp = dic[0];
        for (int i = 0;i < length && state == 0;temp ++,i ++) {
          flag = 0;
          switch (isMatch(temp,0,0)) {
            case 2:
              state = 1;
              break;
            case 1:
              *point = i;
              point ++;
              count ++;
              break;
            default:
              break;
          }
        }
        if(state) {
          printf(" is correct");
        }
        else {
          printf(":");
          point = indexs;
          for(int i = 0;i < count;i ++,point++) {
            printf(" %s",dic[*point]);
          }
        }
        printf("\n");
      }
    }
  }
}
