// bad suffix automaton begins

struct node{
  map<char, int> go;
  int len, suff;
  long long sum_in;
  node(){}
};

node v[max_n * 4];

int add_node(int max_len){
  //v[number].sum_in = 0;
  v[number].len = max_len;
  v[number].suff = -1;
  number++;
  return number - 1;
}

int last = add_node(0);

void add_char(char c) {
  int cur = last;
  int new_node = add_node(v[cur].len + 1);
  last = new_node;
  while (cur != -1){
    if (v[cur].go.count(c) == 0){
      v[cur].go[c] = new_node;
      //v[new_node].sum_in += v[cur].sum_in;
      cur = v[cur].suff;
      if (cur == -1)
        v[new_node].suff = 0;
    }else{
      int a = v[cur].go[c];
      if (v[a].len == v[cur].len + 1){
        v[new_node].suff = a;
      }else{
        int b = add_node(v[cur].len + 1);
        v[b].go = v[a].go;
        v[b].suff = v[a].suff;
        v[new_node].suff = b;
        while (cur != -1 && v[cur].go.count(c) != 0 && v[cur].go[c] == a){
          v[cur].go[c] = b;
          //v[a].sum_in -= v[cur].sum_in;
          //v[b].sum_in += v[cur].sum_in;
          cur = v[cur].suff;
        }
        v[a].suff = b;
      }
      return;
    }
  }
}

// bad suffix automaton ends

