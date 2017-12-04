#include<stdio.h>
#include<stack>

int dic[30][30];

bool cmpStr(const char* stra,const char* strb) {
  int i;
  for(i = 0;stra[i] != '\0' && strb[i] != '\0';i ++) {
    if(stra[i] != strb[i])
      break;
  }
  if(stra[i] == '\0' && strb[i] == '\0')
    return true;
  else
    return false;
}

int getIndex(char** dictionary,char* target,int length) {
  for(int i = 0;i < length;i ++) {
    if(cmpStr(dictionary[i],target))
      return i;
  }
  return -1;
}

void getTrace(int from,int to,int * result,int length) {
  int* tempDic = new int[length];
  int minDic;
  int minLoc;
  for(int i = 0;i < length;i ++) {
    tempDic[i] = dic[from][i];
    if(tempDic[i] > 0)
      result[i] = from;
    else
      result[i] = -1;
  }
  result[from] = -2;
  for(int i = 0;i < length;i ++) {
    minDic = -1;
    minLoc = -1;
    for(int p = 0;p < length;p ++) {
      if(tempDic[p] > 0 && (minDic > tempDic[p] || minDic < 0)) {
        minDic = tempDic[p];
        minLoc = p;
      }
    }
    if(minLoc == to) {
      return;
    }
    tempDic[minLoc] = -2;
    for(int q = 0;q < length;q ++) {
      if(dic[minLoc][q] != -1) {
        if(result[q] == -1) {
          tempDic[q] = minDic + dic[minLoc][q];
          result[q] = minLoc;
        }
        else if(result[q] >= 0 && tempDic[q] > minDic + dic[minLoc][q]) {
          tempDic[q] = minDic + dic[minLoc][q];
          result[q] = minLoc;
        }
      }
    }
  }
}

int main() {
  char** map = new char*[30];
  char* stra = new char[50];
  char* strb = new char[50];
  int* result = new int[30];
  int P;
  int Q;
  int R;
  int posa;
  int posb;
  int tempDic;
  std::stack<int> resultStack;
  for(int j = 0;j < 50;j ++) {
    for(int k = 0;k < 50;k ++) {
      dic[j][k] = -1;
    }
  }

  scanf("%d",&P);
  for(int i = 0;i < P;i ++) {
    map[i] = new char[51];
    scanf("%s",map[i]);
    dic[i][i] = 0;
  }

  scanf("%d",&Q);
  for(int i = 0;i < Q;i ++) {
    scanf("%s %s %d",stra,strb,&tempDic);
    posa = getIndex(map,stra,P);
    posb = getIndex(map,strb,P);
    dic[posa][posb] = tempDic;
    dic[posb][posa] = tempDic;
  }
  scanf("%d",&R);
  for(int i = 0;i < R;i ++) {
    scanf("%s %s",stra,strb);
    posa = getIndex(map,stra,P);
    posb = getIndex(map,strb,P);
    getTrace(posa,posb,result,P);
    while(posb != posa) {
      resultStack.push(posb);
      posb = result[posb];
    }
    printf(":%s\n",map[posa]);
    while(!resultStack.empty()) {
      printf(":%s\n",map[resultStack.top()]);
      resultStack.pop();
    }
  }
  while(true) {
    if(getchar() == 'q')
      break;
  }
  return 0;
}
