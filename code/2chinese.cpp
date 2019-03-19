// 2-chinese begins

template <typename Info>
class DSU {
  public:
    DSU ( int n ) : jump (new int[n]), rank (new int [n]), info (new Info [n]) {
      for (int i = 0; i < n; i++) {
        jump[i] = i;
        rank[i] = 0;
      }
    }
    Info& operator [] ( int x ) {
      return info[get (x)];
    }
    void merge ( int a, int b, const Info &comment ) {
      a = get (a);
      b = get (b);
      if (rank[a] <= rank[b]) {
        jump[a] = b;
        rank[b] += rank[a] == rank[b];
        info[b] = comment;
      } else {
        jump[b] = a;
        info[a] = comment;
      }
    }
  private:
    int *jump, *rank;
    Info *info;

    int get ( int x ) {
      return jump[x] == x ? x : (jump[x] = get (jump[x]));
    }
};


struct Treap {
  int value, add;
  int source, target, height;
  int min_value, min_path;

  Treap *left, *right;

  Treap ( int _source, int _target, int _value ) : value (_value), add (0), source (_source), target (_target) {
    height = rand ();
    min_value = value, min_path = 0;
    left = right = 0;
  }

  Treap& operator += ( int sub ) {
    add += sub;
    return *this;
  }
  
  void push () {
    if (!add)
      return;
    if (left) {
      left->add += add;
    }
    if (right) {
      right->add += add;
    }
    value += add;
    min_value += add;
    add = 0;
  }

  void recalc () {
    min_value = value;
    min_path = 0;
    if (left && left->min_value + left->add < min_value) {
      min_value = left->min_value + left->add;
      min_path = -1;
    }
    if (right && right->min_value + right->add < min_value) {
      min_value = right->min_value + right->add;
      min_path = +1;
    }
  }
};

Treap* treap_merge ( Treap *x, Treap *y ) {
  if (!x)
    return y;
  if (!y)
    return x;
  if (x->height < y->height) {
    x->push ();
    x->right = treap_merge (x->right, y);
    x->recalc ();
    return x;
  } else {
    y->push ();
    y->left = treap_merge (x, y->left);
    y->recalc ();
    return y;
  }
}

Treap* treap_getmin ( Treap *x, int &source, int &target, int &value ) {
  assert (x);
  x->push ();
  if (x->min_path == 0) {
    // memory leak, sorry
    source = x->source;
    target = x->target;
    value = x->value + x->add;
    return treap_merge (x->left, x->right);
  } else if (x->min_path == -1) {
    x->left = treap_getmin (x->left, source, target, value);
    value += x->add;
    x->recalc ();
    return x;
  } else if (x->min_path == +1) {
    x->right = treap_getmin (x->right, source, target, value);
    value += x->add;
    x->recalc ();
    return x;
  } else
    assert (0);
}

Treap* treap_add ( Treap *x, int add ) {
  if (!x)
    return 0;
  return &((*x) += add);
}


int main () {
  int n, m;
  while (scanf ("%d%d", &n, &m) == 2) {
    Treap * g[n + 1];
    for (int i = 0; i <= n; i++)
      g[i] = 0;
    for (int i = 1; i <= n; i++) {
      int a;
      assert (scanf ("%d", &a) == 1);
      g[i] = treap_merge (g[i], new Treap (i, 0, a));
    }
    n++;
    for (int i = 0; i < m; i++) {
      int a, b, c;
      assert (scanf ("%d%d%d", &a, &b, &c) == 3);
      g[b] = treap_merge (g[b], new Treap (b, a, c));
    }
    DSU <pair <int, Treap*> > dsu (n + 1);
    for (int i = 0; i < n; i++) {
      dsu[i] = make_pair (i, g[i]);
    }

    int ans = 0, k = n;
    int jump[2 * n], jump_from[2 * n], parent[2 * n], c[n];
    vector <int> children[2 * n];
    memset (c, 0, sizeof (c[0]) * n);
    memset (parent, -1, sizeof (parent[0]) * 2 * n);
    vector <int> finish;
    for (int i = 0; i < n; i++) {
      if (dsu[i].first == 0)
        continue;
      int u = i;
      c[u] = 1;
      while (true) {
        int source, target, value;
        dsu[u].second = treap_getmin (dsu[u].second, source, target, value);
        if (dsu[target] == dsu[u])
          continue;
        treap_add (dsu[u].second, -value);
        ans += value;
        jump_from[dsu[u].first] = source;
        jump[dsu[u].first] = target;
        if (dsu[target].first == 0)
          break;
        if (!c[target]) {
          c[target] = 1;
          u = target;
          continue;
        }
        assert (k < 2 * n);
        int node = k++, t = target;
        parent[dsu[u].first] = node;
        children[node].push_back (dsu[u].first);
        dsu[u].first = node;
        Treap *v = dsu[u].second;
        while (dsu[t].first != node) {
          int next = jump[dsu[t].first];
          parent[dsu[t].first] = node;
          children[node].push_back (dsu[t].first);
          v = treap_merge (v, dsu[t].second);
          dsu.merge (u, t, make_pair (node, v));
          t = next;
        }
      }
      u = i;
      while (dsu[u].first) {
        int next = jump[dsu[u].first];
        finish.push_back (dsu[u].first);
        dsu.merge (u, 0, make_pair (0, (Treap *)0));
        u = next;
      }
    }
    bool ok[k];
    int res[n];
    memset (ok, 0, sizeof (ok[0]) * k);
    memset (res, -1, sizeof (res[0]) * n);
    function <void (int, int)> add_edge = [&ok, &parent, &res, &n] ( int a, int b ) {
      assert (0 <= a && a < n);
      assert (0 <= b && b < n);
      assert (res[a] == -1);
      res[a] = b;
      while (a != -1 && !ok[a]) {
        ok[a] = true;
        a = parent[a];
      }
    };
    function <void (int)> reach = [&ok, &reach, &children, &jump, &jump_from, &add_edge]( int u ) {
      if (!ok[u])
        add_edge (jump_from[u], jump[u]);
      for (auto x : children[u])
        reach (x);
    };
    for (auto x : finish)
       reach (x);
    printf ("%d\n", ans);
    for (int i = 1; i < n; i++)
      printf ("%d%c", res[i] ? res[i] : -1, "\n "[i < n - 1]);
  }
  return 0;
}

// 2-chinese ends
