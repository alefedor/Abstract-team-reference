// prime roots mod n begins

int num = 0;
long long phi = n, nn = n;
for (long long x:primes){
    if (x*x>nn)
        break;
    if (nn % x == 0){
        while (nn % x == 0)
            nn /= x;
        phi -= phi/x;
        num++;
    }
}
if (nn != 1){
    phi -= phi/nn;
    num++;
}
if (!((num == 1 && n % 2 != 0) || n == 4 || n == 2 || (num == 2 && n % 2 == 0 && n % 4 != 0))) {
    cout << "-1\n";
    continue;
}
vector<long long> v;
long long pp = phi;
for (long long x:primes){
    if (x*x>pp)
        break;
    if (pp % x == 0){
        while (pp % x == 0)
            pp /= x;
        v.push_back(x);
    }
}
if (pp != 1){
    v.push_back(pp);
}
while (true){
    long long a = primes[rand()%5000]%n;
    if (gcd(a, n) != 1)
        continue;
    bool bb = false;
    for (long long x:v)
        if (pow(a, phi/x) == 1){
            bb = true;
            break;
        }
    if (!bb){
        cout << a << "\n";
        break;
    }
}

// prime roots mod n ends
