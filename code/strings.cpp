// string basis begins

vector<int> getZ(string s){
  vector<int> z;
  z.resize(s.size(), 0);
  int l = 0, r = 0;
  for (int i = 1; i < s.size(); i++){
    if (i <= r)
      z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]])
      z[i]++;
    if (i + z[i] - 1 > r){
      r = i + z[i] - 1;
      l = i;
    }
  }
  return z;
}

vector<int> getP(string s){
  vector<int> p;
  p.resize(s.size(), 0);
  int k = 0;
  for (int i = 1; i < s.size(); i++){
    while (k > 0 && s[i] == s[k])
      k = p[k - 1];
    if (s[i] == s[k])
      k++;
    p[i] = k;
  }
  return p;
}

vector<int> getH(string s){
  vector<int> h;
  h.resize(s.size() + 1, 0);
  for (int i = 0; i < s.size(); i++)
    h[i + 1] = ((h[i] * 1ll * pow) + s[i] - 'a' + 1) % mod;
  return h;
}

int getHash(vector<int> &h, int l, int r){
  int res = (h[r + 1] - h[l] * p[r - l + 1]) % mod;
  if (res < 0)
    res += mod;
  return res;
}

// string basis ends

