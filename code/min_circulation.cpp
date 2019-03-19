// slow min circulation begins

struct Edge {
  int a;
  int b;
  int cost;
};

vector<int> negative_cycle(int n, vector<Edge> &edges) {
  // O(nm), return ids of edges in negative cycle

  vector<int> d(n);
  vector<int> p(n, -1); // last edge ids

  const int inf = 1e9;

  int x = -1;
  for (int i = 0; i < n; i++) {
    x = -1;
    for (int j = 0; j < edges.size(); j++) {
      Edge &e = edges[j];

      if (d[e.b] > d[e.a] + e.cost) {
        d[e.b] = max(-inf, d[e.a] + e.cost);
        p[e.b] = j;
        x = e.b;
      }
    }
  }

  if (x == -1)
    return vector<int>(); // no negative cycle

  for (int i = 0; i < n; i++)
    x = edges[p[x]].a;

  vector<int> result;
  for (int cur = x; ; cur = edges[p[cur]].a) {
    if (cur == x && result.size() > 0) break;
    result.push_back(p[cur]);
  }
  reverse(result.begin(), result.end());

  return result;
}

vector<int> min_avg_cycle(int n, vector<Edge> &edges) {
  const int inf = 1e3;

  for (auto &e : edges)
    e.cost *= n * n;

  int l = -inf;
  int r = inf;
  while (l + 1 < r) {
    int m = (l + r) / 2;
    for (auto &e : edges)
      e.cost -= m;

    if (negative_cycle(n, edges).empty())
      l = m;
    else
      r = m;

    for (auto &e : edges)
      e.cost += m;
  }

  if (r >= 0) // if only negative needed
    return vector<int>();

  for (auto &e : edges)
    e.cost -= r;

  vector<int> result = negative_cycle(n, edges);


  for (auto &e : edges)
    e.cost += r;

  for (auto &e : edges)
    e.cost /= n * n;

  return result;
}

struct edge {
  int from, to;
  int c, f, cost;
};

const int max_n = 200;

vector<int> gr[max_n];
vector<edge> edges;

void add(int fr, int to, int c, int cost) {
  gr[fr].push_back(edges.size());
  edges.push_back({fr, to, c, 0, cost});
  gr[to].push_back(edges.size());
  edges.push_back({to, fr, 0, 0, -cost}); // single
}

void calc_min_circulation(int n) {
  while (true) {
    vector<Edge> eds;
    vector<int> origin;

    for (int i = 0; i < edges.size(); i++) {
      edge &e = edges[i];
      if (e.c - e.f > 0) {
        eds.push_back({e.from, e.to, e.cost});
        origin.push_back(i);
      }
    }

    vector<int> cycle = negative_cycle(n, eds);

    if (cycle.empty())
      break;

    for (auto id : cycle) {
      int x = origin[id];
      edges[x].f += 1;
      edges[x ^ 1].f -= 1;
    }
  }
}

// slow min circulation ends
