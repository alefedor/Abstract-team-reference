// planar begins

// обход граней
int n; // число вершин
vector < vector<int> > g; // граф 
vector < vector<char> > used (n);
for (int i=0; i<n; ++i)
  used[i].resize (g[i].size());
for (int i=0; i<n; ++i)
  for (size_t j=0; j<g[i].size(); ++j)
    if (!used[i][j]) {
      used[i][j] = true;
      int v = g[i][j],  pv = i;
      vector<int> facet;
      for (;;) {
        facet.push_back (v);
        vector<int>::iterator it = find (g[v].begin(), g[v].end(), pv);
        //vector<int>::iterator it = lower_bound(g[v].begin(), g[v].end(), pv, cmp_ang(v));
        // cmp_ang(v) -- true, если меньше полярный угол относ v
        if (++it == g[v].end())  it = g[v].begin();
        if (used[v][it-g[v].begin()])  break;
        used[v][it-g[v].begin()] = true;
        pv = v,  v = *it;
      }
      ... вывод facet - текущей грани ...
    }

// построение планарного графа
struct point {
  double x, y;
  bool operator< (const point & p) const {
    return x < p.x - EPS || abs (x - p.x) < EPS && y < p.y - EPS;
  }
};
 
map<point,int> ids;
vector<point> p;
vector < vector<int> > g;
 
int get_point_id (point pt) {
  if (!ids.count(pt)) {
    ids[pt] = (int)p.size();
    p.push_back (pt);
    g.resize (g.size() + 1);
  }
  return ids[p];
}
 
void intersect (pair<point,point> a, pair<point,point> b, vector<point> & res) {
  ... стандартная процедура, пересекает два отрезка a и b и закидывает результат в res ...
  ... если отрезки перекрываются, то закидывает те концы, которые попали внутрь первого отрезка ...
}
 
int main() {
  // входные данные
  int m;
  vector < pair<point,point> > a (m);
  ... чтение ...
 
  // построение графа
  for (int i=0; i<m; ++i) {
    vector<point> cur;
    for (int j=0; j<m; ++j)
      intersect (a[i], a[j], cur);
    sort (cur.begin(), cur.end());
    for (size_t j=0; j+1<cur.size(); ++j) {
      int x = get_id (cur[j]),  y = get_id (cur[j+1]);
      if (x != y) {
        g[x].push_back (y);
        g[y].push_back (x);
      }
    }
  }
  int n = (int) g.size();
  // сортировка по углу и удаление кратных рёбер
  for (int i=0; i<n; ++i) {
    sort (g[i].begin(), g[i].end(), cmp_ang (i));
    g[i].erase (unique (g[i].begin(), g[i].end()), g[i].end());
  }
}        
// planar ends    
