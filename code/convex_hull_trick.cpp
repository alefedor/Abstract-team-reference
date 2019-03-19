// convex hull trick begins

typedef long long ftype;
typedef complex<ftype> point;
#define x real
#define y imag

ftype dot(point const& a, point const& b) {
    return (conj(a) * b).x();
}

ftype f(point const& a, int x) {
    return dot(a, {compressed[x], 1});
    //return dot(a, {x, 1});
}

int pos = 0;

// (x, y) -> (k, b) -> kb + x
struct li_chao { // for min
    vector<point> line;

    li_chao(int maxn) {
        line.resize(4 * maxn, {0, inf});
    }

    void add_line(int v, int l, int r, int a, int b, point nw) {
        if (r <= a || b <= l) return; // remove if no [a, b) query

        int m = (l + r) >> 1;

        if (!(a <= l && r <= b)) { // remove if no [a, b) query
            add_line(v + v + 1, l, m, a, b, nw);
            add_line(v + v + 2, m, r, a, b, nw);
            return;
        }

        bool lef = f(nw, l) < f(line[v], l);
        bool mid = f(nw, m) < f(line[v], m);

        if (mid) swap(line[v], nw);

        if (l == r - 1)
            return;

        if (lef != mid)
            add_line(v + v + 1, l, m, a, b, nw);
        else
            add_line(v + v + 2, m, r, a, b, nw);
    }

    ftype get(int v, int l, int r, int x) {
        if(l == r - 1)
            return f(line[v], x);
        int m = (l + r) / 2;
        if(x < m) {
            return min(f(line[v], x), get(v + v + 1, l, m, x));
        } else {
            return min(f(line[v], x), get(v + v + 2, m, r, x));
        }
    }

} cdt(maxn);

// convex hull with stack

ftype cross(point a, point b) {
    return (conj(a) * b).y();
}

vector<point> hull, vecs;

void add_line(ftype k, ftype b) {
    point nw = {k, b};
    while(!vecs.empty() && dot(vecs.back(), nw - hull.back()) < 0) {
        hull.pop_back();
        vecs.pop_back();
    }
    if(!hull.empty()) {
        vecs.push_back(1i * (nw - hull.back()));
    }
    hull.push_back(nw);
}

int get(ftype x) {
    point query = {x, 1};
    auto it = lower_bound(vecs.begin(), vecs.end(), query, [](point a, point b) {
        return cross(a, b) > 0;
    });
    return dot(query, hull[it - vecs.begin()]);
}

// convex hull trick ends
