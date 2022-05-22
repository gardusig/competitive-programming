// TODO

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long now = 0, nowDir = -1;
    
    vector < long long > v0, v1;

    for (int i=0; i<n; i++) {
        long long t, d;
        cin >> t >> d;
        if(d == 0) v0.push_back(t);
        else v1.push_back(t);
    }

    int i0 = 0, i1 = 0;

    if(v0.size() == 0) {
        now = v1[i1] + 10;
        i1++;
        nowDir = 1;
    }
    if(v1.size() == 0) {
        now = v0[i0] + 10;
        i0++;
        nowDir = 0;
    }

    if(v0.size() != 0 && v1.size() != 0) {
        if(v0[i0] <= v1[i1]) {
            now = v0[i0] + 10;
            nowDir = 0;
            i0++;
        } else {
            now = v1[i1] + 10;
            nowDir = 1;
            i1++;
        }
    }

    for (int i=1; i<n; i++) {
        if(nowDir == 0) {
            if(i0 < v0.size() && i1 < v1.size()) {
                if(v0[i0] <= now) {
                    now = max(now, v0[i0] + 10);
                    i0++;
                } else {
                    if(v0[i0] <= v1[i1]) {
                        now = v0[i0] + 10;
                        i0++;
                    }
                    else {
                        now = max(now, v1[i1]) + 10;
                        i1++;
                        nowDir = 1;
                    }
                }
            } else {
                if(i0 == (int)v0.size()) {
                    now = max(now, v1[i1]) + 10;
                    nowDir = 1;
                    i1++;
                } else {
                    now = max(now, v0[i0] + 10);
                    i0++;
                    nowDir = 0;
                }
            }
        } else {
            if(i0 < v0.size() && i1 < v1.size()) {
                if(v1[i1] <= now) {
                    now = max(now, v1[i1] + 10);
                    i1++;
                } else {
                    if(v1[i1] <= v0[i0]) {
                        now = v1[i1] + 10;
                        i1++;
                    }
                    else {
                        now = max(now, v0[i0]) + 10;
                        nowDir = 0;
                        i0++;
                    }
                }
            } else {
                if(i1 == (int)v1.size()) {
                    now = max(now, v0[i0]) + 10;
                    nowDir = 0;
                    i0++;
                } else {
                    now = max(now, v1[i1] + 10);
                    nowDir = 1;
                    i1++;
                }
            }
        }
    }
    
    cout << now << endl;
}