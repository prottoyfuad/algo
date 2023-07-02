
#include <cmath>
#include <complex>

template <typename T> int signOf(T x) {
  return (x > 0) - (x < 0);
}

template <typename T> struct Point {
  T x, y;
  explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
  bool operator < (Point p) const {
    return tie(x, y) < tie(p.x, p.y);
  }
  bool operator == (Point p) const {
    return tie(x, y) == tie(p.x, p.y);
  }
  Point operator + (Point p) const { 
    return Point(x + p.x, y + p.y);
  }
  Point operator - (Point p) const {
    return Point(x - p.x, y - p.y);
  }
  Point operator * (T d) const {
    return Point(x * d, y * d);
  }
  Point operator / (T d) const {
    return Point(x / d, y / d);
  }
  T dot(Point p) const {
    return x * p.x + y * p.y;
  }
  T cross(Point p) const {
    return x * p.y - y * p.x;
  }
  T cross(Point a, Point b) const {
    return (a - *this).cross(b - *this);
  }
  T dist2() const { 
    return x * x + y * y;
  }
  double dist() const {
    return sqrt(static_cast<double>(dist2()));
  }
  // makes this point's dist() = 1 unit
  Point unit() const {
    return *this / dist();
  }
  // angle to x-axis in interval [-pi, pi]
  double angle() const {
    return atan2(y, x);
  }
  Point normal() const {
    return perp().unit();
  }
  // rotates +90 degrees(ccw)
  Point perp() const { 
    return Point(-y, x);
  }
  // returns point rotated 'a' radians ccw around the origin
  Point rotate(double a) const {
    return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  friend std::ostream& operator << (std::ostream& stream, const Point& p) {
    return stream << p.x << " " << p.y;
  }
};
 
 