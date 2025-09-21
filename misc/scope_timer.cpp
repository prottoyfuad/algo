
#include <bits/stdc++.h>

#ifdef LOCAL
#include "../algo/debug.h"
#else
#define debug(...) 0
#endif

struct ScopeTimer {
  static long long clock_now() { 
    return std::chrono::steady_clock::now().time_since_epoch().count(); 
  }
  std::string scopeName;
  long long start;
  ScopeTimer(const std::string& s) : scopeName(s), start(clock_now()) {}
  double timeElapsed() { 
    return (clock_now() - start) / 1e9; 
  }
  ~ScopeTimer() { 
    debug("@ScopeTime:", scopeName, timeElapsed());
  }
};

int main() {      
  ScopeTimer tt1(__func__);
  int N = 1e7;
  srand(time(0));
  for (int i = 0; i < N; i++) {    
      unsigned x = rand() << 15 | rand() | 1;
      unsigned y = rand() << 15 | rand() | 1;
      if (x < y) std::swap(x, y);
      x /= y;
      y /= x;
  }
  {                    
    ScopeTimer tt2("dummy-scope");
    for (int i = 0; i < N; i++) {    
      unsigned x = rand() << 15 | rand();
      unsigned y = rand() << 15 | rand();
      if (x < y) std::swap(x, y);
      x /= y;
      y /= x;
    }
  }
  return 0;
}
 