// FFT begins

const int LOG = 19;
const int N = (1 << LOG);

typedef std::complex<double> cd;

int rev[N];
cd W[N];

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
    std::reverse(a.begin() + 1, a.end());
    
    for (cd& elem: a)
        elem /= N;
}

// FFT ends
