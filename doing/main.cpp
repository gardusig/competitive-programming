#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

class pv {
public:
	double x, y;
	pv() {}
	pv(const auto &x, const auto &y) {
		this->x = x;
		this->y = y;
	}
	pv operator + (const auto &other) const {
		return pv(x + other.x, y + other.y);
	}
	pv operator - (const auto &other) const {
		return pv(x - other.x, y - other.y);
	}
	pv operator * (const auto &k) const {
		return pv(x * k, y * k);
	}
	pv operator / (const auto &k) const {
		return pv(x / k, y / k);
	}
	bool operator < (const auto &other) const {
		if (fabs(x - other.x) < EPS)
			return y < other.y;
		return x < other.x;
	}
	bool operator == (const auto &other) const {
		return fabs(x - other.x) + fabs(y - other.y) < EPS;
	}
	static double angle(const auto &A, const auto &O, const auto &B) {
		pv C = A - O, D = B - O;
		// if (pv::cross(C, D) > 0)
			// return acos(-1) * 2.0 - acos(pv::dot(C, D) / (pv::norm(C) * pv::norm(D)));
		return acos(pv::dot(C, D) / (pv::norm(C) * pv::norm(D)));
	}
	static double convert_degree_to_radian(const double &degree) {
		return degree * acos(-1) / 180.0;
	}
	static double convert_radian_to_degree(const double &radian) {
		return radian * 180.0 / acos(-1);
	}
	static double cross(const pv &A, const pv &B) {
		return (A.x * B.y) - (A.y * B.x);
	}
	static double dot(const pv &A, const pv &B) {
		return (A.x * B.x) + (A.y * B.y);
	}
	static double norm(const pv &P) {
		return sqrt(pv::dot(P, P));
	}
	static pv perpendicular(const pv &P) {
		return pv(-P.y, P.x);
	}
	static pv rotate(const pv &P, const double &rad) {
		return pv((P.x * cos(rad)) - (P.y * sin(rad)), (P.x * sin(rad)) + (P.y * cos(rad)));
	}
	static pv unit(const pv &P) {
		return P / pv::norm(P);
	}
};

