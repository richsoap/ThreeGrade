#include <stdio.h>

int tree[50010];

int getRoot(int j) {
	if(0 == tree[j])
	  return j;
	tree[j] = getRoot(tree[j]);
	return tree[j];
}

bool isSameParent(int j,int k) {
	j = getRoot(j);
	k = getRoot(k);
	if(j == k)
	  return true;
	else {
	  tree[j] = k;
	  return false;
	}
}

int main() {
	int m,n,count,j,k,cases;
	cases = 1;
	while(true) {
		scanf("%d %d",&n,&m);
		if(m == 0 && n == 0) {
			return 0;
		}
		for(int i = 1;i <= n;i ++) {
			tree[i] = 0;
		}
		count = 0;
		while(m --) {
			scanf("%d %d",&j,&k);
			if(!isSameParent(j,k))
			  count ++;
		}
		printf("Case %d: %d\n",cases ++,n - count);
	}
}
