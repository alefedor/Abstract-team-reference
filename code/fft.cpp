// FFT begins

const int MAX_LOG = 17;
const int MAXN = (1 << MAX_LOG);
int LOG = MAX_LOG;
int N = MAXN;

typedef std::complex<double> cd;

int rev[MAXN];
cd W[MAXN];

void precalc() {
  const double pi = std::acos(-1);
  for (int i = 0; i != N; ++i)
    W[i] = cd(std::cos(2 * pi * i / N), std::sin(2 * pi * i / N));

  int last = 0;
  for (int i = 1; i != N; ++i) {
    if (i == (2 << last))
      ++last;

    rev[i] = rev[i ^ (1 << last)] | (1 << (LOG - 1 - last));
  }
}

void fft(vector<cd>& a) {
  for (int i = 0; i != N; ++i)
    if (i < rev[i])
      std::swap(a[i], a[rev[i]]);

  for (int lvl = 0; lvl != LOG; ++lvl)
    for (int start = 0; start != N; start += (2 << lvl))
      for (int pos = 0; pos != (1 << lvl); ++pos) {
        cd x = a[start + pos];
        cd y = a[start + pos + (1 << lvl)];

        y *= W[pos << (LOG - 1 - lvl)];

        a[start + pos] = x + y;
        a[start + pos + (1 << lvl)] = x - y;
      }
}

void inv_fft(vector<cd>& a) {
  fft(a);
  std::reverse(a.begin() + 1, a.begin() + N);

  for (cd& elem: a)
    elem /= N;
}


vector<cd> mul_fft(vector<cd> a, vector<cd> b, int n = N) {
  if (N != n) {
    N = n;
    LOG = round(log2(N));
    precalc();
  }
  fft(a);
  fft(b);

  vector<cd> c(n);
  for (int i = 0; i < n; i++) {
    c[i] = a[i] * b[i];
  }

  inv_fft(c);
  return c;
}


vector<cd> inv_poly(vector<cd>& a, int n = N) {
  if (n == 1) {
    vector<cd> res(1);
    res[0] = cd(1) / a[0];
    return res;
  }
  vector<cd> r = inv_poly(a, n / 2);
  r.resize(n);
  vector<cd> q = mul_fft(a, r, n);
  for (int i = 0; i < n / 2; i++) {
    q[i] = -q[n / 2 + i];
    q[n / 2 + i] = 0;
  }
  vector<cd> c = mul_fft(q, r, n);
  for (int i = n / 2; i < n; i++) {
    r[i] = c[i - n / 2];
  }
  return r;
}

// FFT ends
