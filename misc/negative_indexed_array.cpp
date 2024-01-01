
#include <iostream>

const int N = 2;

int a_[2 * N + 1][2 * N + 1][2 * N + 1];
auto a = reinterpret_cast<int (*)[2 * N + 1][2 * N + 1]>(&a_[N][N][N]);

int main() {
  int cnt = 0;
  for (int i = -N; i <= N; i++) {
    for (int j = -N; j <= N; j++) {
      for (int k = -N; k <= N; k++) {
        a[i][j][k] = ++cnt;
      }
    }
  }
  for (int i = -N; i <= N; i++) {
    for (int j = -N; j <= N; j++) {
      for (int k = -N; k <= N; k++) {
        std::cout << a[i][j][k] << " \n"[k == N];
      } 
    }
    std::cout << '\n';
  }
  return 0;
}

