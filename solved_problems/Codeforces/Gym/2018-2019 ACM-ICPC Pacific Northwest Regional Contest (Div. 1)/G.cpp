#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

class pv {
public:

	double x, y;
	
	pv () {}
	
	pv (const auto &x, const auto &y) {
		this->x = x;
		this->y = y;
	}
	
	pv operator - (const pv &other) const {
		return pv(x - other.x, y - other.y);
	}
};

class lrs {
public:

	pv start;
	pv finish;
	pv direction;

	lrs () {}
  
	lrs(const auto &start, const auto &finish) {
		this->start = start;
		this->finish = finish;
		this->direction = this->finish - this->start;
	}
};

double cross(const pv &A, const pv &B) {
	return (A.x * B.y) - (A.y * B.x);
}

double dot(const pv &A, const pv &B) {
	return (A.x * B.x) + (A.y * B.y);
}

double norm(const pv &P) {
	return sqrt(dot(P, P));
}

double distance_point_line(const pv &point, const lrs &line) {
	return fabs(cross(point - line.start, line.direction)) / norm(line.direction);
}

double distance_point_segment(const pv &point, const lrs &segment) {
	if (dot(point - segment.start, segment.finish - segment.start) < -EPS) {
		return norm(point - segment.start);
	}
	if (dot(point - segment.finish, segment.start - segment.finish) < -EPS) {
		return norm(point - segment.finish);
	}
	return distance_point_line(point, segment);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	vector< int > v;
	for (int i = 0; i < 6; i += 1) {
		int x;
		cin >> x;
		v.push_back(x);
	}
	vector< lrs > segments;
	segments.push_back(lrs(pv(v[2], v[3]), pv(v[4], v[3])));
	segments.push_back(lrs(pv(v[4], v[3]), pv(v[4], v[5])));
	segments.push_back(lrs(pv(v[4], v[5]), pv(v[2], v[5])));
	segments.push_back(lrs(pv(v[2], v[5]), pv(v[2], v[3])));
	double ans = LLONG_MAX;
	pv kappaloiro = pv(v[0], v[1]);
	for (const auto &segment: segments) {
		ans = min(ans, distance_point_segment(kappaloiro, segment));
	}
	cout << fixed << setprecision(3) << ans << endl;
	return 0;
}
