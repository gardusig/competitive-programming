#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;  // Precision for floating point comparisons

// --------------- Point and Vector Class ---------------

// The `pv` class represents a point or a 2D vector with coordinates `x` and
// `y`.
class pv {
 public:
  double x, y;

  // Default constructor
  pv();

  // Constructor initializing the point/vector with specific coordinates
  pv(const double &x, const double &y);

  // Overloading + operator to add two vectors
  pv operator+(const pv &other) const;

  // Overloading - operator to subtract two vectors
  pv operator-(const pv &other) const;

  // Overloading * operator to scale a vector by a constant
  pv operator*(const double &k) const;

  // Overloading / operator to divide a vector by a constant
  pv operator/(const double &k) const;

  // Overloading < operator to compare two vectors based on cross product
  bool operator<(const pv &other) const;

  // Overloading == operator to check equality of two points
  bool operator==(const pv &other) const;
};

// --------------- Line, Ray, and Segment Class ---------------

// The `lrs` class represents a line, ray, or segment in 2D space.
class lrs {
 public:
  double a, b,
      c;  // Coefficients for the general line equation: ax + by + c = 0
  pv start, finish;  // Start and end points of a segment or ray
  pv direction;      // Direction vector for the line/ray/segment

  // Default constructor
  lrs();

  // Constructor for a segment or ray initialized by two points
  lrs(const pv &start, const pv &finish);

  // Constructor for a line defined by the general equation ax + by + c = 0
  lrs(const double &a, const double &b, const double &c);
};

// --------------- Circle Class ---------------

// The `circle` class represents a circle defined by its center point `C` and
// radius `r`.
class circle {
 public:
  pv C;      // Center of the circle
  double r;  // Radius of the circle

  // Default constructor
  circle() {}

  // Constructor initializing a circle with a center and radius
  circle(const pv &C, const double &r);
};

// --------------- 2D Geometry Utilities ---------------

namespace _2D {

// Returns the angle ∠AOB between two vectors OA and OB (in radians)
double angle(const pv &A, const pv &O, const pv &B);

// Converts degrees to radians
double convert_degree_to_radian(const double &degree);

// Converts radians to degrees
double convert_radian_to_degree(const double &radian);

// Computes the cross product of two vectors A and B
double cross(const pv &A, const pv &B);

// Computes the dot product of two vectors A and B
double dot(const pv &A, const pv &B);

// Computes the norm (magnitude) of vector P
double norm(const pv &P);

// Returns a vector perpendicular to vector P
pv perpendicular(const pv &P);

// Rotates vector P by a given angle (in radians)
pv rotate(const pv &P, const double &rad);

// Returns the unit (normalized) vector of P
pv unit(const pv &P);

// Returns the bisector of angle ∠AOB
lrs bisector(const pv &A, const pv &O, const pv &B);

// Calculates the shortest distance between two lines
double distance_line_line(const lrs &l1, const lrs &l2);

// Calculates the shortest distance between a point and a line
double distance_point_line(const pv &point, const lrs &line);

// Calculates the shortest distance between a point and a ray
double distance_point_ray(const pv &point, const lrs &ray);

// Calculates the shortest distance between a point and a segment
double distance_point_segment(const pv &point, const lrs &segment);

// Calculates the shortest distance between two rays
double distance_ray_ray(const lrs &r1, const lrs &r2);

// Calculates the shortest distance between a ray and a line
double distance_ray_line(const lrs &ray, const lrs &line);

// Calculates the shortest distance between two segments
double distance_segment_segment(const lrs &s1, const lrs &s2);

// Calculates the shortest distance between a segment and a ray
double distance_segment_ray(const lrs &segment, const lrs &ray);

// Calculates the shortest distance between a segment and a line
double distance_segment_line(const lrs &segment, const lrs &line);

// Finds the intersection points of two lines (if they intersect)
vector<pv> line_line_intersect(const lrs &l1, const lrs &l2);

// Checks if a point lies on a line
bool point_inside_line(const pv &point, const lrs &line);

// Checks if a point lies on a ray
bool point_inside_ray(const pv &point, const lrs &ray);

// Checks if a point lies on a segment
bool point_inside_segment(const pv &point, const lrs &segment);

// Finds the intersection points of two circles
vector<pv> circle_circle_intersection(const circle &c1, const circle &c2);

// Finds the intersection points between a circle and a line
vector<pv> circle_line_intersection(const circle &_circle, const lrs &line);

// Finds the incenter of a triangle, the center of its incircle
pv circle_inside_triangle_center(const pv &A, const pv &B, const pv &C);

// Calculates the circumradius of a triangle
double circle_outside_triangle_radius(const pv &A, const pv &B, const pv &C);

// Checks if a point lies inside a circle
bool point_inside_circle(const pv &P, const circle &_circle);

// Constructs the convex hull of a set of points
vector<pv> build_convex_hull(const vector<pv> &points);

double polygon_area(const vector<pv> &v);

double polygon_perimeter(const vector<pv> &v);

bool point_inside_polygon(const pv &P, const vector<pv> &v);

pv polygon_centroid(const vector<pv> &v);

bool is_polygon_convex(const vector<pv> &v);

bool point_on_polygon_boundary(const pv &P, const vector<pv> &v);

}  // namespace _2D

