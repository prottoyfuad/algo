
#include <bits/stdc++.h>
 
template <typename T> struct Stack {
  std::vector<T> val;
  std::vector<T> sum, mn, mx;
 
  Stack(const T& _d1, const T& _d2, const T& _d3) {
    sum.push_back(_d1);
    mn.push_back(_d2);
    mx.push_back(_d3);
  }
 
  void push(const T& x) {
    assert(!mn.empty());
    val.push_back(x);
    sum.push_back(sum.back() + x);
    mn.push_back(min(mn.back(), sum.back()));
    mx.push_back(max(mx.back(), sum.back()));
  }
 
  void pop() {
    assert(!mn.empty());
    val.pop_back();
    mn.pop_back();
    mx.pop_back();
    sum.pop_back();   
  }
 
  T back() {
    return val.back();
  }
 
  T get_max() {
    return mx.back();
  }
 
  bool good() {
    return mn.back() >= 0;
  }

  int size() {
    return (int) val.size() - 1;
  }
};

template <typename T> struct Queue {
  Stack<T> front, back;
        
  Queue(const T& _d1, const T& _d2, const T& _d3) {            
    front = Stack<T>(_d1, _d2, _d3);
    back = Stack<T>(_d1, _d2, _d3);
  }
};

using namespace std;
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  return 0;
}
 