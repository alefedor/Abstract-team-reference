// heavy-light begins

int sz[maxn];
 
void dfs_sz(int v, int par = -1) {
    sz[v] = 1;
    for (int x : gr[v])
        if (x != par) {
            dfs_sz(x, v);
            sz[v] += sz[x];
        }
    for (int i = 0; i < gr[v].size(); i++)
        if (gr[v][i] != par)
        if (sz[gr[v][i]] * 2 >= sz[v]) {
            swap(gr[v][i], gr[v][0]);
            break;
        }
}
 
int rev[maxn];
int t_in[maxn];
int upper[maxn];;
int par[maxn];
int dep[maxn];
 
int T = 0;
 
void dfs_build(int v, int uppr, int pr = -1) {
    rev[T] = v;
    t_in[v] = T++;
    dep[v] = pr == -1 ? 0 : dep[pr] + 1;
    par[v] = pr;
    upper[v] = uppr;
 
    bool first = true;
 
    for (int x : gr[v])
        if (x != pr) {
            dfs_build(x, first ? upper[v] : x, v);
            first = false;
        }
}
 
struct interval {
    int l;
    int r;
    bool inv; // should direction be reversed
};
 
// node-weighted hld 
vector<interval> get_path(int a, int b) {
    vector<interval> front;
    vector<interval> back;
 
    while (upper[a] != upper[b]) {
        if (dep[upper[a]] > dep[upper[b]]) {
            front.push_back({t_in[upper[a]], t_in[a], true});
            a = par[upper[a]];
        } else {
            back.push_back({t_in[upper[b]], t_in[b], false});
            b = par[upper[b]];
        }
    }
 
    front.push_back({min(t_in[a], t_in[b]), max(t_in[a], t_in[b]), t_in[a] > t_in[b]});
    // for edge-weighted hld add: "front.back().l++;"
    front.insert(front.end(), back.rbegin(), back.rend());
 
    return front;
}

// heavy-light ends
