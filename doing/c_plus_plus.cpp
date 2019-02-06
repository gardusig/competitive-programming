#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

// point and vector class
class pv {
public:

  double x, y;

  pv();
  pv(const double &x, const double &y);
  pv operator + (const pv &other) const;
  pv operator - (const pv &other) const;
  pv operator * (const double &k) const;
  pv operator / (const double &k) const;
  bool operator < (const pv &other) const;
  bool operator == (const pv &other) const;
};

// line, ray and segment class
class lrs {
public:

  double a, b, c;
  pv start, finish, direction;

  lrs();
  lrs(const pv &start, const pv &finish);
  lrs(const double &a, const double &b, const double &c);
};

// circle class
class circle {
public:

  pv C;
  double r;

  circle () {}
  circle (const pv &C, const double &r);
};

// 2D geometry namespace
namespace _2D {
  double angle(const pv &A, const pv &O, const pv &B);
  double convert_degree_to_radian(const double &degree);
  double convert_radian_to_degree(const double &radian);
  double cross(const pv &A, const pv &B);
  double dot(const pv &A, const pv &B);
  double norm(const pv &P);
  pv perpendicular(const pv &P);
  pv rotate(const pv &P, const double &rad);
  pv unit(const pv &P);
  lrs bisector(const pv &A, const pv &O, const pv &B);
  double distance_line_line(const lrs &l1, const lrs &l2);
  double distance_point_line(const pv &point, const lrs &line);
  double distance_point_ray(const pv &point, const lrs &ray);
  double distance_point_segment(const pv &point, const lrs &segment);
  double distance_ray_ray(const lrs &r1, const lrs &r2);
  double distance_ray_line(const lrs &ray, const lrs &line);
  double distance_segment_segment(const lrs &s1, const lrs &s2);
  double distance_segment_ray(const lrs &segment, const lrs &ray);
  double distance_segment_line(const lrs &segment, const lrs &line);
  vector< pv > line_line_intersect(const lrs &l1, const lrs &l2);
  bool point_inside_line(const pv &point, const lrs &line);
  bool point_inside_ray(const pv &point, const lrs &ray);
  bool point_inside_segment(const pv &point, const lrs &segment);
  vector< pv > circle_circle_intersection(const circle &c1, const circle &c2);
  vector< pv > circle_line_intersection(const circle &_circle, const lrs &line);
  pv circle_inside_triangle_center(const pv &A, const pv &B, const pv &C);
  double circle_outside_triangle_radius(const pv &A, const pv &B, const pv &C);
  bool point_inside_circle(const pv &P, const circle &_circle);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  return 0;
}

pv::pv() {}

pv::pv(const double &x, const double &y) {
  this->x = x;
  this->y = y;
}

pv pv::operator + (const pv &other) const {
  return pv(x + other.x, y + other.y);
}

pv pv::operator - (const pv &other) const {
  return pv(x - other.x, y - other.y);
}

pv pv::operator * (const double &k) const {
  return pv(x * k, y * k);
}

pv pv::operator / (const double &k) const {
  return pv(x / k, y / k);
}

bool pv::operator < (const pv &other) const {
  if (x != other.x) {
    return y < other.y;
  }
  return x < other.x;
}

bool pv::operator == (const pv &other) const {
  return fabs(x - other.x) + fabs(y - other.y) < EPS;
}

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