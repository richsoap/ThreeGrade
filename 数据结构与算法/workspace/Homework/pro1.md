#  第一次作业
1. 高度=[$log_2(510+1)]=8$<br/>
n=m+1
2.
int been[28];//是否已经读取过该字母
int loc[26];//字母位置映射表
char bef[26];//前序
char mid[26];//中序
int length;//长度
int point;//指针
void seek() {
  char word = bef[point ++];
  if(point == length)
    return;
  been[loc[word -'A']] = 1;//设置当前位置已经来过
  switch(been[loc[word -'A'] + 1] + been[loc[word - 'A'] - 1]) {
    case 0:
      seek();//左右两边都有子树
    case 1:
      seek();//只有一边有子树
    default:
      printf(word);//最后输出本节点的值
  }
}

int main() {
  scanf(bef);//输入前序遍历
  sacnf(mid);//输入中序遍历
  length = bef.length;
  been = 0;//been数组全令为false
  been[0] = been[27] = 1;//防止越界
  for(word in mid,int i = 1) {
    loc[word-'A'] = i ++;//建立中序遍历的字母位置映射表
  }
  point = 0;
  seek();
  return 0;
}

3. 哈夫曼树只有二度结点和零度结点，其中零度节点n个，则有2n个空指针域
4. 哈夫曼编码后，最短的一位，最长的四位，总长201位。等长编码每个字母需要3位，共有111个字母，总空间333位。
111
47 24 J
F G 15 E B H
A C 4
K I
5. 不成立，因为只能确定左边集合的结点比其所在子树的根节点的父节点小，但不能保证比根结点的父节点的父节点还小；对于右边的集合，也只能确定其比所在子树的根结点的父节点大，而不一定比根结点的父节点的父节点大。所以不成立。

6. 六次{97,76,65,49,49,13,27,38}

97
 76  65
49 49 13 27
38

111111

# 第二次作业
1. （1）9（2）$\frac{m-1}{k-1}$(3)h(4)$2^k,2^{k+1}-1$
2. （1）每层节点数均为上层节点数*k，则，第i层有$k*{i-1}$个结点
（2）设i为第q层的第n个结点，则$i=\frac{1-k^q}{1-k}+n$，则其第m个子结点的编号为$a=\frac{1-k^{1+q}}{1-k}+k(n-1)+m$，将i的表达式带入得，a=k(i-1)+m+1
（3）每层最右边的结点没有右兄弟结点，设其位于第m层，则其编号为$\frac{1-K^{m+1}}{1-K}$，即，$i\neq\frac{1-K^q}{1-K}$,q为任意正整数时，没有右兄弟结点，否则都有，编号为i+1

5.
int GetDepth(Ptree t) {
int depth[t.length];
for(i in depth) {
  i = -1;
}
depth[0] = 0;
for(i in Ptree) {
  if(i != 0) {
    depth[i] = depth[Ptree[i].parent] + 1;
  }
}
return max(depth);
}
