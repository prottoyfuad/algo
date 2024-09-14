
#include <bits/stdc++.h>

#ifdef LOCAL
#include "../algo/debug.h"
#else 
#define debug(...) 0
#endif

using namespace std;

// if you use argc and arg v
// do not forget to pass those argument from ./test script

int main (int argc, char **argv) {
  // argv is an array of strings
  // atoi is a C function for converting a string into an int

  srand(atoi(argv[1])); // srand sets the random seed
  int n = atoi(argv[2]);
  int x = atoi(argv[3]);

  cout << n << " " << x << endl;
  for (int i = 0; i < n; i++) {
    cout << 1 + rand() % x << " ";
  }
  cout << endl;
}

