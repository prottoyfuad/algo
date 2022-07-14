
#ifndef WE_HAVE_MAGIC
#define WE_HAVE_MAGIC 1

template <typename A, typename B> std::ostream& operator << (std::ostream &stream, const std::pair<A, B> &x);
template <typename A, typename B, typename C> std::ostream& operator << (std::ostream &stream, const std::tuple<A, B, C> &x);
template <typename A, typename B, typename C, typename D> std::ostream& operator << (std::ostream &stream, const std::tuple<A, B, C, D> &x);

template <typename A, typename B>
std::ostream& operator << (std::ostream &stream, const std::pair<A, B> &x) {
  return stream << '(' << x.first << ", " << x.second << ')';
}

template <typename A, typename B, typename C>
std::ostream& operator << (std::ostream &stream, const std::tuple<A, B, C> &x) {
  return stream << '(' << std::get<0>(x) << ", " << std::get<1>(x) << ", " << std::get<2>(x) << ')';
}

template <typename A, typename B, typename C, typename D>
std::ostream& operator << (std::ostream &stream, const std::tuple<A, B, C, D> &x) {
  return stream << '(' << std::get<0>(x) << ", " << std::get<1>(x) << ", " << std::get<2>(x) << ", " << std::get<3>(x) << ')';
}

template <typename T, size_t S>
std::ostream& operator << (std::ostream &stream, const std::array<T, S> &v) {
  stream << '{';
  std::string space;
  for (const T &x : v) stream << space << x, space = ", ";
  return stream << '}';
}

template <typename T_container, typename T = typename std::enable_if<!std::is_same<T_container, std::string>::value, typename T_container::value_type>::type>
std::ostream& operator << (std::ostream &stream, const T_container &v) {
  stream << '{';
  std::string space;
  for (const T &x : v) stream << space << x, space = ", ";
  return stream << '}';
}

static std::string __sep = ": ";
void __debug_out() { __sep = ": "; std::cout << std::endl; }
template <typename T, typename... Args>
void __debug_out(T x, Args... args) {
  std::cout << __sep << x;
  __sep[0] = ',';
  __debug_out(args...);
}

#define debug(...) std::cout << __LINE__ << ". [" << #__VA_ARGS__ << "] ", __debug_out(__VA_ARGS__)
#endif
