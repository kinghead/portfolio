#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;

int n, w;
struct col {
    int x, y;
};
col fir[1001], sec[1001];
int dp[1001][1001];

int func(int c1, int c2) {
    if (c1 == w || c2 == w)
        return 0;

    int& ref = dp[c1][c2];
    if (ref != -1)
        return ref;

    int np = max(c1, c2) + 1;
    int n1 = abs(fir[c1].x - fir[np].x) + abs(fir[c1].y - fir[np].y);
    int n2 = func(np, c2) + n1;

    int m1 = abs(sec[c2].x - sec[np].x) + abs(sec[c2].y - sec[np].y);
    int m2 = func(c1, np) + m1;

    return ref = min(n2, m2);
}

vector<int> v;
void tracking(int c1, int c2) {
    if (c1 == w || c2 == w)
        return;

    int np = max(c1, c2) + 1;
    int n1 = abs(fir[c1].x - fir[np].x) + abs(fir[c1].y - fir[np].y);
    int n2 = dp[np][c2] + n1;

    int m1 = abs(sec[c2].x - sec[np].x) + abs(sec[c2].y - sec[np].y);
    int m2 = dp[c1][np] + m1;

    if (n2 > m2) {
        v.push_back(2);
        tracking(c1, np);
    }
    else {
        v.push_back(1);
        tracking(np, c2);
    }
}

int main() {
    scanf("%d %d", &n, &w);

    fir[0] = { 1,1 };
    sec[0] = { n,n };
    for (int i = 1; i <= w; ++i) {
        scanf("%d %d", &fir[i].x, &fir[i].y);
        sec[i] = { fir[i].x, fir[i].y };
    }

    memset(dp, -1, sizeof(dp));
    printf("%d\n", func(0, 0));

    tracking(0, 0);
    for (auto a : v)
        printf("%d\n", a);

    return 0;
}
