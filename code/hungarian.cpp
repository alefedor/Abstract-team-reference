// bad hungarian begins

fill(par, par + 301, -1);
fill(par2, par2 + 301, -1);

int ans = 0;
for (int v = 0; v < n; v++){
  memset(useda, false, sizeof(useda));
  memset(usedb, false, sizeof(usedb));
  useda[v] = true;
  for (int i = 0; i < n; i++)
    w[i] = make_pair(a[v][i] + row[v] + col[i], v);
  memset(prev, 0, sizeof(prev));
  int pos;
  while (true){
    pair<pair<int, int>, int> p = make_pair(make_pair(1e9, 1e9), 1e9);
    for (int i = 0; i < n; i++)
      if (!usedb[i])
        p = min(p, make_pair(w[i], i));
    for (int i = 0; i < n; i++)
      if (!useda[i])
        row[i] += p.first.first;
    for (int i = 0; i < n; i++)
      if (!usedb[i]){
        col[i] -= p.first.first;
        w[i].first -= p.first.first;
      }
    ans += p.first.first;
    usedb[p.second] = true;
    prev[p.second] = p.first.second; //из второй в первую
    int x = par[p.second];
    if (x == -1){
      pos = p.second;
      break;
    }
    useda[x] = true;
    for (int j = 0; j < n; j++)
      w[j] = min(w[j], {a[x][j] + row[x] + col[j], x});

  }
  while (pos != -1){
    int nxt = par2[prev[pos]];
    par[pos] = prev[pos];
    par2[prev[pos]] = pos;
    pos = nxt;
  }
}
cout << ans << "\n";
for (int i = 0; i < n; i++)
  cout << par[i] + 1 << " " << i + 1 << "\n";
  
// bad hungarian ends 
