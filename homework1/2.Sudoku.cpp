#include <iostream>
using namespace std;

bool row[10][10];
bool col[10][10];
bool squ[10][10];
int map[10][10];
bool dfs(int x, int y) {
    if (x == 10)
        return true;
    bool flag = false;
    if (map[x][y]) {
        return y == 9 ? dfs(x + 1, 1) : dfs(x, y + 1);
    } else {
        int k = 3 * ((x - 1) / 3) + (y - 1) / 3 + 1;
        // enumerate 1 to 9
        for (int i = 1; i <= 9; i++) {
            if (!row[x][i] && !col[y][i] && !squ[k][i]) {
                map[x][y] = i;
                row[x][i] = true;
                col[y][i] = true;
                squ[k][i] = true;
                if (y == 9)
                    flag = dfs(x + 1, 1);
                else
                    flag = dfs(x, y + 1);
                if (flag)
                    return true;
                else {
                    // recall
                    map[x][y] = 0;
                    row[x][i] = false;
                    col[y][i] = false;
                    squ[k][i] = false;
                }
            }
        }
    }
    return false;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));
        memset(squ, 0, sizeof(squ));
        for (int i = 1; i <= 9; i++) {
            for (int j = 1; j <= 9; j++) {
                char s;
                cin >> s;
                map[i][j] = s - '0';
                if (map[i][j]) {
                    int k = 3 * ((i - 1) / 3) + (j - 1) / 3 + 1;
                    row[i][map[i][j]] = true;
                    col[j][map[i][j]] = true;
                    squ[k][map[i][j]] = true;
                }
            }
        }
        dfs(1, 1);
        for (int i = 1; i <= 9; i++) {
            for (int j = 1; j <= 9; j++) {
                cout << map[i][j];
            }
            cout << endl;
        }
    }
    return 0;
}