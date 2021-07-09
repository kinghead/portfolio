#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <memory.h>

using namespace std;

const int NODE = 26;

int dy[8] = { -1,-1,-1,0,0,1,1,1 };
int dx[8] = { -1,0,1,-1,1,-1,0,1 };

char arr[10][10];
bool visit[10][10];
string maxStr;
int maxCnt, sz, total;
int tc;
struct TRIE {
    TRIE* next[NODE];
    bool isEnd;
    int isVisited;

    TRIE() {
        for (int i = 0; i < NODE; i++)
            next[i] = nullptr;
        isEnd = isVisited = false;
    }
    ~TRIE() {
        for (int i = 0; i < NODE; i++)
            if (next[i])
                delete next[i];
    }
};

bool chkRange(int y, int x)
{
    return ((0 <= x && x < 4) && (0 <= y && y < 4)) ? true : false;
}

void go(int y, int x, int cnt, TRIE* cur, string str) {

    int nowCh = arr[y][x] - 'A';
    //cout << "y :: " << y << " x ::" << x << " cnt :: " << cnt << " str :: " << str << endl;
    //    cout << "nowCh :: " << (char)(nowCh + 'A')  << endl;
    if (cnt == 8 || !cur->next[nowCh])
        return;
    if (cur->next[nowCh]->isEnd && cur->next[nowCh]->isVisited != tc)
    {
        cur->next[nowCh]->isVisited = tc;
        if (cnt + 1 == 3 || cnt + 1 == 4)
            total += 1;
        else if (cnt + 1 == 5)
            total += 2;
        else if (cnt + 1 == 6)
            total += 3;
        else if (cnt + 1 == 7)
            total += 5;
        else if (cnt + 1 == 8)
            total += 11;

        sz++;
        if (cnt + 1 > maxCnt) {
            maxStr = str + (char)(nowCh + 'A');
            maxCnt = cnt + 1;
        }
        else if (cnt + 1 == maxCnt)
            if (maxStr > (str + (char)(nowCh + 'A')))
                maxStr = str + (char)(nowCh + 'A');
    }

    for (int i = 0; i < 8; i++)
    {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (!chkRange(ny, nx) || visit[ny][nx])
            continue;

        visit[y][x] = true;
        str += arr[y][x];
        go(ny, nx, cnt + 1, cur->next[nowCh], str);
        visit[y][x] = false;
        str.pop_back();
    }

}

int _strlen(char* tmp) {
    int len = 0;
    while (tmp[++len]) {}
    return len;
}

TRIE* root;
int main()
{
    root = new TRIE;

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        char tmp[10];
        scanf("%s", tmp);

        TRIE* pos = root;
        for (int i = 0; tmp[i]; i++) {
            int nowCh = tmp[i] - 'A';

            if (!pos->next[nowCh])
                pos->next[nowCh] = new TRIE;

            pos = pos->next[nowCh];
        }

        pos->isEnd = true;
    }

    int m;
    scanf("%d", &m);

    for (tc = 1; tc <= m; tc++)
    {
        memset(visit, 0, sizeof(visit));
        sz = maxCnt = total = 0;
        maxStr.clear();

        for (int i = 0; i < 4; i++)
            scanf("%s", arr[i]);

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                int nowCh = arr[i][j] - 'A';
                if (root->next[nowCh])
                    go(i, j, 0, root, "");
            }
        cout << total << " " << maxStr << " " << sz << endl;
    }
    return 0;
}