// --------------- Implementation of Class Functions ---------------

// Point/Vector class methods

pv::pv() {}

pv::pv(const double &x, const double &y) {
  this->x = x;
  this->y = y;
}

pv pv::operator+(const pv &other) const { return pv(x + other.x, y + other.y); }

pv pv::operator-(const pv &other) const { return pv(x - other.x, y - other.y); }

pv pv::operator*(const double &k) const { return pv(x * k, y * k); }

pv pv::operator/(const double &k) const { return pv(x / k, y / k); }

bool pv::operator<(const pv &other) const {
  double cross = _2D::cross(*this, other);
  if (cross > 0) return true;
  if (cross < 0) return false;
  if ((this->x < 0 && other.x >= 0) || (this->x >= 0 && other.x < 0)) {
    return this->x < other.x;
  }
  if ((this->y < 0 && other.y >= 0) || (this->y >= 0 && other.y < 0)) {
    return this->y < other.y;
  }
  return _2D::norm(*this) < _2D::norm(other);
}

bool pv::operator==(const pv &other) const {
  return fabs(x - other.x) + fabs(y - other.y) < EPS;
}

// Line, Ray, and Segment class methods

lrs::lrs() {}

lrs::lrs(const pv &start, const pv &finish) {
  this->start = start;
  this->finish = finish;
  this->direction = this->finish - this->start;
  if (direction.x == 0.0) {
    this->a = 1.0;
    this->b = 0.0;
    this->c = -start.x;
  } else {
    double slope = direction.y / direction.x;
    this->a = -slope;
    this->b = 1.0;
    this->c = slope * start.x - start.y;
  }
}

lrs::lrs(const double &a, const double &b, const double &c) {
  this->a = a;
  this->b = b;
  this->c = c;
  if (b == 0.0) {
    this->start = pv(-c / a, 0);
    this->finish = pv(-c / a, 1);
  } else {
    this->start = pv(0, -c / b);
    this->finish = pv(1, -(a + c) / b);
  }
  this->direction = finish - start;
}

circle::circle(const pv &c, const double &r) : C(c), r(r) {}

// --------------- Implementation of 2D Geometry Utility Functions
// ---------------

// Calculates the perimeter of a polygon
// The polygon is represented by a vector of points in 2D
double _2D::polygon_perimeter(const vector<pv> &v) {
  double ans = 0.0;
  int n = int(v.size());
  for (int i = 0; i < n; ++i) {
    ans += _2D::norm(v[i] - v[(i + 1) % n]);
  }
  return ans;
}

// Checks if a polygon is convex
// The polygon is represented by a vector of points in 2D
// The function returns true if the polygon is convex, false otherwise
bool _2D::is_polygon_convex(const vector<pv> &v) {
  bool is_positive = false;
  bool is_negative = false;
  int n = int(v.size());

  for (int i = 0; i < n; ++i) {
    double cross_product =
        _2D::cross(v[(i + 1) % n] - v[i], v[(i + 2) % n] - v[i]);
    if (cross_product > EPS) {
      is_positive = true;
    } else if (cross_product < -EPS) {
      is_negative = true;
    }
    if (is_positive && is_negative) {
      return false;  // If both positive and negative cross products exist, it's
                     // not convex
    }
  }
  return true;
}

