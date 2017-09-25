#include <stdio.h>
int main() {
    int map[16][16];
    map[0][0]  = 1;
    for(int p = 1;p < 16;p ++) {
      map[p][0] = map[p-1][0];
      for(int q = 1;q < p;q ++) {
        map[p][q] = map[p-1][q] + map[p][q-1];
      }
      map[p][p] = map[p][p-1];
    }
    int N;
    scanf("%d",&N );
    printf("%d", map[N][N]);
    return 0;
}
