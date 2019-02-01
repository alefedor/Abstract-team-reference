const ll MOD = ...;
vector<pair<int, int>> rows[MAXN];  // a[i][rows[i][j].first]=rows[i][j].second; b[i]=a[i][n]
vector<ll> res;
int n;

int a[MAXN];
int toZero[MAXN];
int zro[MAXN];
int p[MAXN];
int invP[MAXN];

void subtract(int i, int j, int c) {
    for (auto el: rows[j]) {
        if (a[el.first] == 0) {
            rows[i].push_back({el.first, 0});
        }
        a[el.first] = (a[el.first] + MOD - (c * 1ll * el.second) % MOD) % MOD;
    }
    rows[i].erase(
            std::remove_if(rows[i].begin(), rows[i].end(),
                           [](const pair<int, int>& p) { return a[p.first] == 0; }),
            rows[i].end());
}

void mul(int i, int c) {
    for (auto& el: rows[i]) {
        el.second = (a[el.first] * 1ll * c) % MOD;
        a[el.first] = 0;
    }
    rows[i].erase(
            std::remove_if(rows[i].begin(), rows[i].end(),
                           [](const pair<int, int>& p) { return p.second == 0; }),
            rows[i].end());
}

void sortRows() {
    for (int i = 0; i <= n; i++) {
        p[i] = i;
        toZero[i] = -1;
    }
    sort(p, p + n, [](int i, int j) { return rows[i].size() < rows[j].size(); });
    vector<vector<pair<int, int>>> rs(n);
    for (int i = 0; i < n; i++) {
        invP[p[i]] = i;
        rs[i] = rows[p[i]];
    }
    for (int i = 0; i < n; i++) {
        rows[i] = rs[i];
        for (auto& el: rows[i]) {
            if (el.first < n) {
                el.first = invP[el.first];
            }
        }
    }
}

void gauss() {
    sortRows();
    for (int i = 0; i < n; i++) {
        for (auto& el: rows[i]) {
            a[el.first] = el.second;
        }
        while (1) {
            int k = -1;
            for (auto& el: rows[i]) {
                if (a[el.first] != 0 && toZero[el.first] != -1 &&
                    (k == -1 || toZero[el.first] < toZero[k])) {
                    k = el.first;
                }
            }
            if (k == -1) {
                break;
            }
            subtract(i, toZero[k], a[k]);
        }
        bool ok = false;
        for (auto& el: rows[i]) {
            if (el.first < n && a[el.first] != 0) {
                toZero[el.first] = i;
                zro[i] = el.first;
//                det = (det * a[el.first]) % MOD;
                mul(i, divM(1, a[el.first]));
                ok = true;
                break;
            }
        }
        if (!ok) {
            res[0] = -1;
//            det = 0;
            return;
        }
    }
    res[n] = MOD - 1;
    for (int i = n - 1; i >= 0; i--) {
        int k = zro[i];
        for (auto& el : rows[i]) {
            if (el.first != k) {
                res[p[k]] += (MOD - (el.second * res[p[el.first]]) % MOD);
                res[p[k]] %= MOD;
            }
        }
    }
}
