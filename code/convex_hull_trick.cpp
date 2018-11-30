struct line {
    ll k, b;
    ll at(ll x) const {
        return k * x + b;
    }
};
 double intersec(line a, line b) {
    return 1.0 * (b.b - a.b) / (a.k - b.k);
}
 struct convex_hull_trick {
    vector<double> x = {-1e18};
    vector<line> lines;
     void add(line l) {
        // l.k increasing
        if (lines.empty()) {
            lines.pb(l);
        } else {
            while (lines.size() > 1 && intersec(l, lines[lines.size() - 2]) < x.back()) {
                lines.pop_back();
                x.pop_back();
            }
            x.push_back(intersec(l, lines.back()));
            lines.push_back(l);
        }
    }
};
 struct cht_forward_iterator {
    int ci = 0;
     ll promote(const convex_hull_trick& cht, ll value) {
        while (ci < (int)cht.x.size() - 1 && cht.x[ci + 1] < value)
            ci++;
        return cht.lines[ci].at(value);
    }
};
 const int g = 275;
 struct sqrt_dec {
    struct block {
        vector<int> bs;
        convex_hull_trick cht;
        cht_forward_iterator it;
         block(vector<int> b) {
            bs = b;
            int k = b.size();
            forn(i, k) {
                cht.add({ b[i], 1ll * b[i] * (k - i) });
            }
        }
         ll value(ll x) {
            if (cht.lines.empty())
                return 0;
            return it.promote(cht, x);
        }
    };
     void insert(block& bl, int b) {
        auto v = std::move(bl.bs);
        v.insert(lower_bound(all(v), b), b);
        bl = block(std::move(v));
    }
     vector<block> blocks;
     sqrt_dec(int n) {
        blocks.resize((n + g - 1) / g, block({}));
    }
     void add(int i, int b) {
        insert(blocks[i / g], b);
    }
     ll get_max() {
        int sm = 0;
        ll ans = 0;
        for (int i = blocks.size() - 1; i >= 0; i--) {
            ans = max(ans, blocks[i].value(sm));
            sm += blocks[i].bs.size();
        }
        return ans;
    }
};
