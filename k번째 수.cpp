#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <string>
#include <stack>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int INF = 987654321;
const int mod = 1e9 + 7;

int lessthanX(int qs, int qe, int x, int idx, int s, int e);
vector<vector<int>> mergeseg;
vector<int> vec;
int n, m;

vector<int> merge(const vector<int>& lvec, const vector<int>& rvec, vector<int>& ret)
{
    int l = 0, r = 0;
    int lsize = lvec.size();
    int rsize = rvec.size();

    while (l < lsize && r < rsize)
    {
        if (lvec[l] < rvec[r])
        {
            ret.push_back(lvec[l]);
            l++;
        }
        else
        {
            ret.push_back(rvec[r]);
            r++;
        }
    }

    while (l == lsize && r < rsize)
    {
        ret.push_back(rvec[r]);
        r++;
    }

    while (r == rsize && l < lsize)
    {
        ret.push_back(lvec[l]);
        l++;
    }

    return ret;
}

void Init(int idx, int s, int e)
{
    if (s == e)
    {
        mergeseg[idx] = vector<int>(1, vec[s]);
        return;
    }

    int m = (s + e) / 2;

    Init(2 * idx, s, m);
    Init(2 * idx + 1, m + 1, e);
    merge(mergeseg[2 * idx], mergeseg[2 * idx + 1], mergeseg[idx]);
}

int bisearch(int qs, int qe, int xs, int xe, int k)
{
    if (xs >= xe) return xe;

    if (xs == xe - 1)
    {
        if (lessthanX(qs, qe, xe, 1, 0, n - 1) < k) return xe;
        else return xs;
    }

    int xm = (xs + xe) / 2;

    if (lessthanX(qs, qe, xm, 1, 0, n - 1) < k) return bisearch(qs, qe, xm, xe, k);
    else return bisearch(qs, qe, xs, xm - 1, k);
}

int lessthanX(int qs, int qe, int x, int idx, int s, int e)
{
    if (e < qs || qe < s) return 0;

    if (qs <= s && e <= qe)
    {
        auto it = lower_bound(mergeseg[idx].begin(), mergeseg[idx].end(), x);

        return it - mergeseg[idx].begin();
    }

    int m = (s + e) / 2;

    return lessthanX(qs, qe, x, 2 * idx, s, m) + lessthanX(qs, qe, x, 2 * idx + 1, m + 1, e);
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


    cin >> n >> m;

    mergeseg = vector<vector<int>>((4 * n));
    vec = vector<int>(n);

    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
    }

    Init(1, 0, n - 1);
    for (int x = 0; x < m; x++)
    {
        int i, j, k;
        cin >> i >> j >> k;

        i--; j--;
        cout << bisearch(i, j, -1e9, 1e9, k) << "\n";
    }
    return 0;
}