class lrs {
public:
	double a, b, c;
	pv start, finish, direction;
	lrs () {}
	lrs (const pv _start, const pv _finish) {
		start = _start, finish = _finish, direction = _finish - _start;
		if (!direction.x)
			a = 1.0, b = 0.0, c = -start.x;
		else {
			double slope = direction.y / direction.x;
			a = -slope, b = 1.0, c = slope * start.x - start.y;
		}
	}
	lrs (const double _a, const double _b, const double _c) {
		a = _a, b = _b, c = _c;
		if (!b)
			start = pv(-c / a, 0), finish = pv(-c / a, 1);
		else
			start = pv(0, -c / b), finish = pv(1, -(a + c) / b);
		direction = finish - start;
	}
	static lrs bisector (const pv A, const pv O, const pv B) {
		pv X = (A - O);
		pv Y = (B - O);
		if (pv::cross(X, Y))
			return lrs(O, O + (pv::unit(X) + pv::unit(Y)));
		if ((X.x < 0 and Y.x >= 0) or (X.x >= 0 and Y.x < 0) or (X.y < 0 and Y.y >= 0) or (X.y >= 0 and Y.y < 0))
			return lrs(O, O + pv::perpendicular(X));
		return lrs(O, O + X);
	}
	static double distance_line_line (const lrs l1, const lrs l2) {
		vector<pv> intersection = lrs::line_line_intersect(l1, l2);
		if (int(intersection.size()))
			return 0.0;
		return lrs::distance_point_line(l1.start, l2);
	}
	static double distance_point_line (const pv point, const lrs line) {
		return fabs(pv::cross(point - line.start, line.direction)) / pv::norm(line.direction);
	}
	static double distance_point_ray (const pv point, const lrs ray) {
		if (pv::dot(point - ray.start, ray.direction) < -EPS)
			return pv::norm(point - ray.start);
		return distance_point_line(point, ray);
	}
	static double distance_point_segment (const pv point, const lrs segment) {
		if (pv::dot(point - segment.start, segment.finish - segment.start) < -EPS)
			return pv::norm(point - segment.start);
		if (pv::dot(point - segment.finish, segment.start - segment.finish) < -EPS)
			return pv::norm(point - segment.finish);
		return distance_point_line(point, segment);
	}
	static double distance_ray_ray (const lrs r1, const lrs r2) {
		vector<pv> intersection = lrs::line_line_intersect(r1, r2);
		if (int(intersection.size()) and lrs::point_inside_ray(intersection[0], r1) and lrs::point_inside_ray(intersection[0], r2))
			return 0.0;
		double ans = LLONG_MAX;
		ans = min(ans, lrs::distance_point_ray(r1.start, r2));
		ans = min(ans, lrs::distance_point_ray(r2.start, r1));
		return ans;
	}
	static double distance_ray_line (const lrs ray, const lrs line) {
		vector<pv> intersection = lrs::line_line_intersect(ray, line);
		if (int(intersection.size()) and lrs::point_inside_ray(intersection[0], ray))
			return 0.0;
		return distance_point_line(ray.start, line);
	}
	static double distance_segment_segment (const lrs s1, const lrs s2) {
		vector<pv> intersection = lrs::line_line_intersect(s1, s2);
		if (int(intersection.size()) and lrs::point_inside_segment(intersection[0], s1) and lrs::point_inside_segment(intersection[0], s2))
			return 0.0;
		double ans = LLONG_MAX;
		ans = min(ans, lrs::distance_point_segment(s1.start, s2));
		ans = min(ans, lrs::distance_point_segment(s1.finish, s2));
		ans = min(ans, lrs::distance_point_segment(s2.start, s1));
		ans = min(ans, lrs::distance_point_segment(s2.finish, s1));
		return ans;
	}
	static double distance_segment_ray (const lrs segment, const lrs ray) {
		vector<pv> intersection = lrs::line_line_intersect(segment, ray);
		if (int(intersection.size()) and lrs::point_inside_segment(intersection[0], segment) and lrs::point_inside_ray(intersection[0], ray))
			return 0.0;
		double ans = LLONG_MAX;
		ans = min(ans, lrs::distance_point_ray(segment.start, ray));
		ans = min(ans, lrs::distance_point_ray(segment.finish, ray));
		ans = min(ans, lrs::distance_point_segment(ray.start, segment));
		return ans;
	}
	static double distance_segment_line (const lrs segment, const lrs line) {
		vector<pv> intersection = lrs::line_line_intersect(segment, line);
		if (int(intersection.size()) and lrs::point_inside_segment(intersection[0], segment))
			return 0.0;
		double ans = LLONG_MAX;
		ans = min(ans, lrs::distance_point_line(segment.start, line));
		ans = min(ans, lrs::distance_point_line(segment.finish, line));
		return ans;
	}
	static vector<pv> line_line_intersect (const lrs l1, const lrs l2) {
		vector<pv> ans;
		double den = pv::cross(l1.direction, l2.direction);
		if (fabs(den) < EPS)
			return ans;
		double t = pv::cross(l2.start - l1.start, l2.direction) / den;
		ans.push_back(l1.start + (l1.direction * t));
		return ans;
	}
	static bool point_inside_line (const pv point, const lrs line) {
		return (fabs(pv::cross(point - line.start, line.direction)) < EPS);
	}
	static bool point_inside_ray (const pv point, const lrs ray) {
		if (!(fabs(pv::cross(point - ray.start, ray.direction)) < EPS))
			return false;
		if (pv::dot(point - ray.start, ray.direction) < -EPS)
			return false;
		return true;
	}
	static bool point_inside_segment (const pv point, const lrs segment) {
		if (segment.start == segment.finish)
			return point == segment.start;
		if (!(fabs(pv::cross(point - segment.start, segment.direction)) < EPS))
			return false;
		if (pv::dot(point - segment.start, segment.finish - segment.start) < -EPS)
			return false;
		if (pv::dot(point - segment.finish, segment.start - segment.finish) < -EPS)
			return false;
		return true;
	}
};

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int a, b, c; cin >> a >> b >> c;
	lrs line = lrs(a, b, c);
	vector<pv> v;
	for (int i = 0; i < 2; ++i) {
		int x, y; cin >> x >> y;
		v.push_back(pv(x, y));
	}
	double ans = fabs(v[0].x - v[1].x) + fabs(v[0].y - v[1].y);
	if (v[0].x > v[1].x)
		swap(v[0], v[1]);
	pv A = v[0];
	pv B = v[1];
	pv C = pv(v[0].x, v[1].y);
	pv D = pv(v[1].x, v[0].y);
	vector< pair<lrs, lrs> > ways;
	ways.push_back({lrs(A, C), lrs(C, B)});
	ways.push_back({lrs(A, D), lrs(D, B)});
	ways.push_back({lrs(A, C), lrs(D, B)});
	ways.push_back({lrs(A, D), lrs(C, B)});
	for (const auto &i: ways) {
		vector<pv> kappa = lrs::line_line_intersect(i.first, line);
		vector<pv> keepo = lrs::line_line_intersect(i.second, line);
		if (int(kappa.size()) > 0 and int(keepo.size()) > 0)
			ans = min(ans, pv::norm(A - kappa[0]) + pv::norm(kappa[0] - keepo[0]) + pv::norm(keepo[0] - B));
	}
	return cout << fixed << setprecision(10) << ans << '\n', 0;
}