// Calculates the centroid of a polygon
// The polygon is represented by a vector of points in 2D
pv _2D::polygon_centroid(const vector<pv> &v) {
  double A = 0.0;
  pv centroid(0, 0);
  int n = int(v.size());

  for (int i = 0; i < n; ++i) {
    double cross_product = _2D::cross(v[i], v[(i + 1) % n]);
    A += cross_product;
    centroid = centroid + (v[i] + v[(i + 1) % n]) * cross_product;
  }
  A *= 0.5;
  centroid = centroid / (6.0 * A);

  return centroid;
}

// Determines if a point is on the boundary of a polygon
// The polygon is represented by a vector of points in 2D
bool _2D::point_on_polygon_boundary(const pv &P, const vector<pv> &v) {
  int n = int(v.size());
  for (int i = 0; i < n; ++i) {
    if (_2D::point_inside_segment(P, lrs(v[i], v[(i + 1) % n]))) {
      return true;
    }
  }
  return false;
}

// Returns the angle ∠AOB between two vectors OA and OB (in radians)
double _2D::angle(const pv &A, const pv &O, const pv &B) {
  pv OA = A - O, OB = B - O;
  return acos(_2D::dot(OA, OB) / (_2D::norm(OA) * _2D::norm(OB)));
}

// Converts degrees to radians
double _2D::convert_degree_to_radian(const double &degree) {
  return degree * M_PI / 180.0;
}

// Converts radians to degrees
double _2D::convert_radian_to_degree(const double &radian) {
  return radian * 180.0 / M_PI;
}

// Computes the cross product of two vectors A and B
double _2D::cross(const pv &A, const pv &B) { return A.x * B.y - A.y * B.x; }

// Computes the dot product of two vectors A and B
double _2D::dot(const pv &A, const pv &B) { return A.x * B.x + A.y * B.y; }

// Computes the norm (magnitude) of vector P
double _2D::norm(const pv &P) { return sqrt(_2D::dot(P, P)); }

// Returns a vector perpendicular to vector P
pv _2D::perpendicular(const pv &P) { return pv(-P.y, P.x); }

// Rotates vector P by a given angle (in radians)
pv _2D::rotate(const pv &P, const double &rad) {
  return pv(P.x * cos(rad) - P.y * sin(rad), P.x * sin(rad) + P.y * cos(rad));
}

// Returns the unit (normalized) vector of P
pv _2D::unit(const pv &P) { return P / _2D::norm(P); }

// Returns the bisector of angle ∠AOB
lrs _2D::bisector(const pv &A, const pv &O, const pv &B) {
  pv OA = A - O, OB = B - O;
  pv bisector = _2D::unit(OA) + _2D::unit(OB);
  return lrs(O, O + bisector);
}

// Calculates the shortest distance between two lines
double _2D::distance_line_line(const lrs &l1, const lrs &l2) {
  if (fabs(_2D::cross(l1.direction, l2.direction)) > EPS)
    return 0.0;  // Parallel check
  return fabs(_2D::cross(l2.start - l1.start, l1.direction)) /
         _2D::norm(l1.direction);
}

// Calculates the shortest distance between a point and a line
double _2D::distance_point_line(const pv &point, const lrs &line) {
  return fabs(_2D::cross(line.direction, point - line.start)) /
         _2D::norm(line.direction);
}

// Calculates the shortest distance between a point and a ray
double _2D::distance_point_ray(const pv &point, const lrs &ray) {
  if (_2D::dot(ray.direction, point - ray.start) < 0)
    return _2D::norm(point -
                     ray.start);  // Point is behind the start of the ray
  return _2D::distance_point_line(point, ray);
}

// Calculates the shortest distance between a point and a segment
double _2D::distance_point_segment(const pv &point, const lrs &segment) {
  pv AB = segment.finish - segment.start;
  pv AP = point - segment.start, BP = point - segment.finish;
  if (_2D::dot(AB, AP) < 0) return _2D::norm(AP);
  if (_2D::dot(AB, BP) > 0) return _2D::norm(BP);
  return _2D::distance_point_line(point, segment);
}

