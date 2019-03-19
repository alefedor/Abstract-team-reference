// min-cost flow begins

long long ans = 0;
int mx = 2 * n + 2;

memset(upd, 0, sizeof(upd));
for (int i = 0; i < mx; i++)
    dist[i] = inf;
dist[st] = 0;
queue<int> q;
q.push(st);
upd[st] = 1;
while (!q.empty()){
    int v = q.front();
    q.pop();
    if (upd[v]){
        for (int x : gr[v])	{
            edge &e = edges[x];
            if (e.c - e.f > 0 && dist[v] != inf && dist[e.to] > dist[v] + e.w) {
                dist[e.to] = dist[v] + e.w;
                if (!upd[e.to])
                    q.push(e.to);
                upd[e.to] = true;
                p[e.to] = x;
            }
        }
        upd[v] = false;
    }
}

for (int i = 0; i < k; i++){
    for (int i = 0; i < mx; i++)
        d[i] = inf;
    d[st] = 0;
    memset(used, false, sizeof(used));
    set<pair<int, int> > s;
    s.insert(make_pair(0, st));
    for (int i = 0; i < mx; i++){
        int x;
        while (!s.empty() && used[(s.begin() -> second)]){
            s.erase(s.begin());
        }
        if (s.empty())
            break;
        x = s.begin() -> second;
        used[x] = true;
        s.erase(s.begin());
        for (int i = 0; i < gr[x].size(); i++){
            edge &e = edges[gr[x][i]];
            if (!used[e.to] && e.c - e.f > 0){
                if (d[e.to] > d[x] + (e.c - e.f) * e.w + dist[x] - dist[e.to]){
                    d[e.to] = d[x] + (e.c - e.f) * e.w + dist[x] - dist[e.to];
                    p[e.to] = gr[x][i];
                    s.insert(make_pair(d[e.to], e.to));
                }
            }
        }
        dist[x] += d[x];
    }
    int pos = t;
    while (pos != st){
	    int id = p[pos];
	    edges[id].f += 1;
        edges[id ^ 1].f -= 1;
        pos = edges[id].from;
    }
}

// min-cost flow ends
