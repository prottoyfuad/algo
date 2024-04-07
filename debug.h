
#ifndef DEBUGGER_INCLUDED
#define DEBUGGER_INCLUDED 1

namespace debugger {

template <typename A, typename B>
std::ostream& operator << (std::ostream &stream, const std::pair<A, B> &x);
template <typename A, typename B, typename C>
std::ostream& operator << (std::ostream &stream, const std::tuple<A, B, C> &x);
template <typename A, typename B, typename C, typename D>
std::ostream& operator << (std::ostream &stream, const std::tuple<A, B, C, D> &x);
template <typename T, size_t S>
std::ostream& operator << (std::ostream &stream, const std::array<T, S> &v);
template <typename T_container, typename T>
std::ostream& operator << (std::ostream &stream, const T_container &v);

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
  return stream << '(' << std::get<0>(x) << ", " << std::get<1>(x) 
               << ", " << std::get<2>(x) << ", " << std::get<3>(x) << ')';
}

template <typename T, size_t S>
std::ostream& operator << (std::ostream &stream, const std::array<T, S> &v) {
  stream << '{';
  std::string space;
  for (const T &x : v) stream << space << x, space = ", ";
  return stream << '}';
}

template <typename T_container, 
         typename T = typename std::enable_if<!std::is_same<T_container, std::string>::value, 
         typename T_container::value_type>::type>
std::ostream& operator << (std::ostream &stream, const T_container &v) {
  stream << '{';
  std::string space;
  for (const T &x : v) stream << space << x, space = ", ";
  return stream << '}';
}

std::string sep = "";
void debug_() { 
  sep = ""; 
  std::cout << std::endl; 
}

template <typename T, typename... Args>
void debug_(T x, Args... args) {
  std::cout << sep << x;
  sep = ", ";
  debug_(args...);
}

} // End of namespace debugger

// #define debug_(...) debugger::debug_(__VA_ARGS__)
#define debug(...) std::cout << __LINE__ << ". [" << #__VA_ARGS__ << "]: ", debugger::debug_(__VA_ARGS__)

#endif

