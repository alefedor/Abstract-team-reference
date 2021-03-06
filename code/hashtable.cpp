// fast hashtable begins

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<int, int> table;

const int RANDOM = chrono :: high_resolution_clock :: now().time_since_epoch().count();
struct chash {
  int operator()(int x) { return hash<int>{}(x ^ RANDOM); }
};
gp_hash_table<key, int, chash> table;

// fast hashtable ends