// Finds the intersection points of two lines (if they intersect)
vector<pv> _2D::line_line_intersect(const lrs &l1, const lrs &l2) {
  double d = _2D::cross(l1.direction, l2.direction);
  if (fabs(d) < EPS) return {};  // Parallel lines
  double t = _2D::cross(l2.start - l1.start, l2.direction) / d;
  return {l1.start + l1.direction * t};
}

// Checks if a point lies on a line
bool _2D::point_inside_line(const pv &point, const lrs &line) {
  return fabs(_2D::cross(line.direction, point - line.start)) < EPS;
}

// Checks if a point lies on a ray
bool _2D::point_inside_ray(const pv &point, const lrs &ray) {
  if (!_2D::point_inside_line(point, ray)) return false;
  return _2D::dot(ray.direction, point - ray.start) > -EPS;
}

// Checks if a point lies on a segment
bool _2D::point_inside_segment(const pv &point, const lrs &segment) {
  if (!_2D::point_inside_line(point, segment)) return false;
  return _2D::dot(segment.finish - segment.start, point - segment.start) >
             -EPS &&
         _2D::dot(segment.start - segment.finish, point - segment.finish) >
             -EPS;
}

// Finds the intersection points of two circles
vector<pv> _2D::circle_circle_intersection(const circle &c1, const circle &c2) {
  double d = _2D::norm(c2.C - c1.C);
  if (d > c1.r + c2.r || d < fabs(c1.r - c2.r)) return {};  // No intersection
  double a = (c1.r * c1.r - c2.r * c2.r + d * d) / (2.0 * d);
  double h = sqrt(c1.r * c1.r - a * a);
  pv P = c1.C + (c2.C - c1.C) * (a / d);
  pv offset = _2D::perpendicular(c2.C - c1.C) * (h / d);
  return {P + offset, P - offset};
}

// Finds the intersection points between a circle and a line
vector<pv> _2D::circle_line_intersection(const circle &_circle,
                                         const lrs &line) {
  pv projection =
      line.start +
      line.direction * (_2D::dot(_circle.C - line.start, line.direction) /
                        _2D::dot(line.direction, line.direction));
  double d = _2D::norm(_circle.C - projection);
  if (d > _circle.r) return {};  // No intersection
  double t = sqrt(_circle.r * _circle.r - d * d) / _2D::norm(line.direction);
  return {projection + line.direction * t, projection - line.direction * t};
}

// Finds the incenter of a triangle, the center of its incircle
pv _2D::circle_inside_triangle_center(const pv &A, const pv &B, const pv &C) {
  double a = _2D::norm(B - C);
  double b = _2D::norm(C - A);
  double c = _2D::norm(A - B);
  return (A * a + B * b + C * c) / (a + b + c);
}

// Calculates the circumradius of a triangle
double _2D::circle_outside_triangle_radius(const pv &A, const pv &B,
                                           const pv &C) {
  double a = _2D::norm(B - C);
  double b = _2D::norm(C - A);
  double c = _2D::norm(A - B);
  double s = (a + b + c) / 2.0;  // Semi-perimeter
  double area = sqrt(s * (s - a) * (s - b) * (s - c));
  return (a * b * c) / (4 * area);
}

// Checks if a point lies inside a circle
bool _2D::point_inside_circle(const pv &P, const circle &_circle) {
  return _2D::norm(P - _circle.C) < _circle.r + EPS;
}

// Constructs the convex hull of a set of points
vector<pv> _2D::build_convex_hull(const vector<pv> &points) {
  vector<pv> P = points;
  sort(P.begin(), P.end(), [](const pv &a, const pv &b) {
    if (fabs(a.x - b.x) > EPS) return a.x < b.x;
    return a.y < b.y;
  });
  vector<pv> H;
  for (int phase = 0; phase < 2; ++phase) {
    int start = int(H.size());
    for (const pv &pt : P) {
      while (H.size() >= start + 2 &&
             _2D::cross(H[H.size() - 1] - H[H.size() - 2], pt - H.back()) <
                 EPS) {
        H.pop_back();
      }
      H.push_back(pt);
    }
    H.pop_back();
    reverse(P.begin(), P.end());
  }
  return H;
}

