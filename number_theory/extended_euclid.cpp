
#include <bits/stdc++.h>

using namespace std;

/*
gcd(a, b) ::

  g = a * x + b * y;

  g = b * x1 + (a % b) * y1;
  (a % b) = a - floor(a / b) * b;

    g = b * x1 + [ a - floor(a / b) * b ] * y1;
>>  g = a * x1 + b * x1 - b * y1 * floor(a / b);
>>  g = a * x1 + b * [x1 - y1 * floor(a / b)];

so in equation, g = ax + by, value of the coefficients are-
  x = x1;
  y = x1 - y1 * floor(a / b);

*/

template <typename T> std::array<T, 3> ext_gcd(T a, T b) {
  if (b == 0) return {a, 1, 0};
  auto [d, x, y] = ext_gcd(b, a % b);
  return {d, y, x - y * (a / b)};
}

// tourist
int ext_euclid(int a, int b, int& x, int& y) {
  x = 1, y = 0;
  int u = 0, v = 1;
  while (b) {
    int q = a / b;
    x -= q * u; std::swap(x, u);
    y -= q * v; std::swap(y, v);
    a -= q * b; std::swap(a, b);
  }
  return a; // a is gcd(originalA, originalB);
}
// linear diophantile eqn's solution exist iff gcd(a, b) | c;
// one solution is {x_ans, y_ans} = {x * c / g, y * c / g} ^^[ext-euclid]
// and we can derive the func to find modular inverse from this-
template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T q = m / a;
    m -= q * a; std::swap(a, m);
    u -= q * v; std::swap(u, v);
  }
  assert(m == 1);
  return u; // this needs normalization (using typename T = Modular is fine)
}
// !tourist

// cp algo
int ext_gcd(int a, int b, int& x, int& y) {
  if(b == 0) {
    x = 1, y = 0;
    return a;
  }
  int x1, y1;
  int g = ext_gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return g;
}
int ext_gcd_iterative(int a, int b, int& x, int& y) {
  x = 1, y = 0;
  int x1 = 0, y1 = 1, a1 = a, b1 = b;
  while(b1) {
    int q = a1 / b1;
    tie(x, x1) = {x1, x - q * x1};
    tie(y, y1) = {y1, y - q * y1};
    tie(a1, b1) = {b1, a1 - q * b1};
  }
  return a1;
}
// !cp algo


int main() {
  #ifdef _hogwarts
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
  #endif

  return 0;
}
