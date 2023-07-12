
#include <bits/stdc++.h>
       
/// http://xorshift.di.unimi.it/splitmix64.c
struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {      
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator() (uint64_t x) const {
    static const uint64_t seed = std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + seed);
  }
};

template <typename U, typename T> 
using hash_map = std::unordered_map<U, T, custom_hash>;

/*  
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;

template <typename U, typename T> 
using gp_hash_map = __gnu_pbds::gp_hash_table<U, T, custom_hash>;
*/

int main() {
  return 0;
}
