// hopcroft-karp begins

int m, n; // sizes of left and right parts
vector<int> gr[max_n];
int d[max_n];
int par[max_n];
bool used[max_n];


bool bfs() {
    deque<int> q;
    memset(d, -1, sizeof(d));
    for (int i = 0; i < m; i++)
        if (par[i] == -1) {
            q.push_back(i);
            d[i] = 0;
        }
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        if (v >= m){
            if (par[v] != -1 && d[par[v]] == -1) {
                d[par[v]] = d[v];
                q.push_front(par[v]);
            }
            continue;
        }
        for (int x : gr[v]) {
            if (d[x] == -1) {
                d[x] = d[v] + 1;
                q.push_back(x);
            }
        }
    }
    for (int i = m; i < n + m; i++)
        if (par[i] == -1 && d[i] != -1)
            return true;
    return false;
}

int dfs(int v) {
    used[v] = true;
    for (int to : gr[v]) {
        if (par[to] == -1 || (d[par[to]] == d[v] + 1 && !used[par[to]] && dfs(par[to]))){
            par[v] = to;
            par[to] = v;
            return 1;
        }
    }
    return 0;
}

fill(par, par + max_n, -1);
int ans = 0;
while (bfs()){
    memset(used, 0, sizeof(used));
    for (int i = 0; i < m; i++)
        if (par[i] == -1) {
            ans += dfs(i);
            //cout << n << " " << m << " " << i << endl;
        }
}

// hopcroft-karp ends
