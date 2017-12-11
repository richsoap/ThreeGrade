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
  return a;
}

bool sameKind(int A,int B) {
  int kindA = getKind(A);
  int kindB = getKind(B);
  if(kindA == kindB)
    return true;
  if(getKind(food[kindA]) != 0 && (getKind(food[kindA]) == kindB || getKind(food[kindA]) == getKind(killer[kindB]))) {
    return false;
  }
  if(getKind(food[kindB]) != 0 && (getKind(food[kindB]) == kindA || getKind(food[kindB]) == getKind(killer[kindA]))) {
    return false;
  }
  kind[kindB] = kindA;
  if(food[kindA] == 0)
    food[kindA] = food[kindB];
  if(killer[kindA] == 0)
    killer[kindA] = killer[kindB];
  kind[getKind(food[kindB])] = kind[getKind(food[kindA])];
  kind[getKind(killer[kindB])] = kind[getKind(killer[kindA])];
  return true;
}

bool killKind(int A,int B) {
  int kindA = getKind(A);
  int kindB = getKind(B);
  if(getKind(food[kindA]) == kindB) {
    return true;
  }

}

int main() {
  int k,operate,animalA,animalB,counter;
  while(scanf("%d %d",&N,&k) != EOF) {
    for(int i = 0;i <= N;i ++) {
      kind[i] = i;
      food[i] = 0;
      killer[i] = 0;
    }
    counter = 0;
    for(int i = 0;i < k;i ++) {
      scanf("%d %d %d",&operate,&animalA,&animalB);
      if(animalA > N || animalB > N) {
        counter ++;
        continue;
      }
      switch (operate) {
        case 2:
          if(!killKind(animalA,animalB))
            counter ++;
          break;
        default:if(!sameKind(animalA,animalB))
          counter ++;
      }
    }
    printf("%d\n",counter);
  }
}
