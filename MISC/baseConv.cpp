
#include <vector>
#include <iostream>

template <typename T> std::string to_hex(T a, char lower = 0) {
  if (a == 0) return std::string(1, 48); 
  char foo = 0;
  if (a < 0) foo = 1, a = -a;
  std::string hex;
  while (a) {
    int u = a & 15; a >>= 4;
    hex += char(u > 9 ? u + (lower ? 'a' : 'A') - 10 : u + '0');
  }
  if (foo) hex += '-';
  return std::string(hex.rbegin(), hex.rend());
}

std::vector<int> to_base(long long a, int b) {
  int k = 1;
  long long p = 1;
  while (p * b <= a) p *= b, k += 1;
  std::vector<int> res(k);
  for (int i = 0; i < k; i++) {
    res[i] = a / p;
    a -= p * res[i];
    p /= b;
  }
  return res;
}

int main() {
  auto v = to_base(140, 3);
  for (int e : v) std::cout << e;
  std::cout << "\n\n";
  
  for (int i = -5; i < 6; i++) {
    std::cout << i << " = " << ~i << '\n';
  }
}