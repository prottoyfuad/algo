
#include <bits/stdc++.h>

template <unsigned L = 0> struct Timer {
  using i64 = long long;
  static i64 clock_now() { 
    return std::chrono::steady_clock::now().time_since_epoch().count(); 
  }
  i64 start;
  Timer() : start(clock_now()) {}
  double time() { 
    return (clock_now() - start) / 1e9; 
  }
  ~Timer() { 
    std::cout << L << ". Time elapsed: " << std::fixed << std::setprecision(4) << time() << " sec!" << std::endl;
  }
};           

int main() {      
  Timer<__LINE__> tt1;
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
    Timer<__LINE__> tt2;
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
 