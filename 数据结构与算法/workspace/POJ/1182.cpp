#include<stdio.h>
#include<list>

int N;
int kind[50010];
int food[50010];
int killer[50010];

int getKind(int a) {
  if(a != kind[a]) {
    kind[a] = getKind(kind[a]);
    return kind[a];
  }
  else {
    return a;
  }
}

void printNode(int a) {
  printf("%d is in %d eat %d killed by %d\n",a,getKind(a),getKind(food[getKind(a)]),getKind(killer[getKind(a)]));
}

bool sameKind(int A,int B) {
  int kindA = getKind(A);
  int kindB = getKind(B);
  if(kindA == kindB) {
    return true;
  }
  if((getKind(food[kindA]) == kindB || getKind(food[kindA]) == getKind(killer[kindB]))) {
    return false;
  }
  if((getKind(food[kindB]) == kindA || getKind(food[kindB]) == getKind(killer[kindA]))) {
    return false;
  }
  kind[kindB] = kindA;
  kind[getKind(food[kindB])] = getKind(food[kindA]);
  kind[getKind(killer[kindB])] = getKind(killer[kindA]);
  return true;
}

bool eatKind(int A,int B) {
  int kindA = getKind(A);
  int kindB = getKind(B);
  if(getKind(food[kindA]) == kindB)
  return true;
  if(getKind(killer[kindA]) == kindB || getKind(killer[kindA]) == getKind(killer[kindB])) {
    return false;
  }
  if(getKind(killer[kindB]) == kindA || getKind(killer[kindB]) == getKind(killer[kindA])) {
    return false;
  }
  kind[getKind()]
  return true;
}

int main() {
  int k,operate,animalA,animalB,counter,tempcounter;
  while(scanf("%d %d",&N,&k) != EOF) {
    for(int i = 0;i <= N;i ++) {
      kind[i] = i;
      food[i] = i;
      killer[i] = i;
    }
    counter = 0;
    for(int i = 0;i < k;i ++) {
      scanf("%d %d %d",&operate,&animalA,&animalB);
      if(animalA > N || animalB > N) {
        counter ++;
        continue;
      }
      //tempcounter = counter;
      switch (operate) {
        case 1:
          if(!sameKind(animalA,animalB))
            counter ++;
          break;
        default:
          if(!eatKind(animalA,animalB))
            counter ++;
      }
      /*printNode(animalA);
      printNode(animalB);
      if(tempcounter != counter)
      printf("false\n");
      else
      printf("true\n" );*/
    }
    printf("%d\n",counter);
  }
}
