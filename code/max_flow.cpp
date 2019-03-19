// max flow begins

struct edge{
    int from, to;
    int c, f, num;
    edge(int from, int to, int c, int num):from(from), to(to), c(c), f(0), num(num){}
    edge(){}
};

const int max_n =  600;

edge eds[150000];
int num = 0;
int it[max_n];
vector<int> gr[max_n];
int s, t;
vector<int> d(max_n);

bool bfs(int k) {
    queue<int> q;
    q.push(s);
    fill(d.begin(), d.end(), -1);
    d[s] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int x : gr[v]) {
            int to = eds[x].to;
            if (d[to] == -1 && eds[x].c - eds[x].f >= (1 << k)){
                d[to] = d[v] + 1;
                q.push(to);
            }
        }
    }

    return (d[t] != -1);
}

int dfs(int v, int flow, int k) {
    if (flow < (1 << k))
        return 0;
    if (v == t)
        return flow;
    for (; it[v] < gr[v].size(); it[v]++) {
        int num = gr[v][it[v]];
        if (d[v] + 1 != d[num].to])
            continue;
        int res = dfs(eds[num].to, min(flow, eds[num].c - eds[num].f), k);
        if (res){
            eds[num].f += res;
            eds[num ^ 1].f -= res;
            return res;
        }
    }
    return 0;
}

void add(int fr, int to, int c, int nm) {
    gr[fr].push_back(num);
    eds[num++] = edge(fr, to, c, nm);
    gr[to].push_back(num);
    eds[num++] = edge(to, fr, 0, nm); //corrected c
}

int ans = 0;
    for (int k = 30; k >= 0; k--)
        while (bfs(k)) {
            memset(it, 0, sizeof(it));
            while (int res = dfs(s, 1e9 + 500, k))
                ans += res;
        }
        
        
// decomposition

int path_num = 0;
vector<int> paths[max_n];
int flows[max_n];

int decomp(int v, int flow) {
    if (flow < 1)
        return 0;
    if (v == t) {
        path_num++;
        flows[path_num - 1] = flow;
        return flow;
    }
    for (int i = 0; i < gr[v].size(); i++) {
        int num = gr[v][i];
        int res = decomp(eds[num].to, min(flow, eds[num].f));
        if (res)  {
            eds[num].f -= res;
            paths[path_num - 1].push_back(eds[num].num);
            return res;
        }
    }
    return 0;
}

while (decomp(s, 1e9 + 5));

// max flow ends

