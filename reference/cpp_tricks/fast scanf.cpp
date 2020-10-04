#include <bits/stdc++.h>
using namespace std;

void scanint (int &x) {
    x = 0;
    register int c = getchar_unlocked();
    for (; c < 48 or c > 57; c = getchar_unlocked());
    for (; c > 47 and c < 58; c = getchar_unlocked())
        x = (x << 1) + (x << 3) + c - 48;
}

void scanint_negative (int &x) {
    x = 0;
    bool negative = false;
    register int c = getchar_unlocked();
    for (; (c < 48 or c > 57) and c != '-'; c = getchar_unlocked());
    if (c == '-')
        negative = true, c = getchar_unlocked();
    for (; c > 47 and c < 58; c = getchar_unlocked())
        x = (x << 1) + (x << 3) + c - 48;
    if (negative)
        x = -x;
}

int main () {
    int x; scanint(x);
    int y; scanint_negative(y);
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    return 0;
}
