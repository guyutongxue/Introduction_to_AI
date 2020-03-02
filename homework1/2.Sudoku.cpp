// COPIED CODE, NEED REVIEW
// COPIED CODE, NEED REVIEW
// COPIED CODE, NEED REVIEW

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

bool row[10][10];  //横向 row[i][x]标记在第i行中数字x是否出现了
bool col[10][10];  //纵向 col[j][y]  标记在第j列中数字y是否出现了
bool squ[10][10];  //方块 squ[k][x] 标记在第k个3*3子格中数字z是否出现了
int map[10][10];
bool dfs(int x, int y) {
    if (x == 10)
        return true;
    bool flag = false;
    if (map[x][y]) {
        if (y == 9)
            flag = dfs(x + 1, 1);
        else
            flag = dfs(x, y + 1);

        if (flag)
            return true;
        else
            return false;
    } else {
        int k = 3 * ((x - 1) / 3) + (y - 1) / 3 + 1;
        //从1-9中枚举能放的数
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
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));
        memset(squ, 0, sizeof(squ));

        char t[10][10];
        for (int i = 1; i <= 9; i++) {
            for (int j = 1; j <= 9; j++) {
                cin >> t[i][j];
                map[i][j] = t[i][j] - '0';
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
            for (int j = 1; j <= 9; j++)
                printf("%d", map[i][j]);
            printf("\n");
        }
    }
    return 0;
}