// Calculates the area of a polygon
double _2D::polygon_area(const vector<pv> &polygon) {
  double area = 0;
  int n = polygon.size();
  for (int i = 0; i < n; ++i) {
    area += _2D::cross(polygon[i], polygon[(i + 1) % n]);
  }
  return fabs(area) / 2.0;
}

// Checks if a point is inside a polygon
bool _2D::point_inside_polygon(const pv &point, const vector<pv> &polygon) {
  bool inside = false;
  for (int i = 0, n = polygon.size(); i < n; ++i) {
    pv A = polygon[i], B = polygon[(i + 1) % n];
    if (((A.y > point.y) != (B.y > point.y)) &&
        (point.x < (B.x - A.x) * (point.y - A.y) / (B.y - A.y) + A.x)) {
      inside = !inside;
    }
  }
  return inside;
}

// ---------------------------------------------------------------------------------------

int main() {
  // Create some points
  pv A(0, 0), B(4, 0), C(4, 3), D(0, 3);

  // Test basic point/vector operations
  cout << "A + B = (" << (A + B).x << ", " << (A + B).y << ")" << endl;
  cout << "B - A = (" << (B - A).x << ", " << (B - A).y << ")" << endl;
  cout << "B * 2 = (" << (B * 2).x << ", " << (B * 2).y << ")" << endl;

  // Test distance functions
  lrs lineAB(A, B), lineCD(C, D);
  cout << "Distance between A and B: " << _2D::norm(B - A) << endl;
  cout << "Distance between point A and line CD: "
       << _2D::distance_point_line(A, lineCD) << endl;

  // Test polygon area and perimeter (rectangle ABCD)
  vector<pv> rectangle = {A, B, C, D};
  cout << "Polygon area (ABCD): " << _2D::polygon_area(rectangle) << endl;
  cout << "Polygon perimeter (ABCD): " << _2D::polygon_perimeter(rectangle)
       << endl;

  // Test point inside polygon
  pv P(2, 2);  // Inside point
  cout << "Point P inside rectangle ABCD: "
       << (_2D::point_inside_polygon(P, rectangle) ? "Yes" : "No") << endl;

  // Test point on polygon boundary
  cout << "Point B on rectangle boundary: "
       << (_2D::point_on_polygon_boundary(B, rectangle) ? "Yes" : "No") << endl;

  // Test convex polygon check
  cout << "Rectangle ABCD is convex: "
       << (_2D::is_polygon_convex(rectangle) ? "Yes" : "No") << endl;

  // Test line intersection
  lrs lineAC(A, C), lineBD(B, D);
  auto intersection_points = _2D::line_line_intersect(lineAC, lineBD);
  if (!intersection_points.empty()) {
    cout << "Intersection of line AC and line BD: (" << intersection_points[0].x
         << ", " << intersection_points[0].y << ")" << endl;
  } else {
    cout << "Lines AC and BD are parallel or do not intersect" << endl;
  }

  // Test circle creation and point inside check
  circle circ(A, 5);  // Circle with center A and radius 5
  cout << "Point P inside circle A: "
       << (_2D::point_inside_circle(P, circ) ? "Yes" : "No") << endl;

  // Test intersection between a circle and a line
  auto circle_line_intersections = _2D::circle_line_intersection(circ, lineAB);
  if (!circle_line_intersections.empty()) {
    cout << "Intersection of circle A and line AB: ("
         << circle_line_intersections[0].x << ", "
         << circle_line_intersections[0].y << ")" << endl;
  } else {
    cout << "Circle A and line AB do not intersect" << endl;
  }

  // Test circle-circle intersection
  circle circ2(C, 3);
  auto circle_circle_intersections =
      _2D::circle_circle_intersection(circ, circ2);
  if (!circle_circle_intersections.empty()) {
    cout << "Intersection of circle A and circle C: ("
         << circle_circle_intersections[0].x << ", "
         << circle_circle_intersections[0].y << ")" << endl;
  } else {
    cout << "Circles A and C do not intersect" << endl;
  }

  return 0;
}
