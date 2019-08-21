//~ <template>

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(int(chrono::steady_clock::now().time_since_epoch().count()));

//~ </template>

class Employee {
  private:
    int age;
    int status;
    vector< Employee* > managers;

  public:
    Employee(const int & age) {
      this->status = 0;
      this->age = age;
    }

    void addManager(Employee* const & e) {
      this->managers.push_back(e);
    }

    void change(Employee* const & e) {
      swap(this->age, e->age);
    }

    int query(const int & queryCounter) {
      int ans = INT_MAX;
      this->status = queryCounter;
      for (Employee* const & e: managers) {
        if (e->status == queryCounter) {
          continue;
        }
        ans = min(ans, min(e->age, e->query(queryCounter)));
      }
      return ans;
    }
};

class Solution {
  private:
    int N, M, I;
    vector< int > idx;
    vector< Employee* > employees;

  public:
    Solution() {
      ios_base::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
    }

    void main() {
      while (cin >> N >> M >> I) {
        idx.resize(N);
        employees.resize(N);
        for (int i = 0; i < N; i += 1) {
          idx[i] = i;
          int age;
          cin >> age;
          delete(employees[i]);
          employees[i] = new Employee(age);
        }
        while (M-- > 0) {
          int x, y;
          cin >> x >> y;
          x -= 1;
          y -= 1;
          employees[y]->addManager(employees[x]);
        }
        int queryCounter = 0;
        while (I-- > 0) {
          char operation;
          cin >> operation;
          if (operation == 'T') {
            int x, y;
            cin >> x >> y;
            x -= 1;
            y -= 1;
            employees[idx[x]]->change(employees[idx[y]]);
            swap(idx[x], idx[y]);
          } else {
            int x;
            cin >> x;
            x -= 1;
            queryCounter += 1;
            const int &ans = employees[idx[x]]->query(queryCounter);
            if (ans == INT_MAX) {
              cout << '*' << '\n';
            } else {
              cout << ans << '\n';
            }
          }
        }
      }
    }
};

int main() {
  Solution().main();
  return 0;
}