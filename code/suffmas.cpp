// suffix array O(n) begins

typedef vector<char> bits;

template<const int end>
void getBuckets(int *s, int *bkt, int n, int K) {
  fill(bkt, bkt + K + 1, 0);
  forn(i, n) bkt[s[i] + !end]++;
  forn(i, K) bkt[i + 1] += bkt[i];
}
void induceSAl(bits &t, int *SA, int *s, int *bkt, int n, int K) {
  getBuckets<0>(s, bkt, n, K);
  forn(i, n) {
    int j = SA[i] - 1;
    if (j >= 0 && !t[j])
      SA[bkt[s[j]]++] = j;
  }
}
void induceSAs(bits &t, int *SA, int *s, int *bkt, int n, int K) {
  getBuckets<1>(s, bkt, n, K);
  for (int i = n - 1; i >= 0; i--) {
    int j = SA[i] - 1;
    if (j >= 0 && t[j])
      SA[--bkt[s[j]]] = j;
  }
}

void SA_IS(int *s, int *SA, int n, int K) { // require last symbol is 0 
#define isLMS(i) (i && t[i] && !t[i-1])
  int i, j;
  bits t(n);
  t[n-1] = 1;
  for (i = n - 3; i >= 0; i--)
    t[i] = (s[i]<s[i+1] || (s[i]==s[i+1] && t[i+1]==1));
  int bkt[K + 1];
  getBuckets<1>(s, bkt, n, K);
  fill(SA, SA + n, -1);
  forn(i, n)
    if (isLMS(i))
      SA[--bkt[s[i]]] = i;
  induceSAl(t, SA, s, bkt, n, K);
  induceSAs(t, SA, s, bkt, n, K);
  int n1 = 0;
  forn(i, n)
    if (isLMS(SA[i]))
      SA[n1++] = SA[i];
  fill(SA + n1, SA + n, -1);
  int name = 0, prev = -1;
  forn(i, n1) {
    int pos = SA[i];
    bool diff = false;
    for (int d = 0; d < n; d++)
      if (prev == -1 || s[pos+d] != s[prev+d] || t[pos+d] != t[prev+d])
        diff = true, d = n;
      else if (d > 0 && (isLMS(pos+d) || isLMS(prev+d)))
        d = n;
    if (diff)
      name++, prev = pos;
    SA[n1 + (pos >> 1)] = name - 1;
  }
  for (i = n - 1, j = n - 1; i >= n1; i--)
    if (SA[i] >= 0)
      SA[j--] = SA[i];
  int *s1 = SA + n - n1;
  if (name < n1)
    SA_IS(s1, SA, n1, name - 1);
  else
    forn(i, n1)
      SA[s1[i]] = i;
  getBuckets<1>(s, bkt, n, K);
  for (i = 1, j = 0; i < n; i++)
    if (isLMS(i))
      s1[j++] = i;
  forn(i, n1)
    SA[i] = s1[SA[i]];
  fill(SA + n1, SA + n, -1);
  for (i = n1 - 1; i >= 0; i--) {
    j = SA[i], SA[i] = -1;
    SA[--bkt[s[j]]] = j;
  }
  induceSAl(t, SA, s, bkt, n, K);
  induceSAs(t, SA, s, bkt, n, K);
}
// suffix array O(n) ends

// suffix array O(n log n) begins
string str;
int N, m, SA [MAX_N], LCP [MAX_N];
int x [MAX_N], y [MAX_N], w [MAX_N], c [MAX_N];

inline bool cmp (const int a, const int b, const int l) { return (y [a] == y [b] && y [a + l] == y [b + l]); }

void Sort () {
  for (int i = 0; i < m; ++i) w[i] = 0;
  for (int i = 0; i < N; ++i) ++w[x[y[i]]];
  for (int i = 0; i < m - 1; ++i) w[i + 1] += w[i];
  for (int i = N - 1; i >= 0; --i) SA[--w[x[y[i]]]] = y[i];
}

void DA () {
  for (int i = 0; i < N; ++i) x[i] = str[i], y[i] = i;
  Sort ();
  for (int i, j = 1, p = 1; p < N; j <<= 1, m = p) {
    for (p = 0, i = N - j; i < N; i++) y[p++] = i;
    for (int k = 0; k < N; ++k) if (SA[k] >= j) y[p++] = SA[k] - j;
    Sort();
    for (swap (x, y), p = 1, x[SA[0]] = 0, i = 1; i < N; ++i) x[SA [i]] = cmp (SA[i - 1], SA[i], j) ? p - 1 : p++;
  }
}

// common for all algorithms
void kasaiLCP () {
  for (int i = 0; i < N; i++) c[SA[i]] = i;
  for (int i = 0, j, k = 0; i < N; LCP [c[i++]] = k)
    if (c [i] > 0) for (k ? k-- : 0, j = SA[c[i] - 1]; str[i + k] == str[j + k]; k++);
    else k = 0;
}

void suffixArray () { // require last symbol is char(0)
  m = 256;
  N = str.size();
  DA ();
  kasaiLCP ();
}
// suffix array O(n log n) ends
