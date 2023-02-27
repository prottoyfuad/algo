
#include <bits/stdc++.h>

const int P = 1e9 + 7;

template <typename T> struct Matrix {
  int n, m;
  std::vector<std::vector<T>> mat;
  Matrix() {}
  Matrix(int n_, int m_) : n(n_), m(m_) {
    mat = std::vector<std::vector<T>> (n, std::vector<T> (m));
  }
  Matrix(const std::vector<std::vector<T>>& v) : mat(v) {
    n = static_cast<int> (mat.size());
    if (n == 0) m = 0;
    else {
      m = static_cast<int> (mat[0].size());
    }
  }
  static Matrix<T> identity(int _n) {
    assert(_n > 0);
    Matrix<T> ret(_n, _n);
    for (int i = 0; i < _n; i++) ret.mat[i][i] = static_cast<T>(1);
    return ret;
  }
  bool is_square() const { return n == m; }
  bool is_multipliable(const Matrix<T>& o) const { return m == o.n; }
  std::vector<T>& operator[] (int at) { return mat[at]; }

  Matrix<T> operator * (const Matrix<T>& o) const {
    assert(is_multipliable(o));
    Matrix<T> ret(n, o.m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        for (int k = 0; k < o.m; k++) {
          ret.mat[i][k] += (mat[i][j] * 1ll * o.mat[j][k]) % P;
          if (ret.mat[i][k] >= P) {
            ret.mat[i][k] -= P;
          }
        }
      }
    }
    return ret;
  }

  friend std::ostream& operator << (std::ostream& stream, const Matrix& o) {
    for (int i = 0; i < o.n; i++) {
      for (int j = 0; j < o.m; j++) {
        if (j > 0) stream << ' ';
        stream << o.mat[i][j];
      }
      stream << '\n';
    }
    return stream;
  } 
};

template <typename T, typename U> Matrix<T> power(Matrix<T> mat, U p) {
  assert(p >= 0 && mat.is_square());
  Matrix<T> ret = Matrix<T>::identity(mat.n);
  while (p > 0) {
    if (p & 1) ret = ret * mat;
    p >>= 1, mat = mat * mat;
  }
  return ret;
}

using namespace std;

int main() {
  Matrix<int> a(2, 3);
  a.mat = {{1, 0, 1}, {0, 1, 2}};
  
  Matrix<int> b({{3, 5}, {-1, 0}, {2, -1}});

  cout << a * b << '\n';

  auto fibonacci = [&](int x) {
    vector<vector<int64_t>> v = {{0, 1}, {1, 1}};
    Matrix<int64_t> m(v);
    cout << power(m, x) << '\n';
  };

  const int nax = 5;
  for (int i = 0; i < nax; i++) fibonacci(i);
  return 0;
}
