struct node{
  Value value;
  int count;
  node(Value _value = 0,int _count = 0):value(_value),count(_count) {}
}

node* merge(Value* input,int n,int k) {
  node* output;
  int count = 0;
  SearchCountTree<Node> sc_tree = SearchCountTree<Node>();
  for(int i = 0;i < n;i ++) {
    sc_tree.insert(input[i]);
  }
  output = sc_tree.front();
  return output;
}

Value* expand(node* input,int n,int k) {
  Value* output = new Value[n];
  int point = 0;
  for(int i = 0;i < k;i ++) {
    for(int p = 0;p < input[k].count;p ++) {
      output[point ++] = input[k].value;
    }
  }
  return output;
}

int getNOk(int* input,int start,int end,int k) {
  int tempValue = input[start];
  int p = start;
  int q = end - 1;
  for(;p > q;p --) {
    if(input[p] < tempValue) {
      input[q] = input[p];
      for(;q < p;q ++) {
        if(input[q] > tempValue) {
          input[p] = input[q];
          break;
        }
      }
    }
  }
  if(p == k) 
    return input[k];
  else if(p < k)
    return getNOK(input,p,end,k);
  else
    return getNOK(input,start,p,k);
}
