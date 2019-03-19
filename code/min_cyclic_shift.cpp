// min cyclic shift begins

string min_cyclic_shift (string s) {
  s += s;
  int n = (int) s.length();
  int i=0, ans=0;
  while (i < n/2) {
    ans = i;
    int j=i+1, k=i;
    while (j < n && s[k] <= s[j]) {
      if (s[k] < s[j])
        k = i;
      else
        ++k;
      ++j;
    }
    while (i <= k)  i += j - k;
  }
  return s.substr (ans, n/2);
}

// min cyclic shift ends
