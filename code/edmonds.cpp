// Edmonds O(n^3) begins

vector<int> gr[MAXN];
int match[MAXN], p[MAXN], base[MAXN], q[MAXN];
bool used[MAXN], blossom[MAXN];
int mark[MAXN];
int C = 1;

int lca(int a, int b) {
    C++;
    for (;;) {
        a = base[a];
        mark[a] = C;
        if (match[a] == -1) break;
        a = p[match[a]];
    }

    for (;;) {
        b = base[b];
        if (mark[b] == C) return b;
        b = p[match[b]];
    }
}

void mark_path(int v, int b, int children) {
    while (base[v] != b) {
        blossom[base[v]] = blossom[base[match[v]]] = true;
        p[v] = children;
        children = match[v];
        v = p[match[v]];
    }
}

int find_path(int root) {
    memset(used, 0, sizeof(used));
    memset(p, -1, sizeof p);
    for (int i = 0; i < N; i++)
        base[i] = i;

    used[root] = true;
    int qh = 0, qt = 0;
    q[qt++] = root;
    while (qh < qt) {
        int v = q[qh++];
        for (int to : gr[v]) {
            if (base[v] == base[to] || match[v] == to) continue;
            if (to == root || match[to] != -1 && p[match[to]] != -1) {
                int curbase = lca(v, to);
                memset(blossom, 0, sizeof(blossom));
                mark_path(v, curbase, to);
                mark_path(to, curbase, v);
                for (int i = 0; i < N; i++)
                    if (blossom[base[i]]) {
                        base[i] = curbase;
                        if (!used[i]) {
                            used[i] = true;
                            q[qt++] = i;
                        }
                    }
            } else if (p[to] == -1) {
                p[to] = v;
                if (match[to] == -1)
                    return to;
                to = match[to];
                used[to] = true;
                q[qt++] = to;
            }
        }
    }

    return -1;
}

memset(match, -1, sizeof match);
    for (int i = 0; i < N; i++) {
        if (match[i] == -1 && !gr[i].empty()) {
            int v = find_path(i);
            while (v != -1) {
                int pv = p[v], ppv = match[pv];
                match[v] = pv; match[pv] = v;
                v = ppv;
            }
        }
    }
    
// Edmonds O(n^3) ends
