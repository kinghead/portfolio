#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 50;
const int INF = 987654321;

typedef struct
{
	int y, x;
}Dir;

Dir moveDir[8] = { {1, 0}, {1, 1}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1} };

int N;
string arr[MAX];
int tiredness[MAX][MAX];
bool visited[MAX][MAX];

int main(void)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;

	pair<int, int> start;
	int houses = 0;

	for (int i = 0; i < N; i++)
	{
		cin >> arr[i];

		for (int j = 0; j < N; j++)
		{
			if (arr[i][j] == 'P')
			{
				start = { i, j };
			}
			else if (arr[i][j] == 'K')
			{
				houses++;
			}
		}
	}

	vector<int> fatigue;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> tiredness[i][j];

			fatigue.push_back(tiredness[i][j]);
		}
	}

	sort(fatigue.begin(), fatigue.end());
	fatigue.erase(unique(fatigue.begin(), fatigue.end()), fatigue.end());

	int result = INF;
	int low = 0, high = 0;

	while (low < fatigue.size())
	{
		memset(visited, false, sizeof(visited));

		queue<pair<int, int>> q;
		int piro = tiredness[start.first][start.second];

		if (piro >= fatigue[low] && piro <= fatigue[high])
		{
			visited[start.first][start.second] = true;

			q.push({ start.first, start.second });
		}

		int K = 0;

		while (!q.empty())
		{
			int y = q.front().first;
			int x = q.front().second;
			q.pop();

			for (int k = 0; k < 8; k++)
			{
				int nextY = y + moveDir[k].y;
				int nextX = x + moveDir[k].x;

				if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= N || visited[nextY][nextX])
				{
					continue;
				}

				int piro = tiredness[nextY][nextX];

				if (piro >= fatigue[low] && piro <= fatigue[high])
				{
					visited[nextY][nextX] = true;

					q.push({ nextY, nextX });

					if (arr[nextY][nextX] == 'K')
					{
						K++;
					}
				}
			}
		}

		if (houses == K)
		{
			result = min(result, fatigue[high] - fatigue[low]);

			low++;
		}
		else if (high + 1 < fatigue.size())
		{
			high++;
		}
		else
		{
			break;
		}
	}

	cout << result << "\n";
	return 0;
}