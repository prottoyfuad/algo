
const int P = 1e9 + 7;

template <typename T> struct matrix {
  int n, m;
  std::vector<std::vector<T>> a;

  matrix() {}
  matrix(int n_, int m_) : n(n_), m(m_) {
    a = std::vector<std::vector<T>> (n, std::vector<T> (m));
  }

  matrix(const std::vector<std::vector<T>>& v) : a(v) {
    n = static_cast<int> (a.size());
    if (n == 0) {
      m = 0;
    } else {
      m = static_cast<int> (a[0].size());
    }
  }

  static matrix<T> identity(int _n) {
    assert(_n > 0);
    matrix<T> ret(_n, _n);
    for (int i = 0; i < _n; i++) {
      ret.a[i][i] = static_cast<T>(1);
    }
    return ret;
  }

  bool is_square() const { 
    return n == m; 
  }

  bool is_multipliable(const matrix<T>& o) const { 
    return m == o.n; 
  }

  std::vector<T>& operator[] (int at) { 
    return a[at]; 
  }

  matrix<T> operator * (const matrix<T>& o) const {
    assert(is_multipliable(o));
    matrix<T> ret(n, o.m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        for (int k = 0; k < o.m; k++) {
          ret.a[i][k] += (a[i][j] * 1ll * o.a[j][k]) % P;
          if (ret.a[i][k] >= P) {
            ret.a[i][k] -= P;
          }
        }
      }
    }
    return ret;
  }

  friend std::ostream& operator << (std::ostream& stream, const matrix& o) {
    for (int i = 0; i < o.n; i++) {
      for (int j = 0; j < o.m; j++) {
        if (j > 0) stream << ' ';
        stream << o.a[i][j];
      }
      stream << '\n';
    }
    return stream;
  } 
};

template <typename T, typename U> matrix<T> power(matrix<T> a, U p) {
  assert(p >= 0 && a.is_square());
  matrix<T> ret = matrix<T>::identity(a.n);
  while (p > 0) {
    if (p & 1) ret = ret * a;
    a = a * a;
    p /= 2;
  }
  return ret;
}

using namespace std;

int main() {
  matrix<int> a(2, 3);
  a.a = {{1, 0, 1}, {0, 1, 2}};
  
  matrix<int> b({{3, 5}, {-1, 0}, {2, -1}});

  cout << a * b << '\n';

  auto fibonacci = [&](int x) {
    vector<vector<int64_t>> v = {{0, 1}, {1, 1}};
    matrix<int64_t> m(v);
    cout << power(m, x) << '\n';
  };

  const int nax = 5;
  for (int i = 0; i < nax; i++) fibonacci(i);
  return 0;
}
