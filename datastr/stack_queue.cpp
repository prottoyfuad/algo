
template <typename T> struct Stack {
  std::vector<T> val;
  std::vector<T> sum, mn, mx;
 
  Stack(const T& _d1, const T& _d2, const T& _d3) {
    sum.push_back(_d1);
    mn.push_back(_d2);
    mx.push_back(_d3);
  }

  int size() {
    return (int) val.size();
  }

  bool empty() {
    return val.empty();
  }
 
  void push(const T& x) {
    assert(!mn.empty());
    val.push_back(x);
    sum.push_back(sum.back() + x);
    mn.push_back(min(mn.back(), sum.back()));
    mx.push_back(max(mx.back(), sum.back()));
  }
 
  void pop() {
    assert(!val.empty());
    val.pop_back();
    mn.pop_back();
    mx.pop_back();
    sum.pop_back();   
  }
 
  T back() {
    assert(!val.empty());
    return val.back();
  }
  
  T front() {
    assert(!val.empty());
    return val.front();
  }
 
  T get_max() {
    return mx.back();
  }
};

template <typename T> struct Queue {
  Stack<T> front, back;
  
  void shift() {
    if (!front.empty()) {
      return;
    }
    while (!back.empty()) {
      front.push(back.back());
      back.pop();
    }
  }
        
  Queue(const T& _d1, const T& _d2, const T& _d3) {            
    front = Stack<T>(_d1, _d2, _d3);
    back = Stack<T>(_d1, _d2, _d3);
  }

  int size() {
    return front.size() + back.size();
  }

  bool empty() {
    return front.empty() && back.empty();
  }

  void push(T x) {
    back.push(x);
  }

  void pop() {
    assert(!empty());
    shift();
    front.pop();
  }

  T front() {
    assert(!empty());
    if (front.empty()) {
      return back.front();
    }
    return front.back();
  }

  T back() {
    assert(!empty());
    if (back.empty()) {
      return front.front();
    }
    return back.back();
  }

  int get_max() {
    return max(front.get_max(), back.get_max());
  }
};

