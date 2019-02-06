// class for sorting around center
class center_comparator {
public:
  
  pv center;
  
  center_comparator(const pv &center) {
    this->center = center;
  }
  
  bool operator () (const pv &x, const pv &y) const {
    const auto &A = x - this->center;
    const auto &B = y - this->center;
    double cross = _2D::cross(A, B);
    if (cross > 0) {
      return true;
    }
    if (cross < 0) {
      return false;
    }
    if ((A.x < 0 and B.x >= 0) or (A.x >= 0 and B.x < 0)) {
      return A.x < B.x;
    }
    if ((A.y < 0 and B.y >= 0) or (A.y >= 0 and B.y < 0)) {
      return A.y < B.y;
    }
    return _2D::norm(A) < _2D::norm(B);
  }
};

// void build_convex_hull () {
//   if (int(v.size()) < 3)
//     return;
//   int idx = 0;
//   for (int i = 1; i < n; ++i)
//     if (v[i].x < v[idx].x or (v[i].x == v[idx].x and v[i].y < v[idx].y))
//       idx = i;
//   swap(v[0], v[idx]), center = v[0];
//   sort(v.begin() + 1, v.end(), ccw_center);
//   stack<pv> st;
//   for (int i = 1; i < int(v.size()); ++i) {
//     if (!st.size()) {
//       if (_2D::cross(v[i] - v[0], v[i + 1] - v[0])) {
//         st.push(v[0]);
//         st.push(v[i]);
//         st.push(v[i + 1]);
//       }
//       continue;
//     }
//     pv A = v[i];
//     while (int(st.size()) > 2) {
//       pv B = st.top(); st.pop();
//       pv O = st.top(); st.pop();
//       if (_2D::cross(A - O, B - O) < 0) {
//         st.push(O);
//         st.push(B);
//         break;
//       }
//       st.push(O);
//     }
//     st.push(A);
//   }
//   v.clear();
//   for (; int(st.size()); st.pop())
//     v.push_back(st.top());
//   reverse(v.begin(), v.end());
// }

// double polygon_area () {
//   double ans = 0;
//   for (int i = 0; i < int(v.size()); ++i)
//     ans += _2D::cross(v[i], v[(i + 1) % int(v.size())]);
//   return fabs(ans /2.0);
// }

// double polygon_perimeter () {
//   double ans = 0;
//   for (int i = 0; i < int(v.size()); ++i)
//     ans += _2D::norm(v[i] - v[(i + 1) % int(v.size())]);
//   return ans;
// }

// bool point_inside_polygon (const pv P) {
//   int lo = 1, hi = int(v.size()) - 2;
//   while (lo <= hi) {
//     const int mid = (lo + hi) >> 1;
//     if (_2D::cross(current - v[0], v[mid + 1] - v[0]) < 0)
//       lo = mid + 1;
//     else if (_2D::cross(current - v[0], v[mid] - v[0]) > 0)
//       hi = mid - 1;
//     else
//       return (_2D::cross(current - v[0], v[mid + 1] - v[0]) >= 0 and
//         _2D::cross(current - v[0], v[mid] - v[0]) <= 0 and
//         _2D::cross(current - v[mid], v[mid + 1] - v[mid]) <= 0);
//   }
//   return false;
// }

// void sort_lowest_first () {
//   int idx = 0;
//   for (int i = 1; i < int(v.size()); ++i)
//     if (v[i].x < v[idx].x or (v[i].x == v[idx].x and v[i].y < v[idx].y))
//       idx = i;
//   vector<pv> other;
//   for (int i = idx; i < int(v.size()); ++i)
//     other.push_back(v[i]);
//   for (int i = 0; i < idx; ++i)
//     other.push_back(v[i]);
//   v = other;
// }

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  return 0;
}