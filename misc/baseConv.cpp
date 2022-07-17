
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

std::vector<int> to_base(int a, int b) {
  std::vector<int> res;
  int p = 1;
  while (p * b <= a) p *= b;
  while (a) {
    int d = a / p;
    res.push_back(d);
    a -= p * d, p /= b;
  }
  if (res.empty()) res.push_back(0);
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