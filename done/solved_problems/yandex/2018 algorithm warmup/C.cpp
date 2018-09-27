#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;

class pv {
public:
	double x, y;
	pv () {}
	pv (const double _x, const double _y) {
		x = _x, y = _y;
	}
	pv operator + (const pv other) const {
		return pv(x + other.x, y + other.y);
	}
	pv operator - (const pv other) const {
		return pv(x - other.x, y - other.y);
	}
	pv operator / (const double k) const {
		return pv(x / k, y / k);
	}
	bool operator == (const pv other) const {
		return fabs(x - other.x) + fabs(y - other.y) < EPS;
	}
	static double cross (const pv A, const pv B) {
		return (A.x * B.y) - (A.y * B.x);
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
	static bool point_inside_line (const pv point, const lrs line) {
		return (fabs(pv::cross(point - line.start, line.direction)) < EPS);
	}
};

int main () {
	vector<pv> v;
	int n; scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int type; scanf("%d", &type);
		if (!type) {
			int r, x, y; scanf("%d %d %d", &r, &x, &y);
			v.push_back(pv(x, y));
		}
		else {
			vector<pv> current_rectangle;
			for (int j = 0; j < 4; ++j) {
				int x, y; scanf("%d %d", &x, &y);
				current_rectangle.push_back(pv(x, y));
			}
			v.push_back(current_rectangle[0] + ((current_rectangle[2] - current_rectangle[0]) / 2));
		}
	}
	if (int(v.size()) < 3)
		return !printf("%s\n", "Yes");
	vector<lrs> available;
	for (auto i : v) {
		if (!(i == v[0])) {
			if (!available.size())
				available.push_back(lrs(v[0], i));
			else if (!lrs::point_inside_line(i, available[0]))
				return !printf("%s\n", "No");
		}
	}
	return !printf("%s\n", "Yes");
}