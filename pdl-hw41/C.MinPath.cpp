// Time: 50 min
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

int n;
int dis[102][102];

void floyd() {
    for (int k = 1; k <= n; k++) {  // Enum transits first
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j || j == k || k == i)
                    continue;
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> dis[i][j];
        }
    }
    floyd();
    cout << dis[1][n] << endl;
}