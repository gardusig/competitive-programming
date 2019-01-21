#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
vector<int> v;

class pv {
public:
	double x, y;
	pv() {}
	pv(const double &x, const double &y) {
		this->x = x;
		this->y = y;
	}
	pv operator + (const pv &other) const {
		return pv(x + other.x, y + other.y);
	}
	pv operator - (const pv &other) const {
		return pv(x - other.x, y - other.y);
	}
	pv operator * (const double &k) const {
		return pv(x * k, y * k);
	}
	pv operator / (const double &k) const {
		return pv(x / k, y / k);
	}
	bool operator < (const pv &other) const {
		if (fabs(x - other.x) < EPS)
			return y < other.y;
		return x < other.x;
	}
	bool operator == (const pv &other) const {
		return fabs(x - other.x) + fabs(y - other.y) < EPS;
	}
	static double angle(const pv &A, const pv &O, const pv &B) {
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

class circle {
public:
	pv C;
	double r;
	circle () {}
	circle (const pv _C, const double _r) {
		C = _C, r = _r;
	}
	static vector<pv> circle_circle_intersection (const circle c1, const circle c2) {
		vector<pv> ans;
		double d = pv::norm(c1.C - c2.C);
		if (d > c1.r + c2.r or d < fabs(c1.r - c2.r))
			return ans;
		double x = (c1.r * c1.r - c2.r * c2.r + d * d) / (2.0 * d);
		if (c1.r * c1.r < x * x)
			return ans;
		double h = sqrt(c1.r * c1.r - x * x);
		pv P = c1.C + (pv::unit(c2.C - c1.C) * x);
		if (h < EPS) {
			ans.push_back(P);
			return ans;
		}
		pv Q = pv::perpendicular(pv::unit(c2.C - c1.C)) * h;
		ans.push_back(P + Q);
		ans.push_back(P - Q);
		return ans;
	}
	static vector<pv> circle_line_intersection (const circle _circle, const lrs line) {
		vector<pv> ans;
		double h = lrs::distance_point_line(_circle.C, line);
		if (h > _circle.r)
			return ans;
		pv P = lrs::line_line_intersect(line, lrs(_circle.C, _circle.C + pv::perpendicular(line.direction)))[0];
		double delta = sqrt(_circle.r * _circle.r - h * h);
		if (delta < EPS) {
			ans.push_back(P);
			return ans;
		}
		pv Q = pv::unit(line.direction) * delta;
		ans.push_back(P + Q);
		ans.push_back(P - Q);
		return ans;
	}
	static pv circle_inside_triangle_center (const pv A, const pv B, const pv C) {
		lrs l1 = lrs::bisector(A, B, C);
		lrs l2 = lrs::bisector(B, C, A);
		return lrs::line_line_intersect(l1, l2)[0];
	}
	static double circle_outside_triangle_radius (const pv A, const pv B, const pv C) {
		double ab = pv::norm(A - B);
		double bc = pv::norm(B - C);
		double ca = pv::norm(C - A);
		double area = pv::cross(B - A, C - A);
		return (ab * bc * ca) / (8.0 * area);
	}
	static bool point_inside_circle (const pv P, const circle _circle) {
		return pv::norm(P - _circle.C) <= _circle.r;
	}
};

bool ccw_center (const pv X, const pv Y) {
	pv A = X - center;
	pv B = Y - center;
	double cross = pv::cross(A, B);
	if (cross > 0)
		return true;
	if (cross < 0)
		return false;
	if ((A.x < 0 and B.x >= 0) or (A.x >= 0 and B.x < 0))
		return A.x < B.x;
	if ((A.y < 0 and B.y >= 0) or (A.y >= 0 and B.y < 0))
		return A.y < B.y;
	return pv::norm(A) < pv::norm(B);
}

void build_convex_hull () {
	if (int(v.size()) < 3)
		return;
	int idx = 0;
	for (int i = 1; i < n; ++i)
		if (v[i].x < v[idx].x or (v[i].x == v[idx].x and v[i].y < v[idx].y))
			idx = i;
	swap(v[0], v[idx]), center = v[0];
	sort(v.begin() + 1, v.end(), ccw_center);
	stack<pv> st;
	for (int i = 1; i < int(v.size()); ++i) {
		if (!st.size()) {
			if (pv::cross(v[i] - v[0], v[i + 1] - v[0])) {
				st.push(v[0]);
				st.push(v[i]);
				st.push(v[i + 1]);
			}
			continue;
		}
		pv A = v[i];
		while (int(st.size()) > 2) {
			pv B = st.top(); st.pop();
			pv O = st.top(); st.pop();
			if (pv::cross(A - O, B - O) < 0) {
				st.push(O);
				st.push(B);
				break;
			}
			st.push(O);
		}
		st.push(A);
	}
	v.clear();
	for (; int(st.size()); st.pop())
		v.push_back(st.top());
	reverse(v.begin(), v.end());
}

double polygon_area () {
	double ans = 0;
	for (int i = 0; i < int(v.size()); ++i)
		ans += pv::cross(v[i], v[(i + 1) % int(v.size())]);
	return fabs(ans /2.0);
}

double polygon_perimeter () {
	double ans = 0;
	for (int i = 0; i < int(v.size()); ++i)
		ans += pv::norm(v[i] - v[(i + 1) % int(v.size())]);
	return ans;
}

bool point_inside_polygon (const pv P) {
	int lo = 1, hi = int(v.size()) - 2;
	while (lo <= hi) {
		const int mid = (lo + hi) >> 1;
		if (pv::cross(current - v[0], v[mid + 1] - v[0]) < 0)
			lo = mid + 1;
		else if (pv::cross(current - v[0], v[mid] - v[0]) > 0)
			hi = mid - 1;
		else
			return (pv::cross(current - v[0], v[mid + 1] - v[0]) >= 0 and
				pv::cross(current - v[0], v[mid] - v[0]) <= 0 and
				pv::cross(current - v[mid], v[mid + 1] - v[mid]) <= 0);
	}
	return false;
}

void sort_lowest_first () {
	int idx = 0;
	for (int i = 1; i < int(v.size()); ++i)
		if (v[i].x < v[idx].x or (v[i].x == v[idx].x and v[i].y < v[idx].y))
			idx = i;
	vector<pv> other;
	for (int i = idx; i < int(v.size()); ++i)
		other.push_back(v[i]);
	for (int i = 0; i < idx; ++i)
		other.push_back(v[i]);
	v = other;
}

int main() {
	return 0;
}