#include <cstring>
#include <iostream>
using namespace std;

char state[5][5];
int chess, resultX, resultY;
bool check(int x, int y) {
    int tot = 0;
    //横向判断
    for (int i = 0; i < 4; i++)
        if (state[x][i] == 'o')
            tot++;
        else if (state[x][i] == 'x')
            tot--;
    if (tot == 4 || tot == -4)
        return true;
    tot = 0;
    //纵向判断
    for (int i = 0; i < 4; i++)
        if (state[i][y] == 'o')
            tot++;
        else if (state[i][y] == 'x')
            tot--;
    if (tot == 4 || tot == -4)
        return true;
    tot = 0;
    //正对角线判断
    for (int i = 0; i < 4; i++)
        if (state[i][i] == 'o')
            tot++;
        else if (state[i][i] == 'x')
            tot--;
    if (tot == 4 || tot == -4)
        return true;
    tot = 0;
    //反对角线判断
    for (int i = 0; i < 4; i++)
        if (state[i][3 - i] == 'o')
            tot++;
        else if (state[i][3 - i] == 'x')
            tot--;
    if (tot == 4 || tot == -4)
        return true;
    return false;
}
int minSearch(int, int);
int maxSearch(int x, int y) {
    //已经结束
    if (check(x, y))
        return -1;
    //平局
    if (chess == 16)
        return 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (state[i][j] == '.') {
                state[i][j] = 'x';
                chess++;
                int tmp = minSearch(i, j);
                state[i][j] = '.';
                chess--;
                //对方需要找的最差估价，如果当前比之前最差的高，剪枝
                if (tmp == 1)
                    return 1;
            }
    return -1;
}
int minSearch(int x, int y) {
    //已经结束
    if (check(x, y))
        return 1;
    //平局
    if (chess == 16)
        return 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (state[i][j] == '.') {
                state[i][j] = 'o';
                chess++;
                int tmp = maxSearch(i, j);
                state[i][j] = '.';
                chess--;
                //自己需要找的最高估价，如果当前比之前最差的低，剪枝
                if (tmp == -1 || tmp == 0)
                    return -1;
            }
    return 1;
}
bool solve() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            //枚举，然后搜索
            if (state[i][j] == '.') {
                state[i][j] = 'x';
                chess++;
                int tmp = minSearch(i, j);
                state[i][j] = '.';
                chess--;
                if (tmp == 1) {
                    resultX = i;
                    resultY = j;
                    return true;
                }
            }
    return false;
}
int main() {
    char ch;
    while (cin >> ch, ch != '$') {
        chess = 0;
        for (int i = 0; i < 4; i++) {
            cin >> state[i];
            for (int j = 0; j < 4; j++) {
                chess += state[i][j] != '.';
            }
        }
        if (chess <= 4) {  //强力剪枝
            cout << "#####" << endl;
            continue;
        }
        if (solve())
            cout << "(" << resultX << "," << resultY << ")" << endl;
        else
            cout << "#####" << endl;
    }
    return 0;
}