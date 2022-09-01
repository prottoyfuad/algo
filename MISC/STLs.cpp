
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class queue {
 private :
  size_t _size {};
  std::vector<T> _vl, _vr;
  void _shift() {
    assert(_size);
    if(_vl.empty()) while(!_vr.empty()) {
      _vl.emplace_back(_vr.back());
      _vr.pop_back();
    }
  }
 public :
  size_t size() { return _size; }
  bool empty() { return _size == 0; }
  T front() { return _shift(), _vl.back(); }
  void pop() { _shift(), _vl.pop_back(), --_size; }
  void push(T w) { _vr.emplace_back(w), ++_size; }
};

template <typename T>
class Stack {
 private :
  int n;
  vector<T> v;
  vector<bitset<nax>> st;
 public :
  Stack() : n() {
    bitset<nax> neutral;
    neutral.set(0);
    st.push_back(neutral);
  }
  void push(T x) {
    v.push_back(x);
    st.push_back(st.back() | (st.back() << x));
    ++n;
  }
  void pop() {
    assert(n);
    v.pop_back();
    st.pop_back();
    --n;
  }
  T top() {
    assert(n);
    return v.back();
  }
  bitset<nax> top_bit() {
    return st.back();
  }
  bool empty() { return n == 0; }
};

template <typename T>
class Queue {
 private :
  int n;
  Stack<T> front, back;
  void shift() {
    if(front.empty()) {
      while(!back.empty()) {
        front.push(back.top());
        back.pop();
      }
    }
  }
 public :
  Queue() : n() {}
  void push(T x) {
    back.push(x);
    ++n;
  }
  void pop() {
    assert(n); shift();
    front.pop();
  }
  T front_v() {
    assert(n); shift();
    return front.top();
  }
  bitset<nax> front_bit() {
    shift();
    return front.top_bit();
  }
  bool empty() { return n == 0; }

  bool good(const int S) {
    bitset<nax> A = front.top_bit(), B = back.top_bit();
    for(int i = 0; i <= S; i++) {
      if(A.test(i) && B.test(S - i))
      return true;
    }
    return false;
  }
};
