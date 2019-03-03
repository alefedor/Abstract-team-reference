// fast gauss begins

using elem_t = int;
// a[i][rows[i][j].first]=rows[i][j].second; b[i]=a[i][n]
bool gauss(vector<vector<pair<int, elem_t>>> rows, vector<elem_t> &res) {
    int n = rows.size();

    res.resize(n + 1, 0);
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    vector<int> toZero(n + 1, -1);
    vector<int> zro(n + 1);
    vector<elem_t> a(n + 1);

    // optional: sort rows

    sort(p.begin(), p.begin() + n, [&rows](int i, int j) { return rows[i].size() < rows[j].size(); });
    vector<int> invP(n + 1);
    vector<vector<pair<int, elem_t>>> rs(n);
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


    for (int i = 0; i < n; i++) {
        for (auto& el: rows[i]) {
            a[el.first] = el.second;
        }
        while (true) {
            int k = -1;
            for (auto& el: rows[i]) {
                if (!isZero(a[el.first]) && toZero[el.first] != -1 &&
                    (k == -1 || toZero[el.first] < toZero[k])) {
                    k = el.first;
                }
            }
            if (k == -1)
                break;

            int j = toZero[k];
            elem_t c = a[k];

            for (auto el: rows[j]) {
                if (isZero(a[el.first]))
                    rows[i].emplace_back(el.first, 0);
                a[el.first] = sub(a[el.first], mult(c, el.second));
            }

            auto cond = [&a](const pair<int, elem_t>& p) { return isZero(a[p.first]); };

            rows[i].erase(std::remove_if(rows[i].begin(), rows[i].end(), cond), rows[i].end());
        }

        bool ok = false;
        for (auto& el: rows[i]) {
            if (el.first < n && !isZero(a[el.first])) {
                toZero[el.first] = i;
                zro[i] = el.first;
//              det = (det * a[el.first]) % MOD;

                elem_t c = divM(1, a[el.first]);
                for (auto& el: rows[i]) {
                    el.second = mult(a[el.first], c);
                    a[el.first] = 0;
                }

                ok = true;
                break;
            }
        }

        if (!ok) {
//          det = 0;
            return false;
        }
    }

    res[n] = sub(0, 1);
    for (int i = n - 1; i >= 0; i--) {
        int k = zro[i];
        for (auto& el : rows[i])
            if (el.first != k)
                res[p[k]] = sub(res[p[k]], mult(el.second, res[p[el.first]]));
    }

    return true;
}

// fast gauss ends
