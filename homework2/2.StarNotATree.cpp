// #define ORIGINAL

#include <algorithm>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
using namespace std;

const int INF = numeric_limits<int>::max();
const double EPS = 1e-8;       // 搜索条件阈值
const double DELTA = 0.99975;  // 温度下降速度
const int T = 100;             // 初始温度

const int dxy[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    double operator-(const Point& b) const {
        return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
    }
};
Point p[1005];
int n;

double getDistanceSum(Point t) {
    double sum = 0;
    for (int i = 1; i <= n; i++)
        sum += p[i] - t;
    return sum;
}

// 模拟退火
double simulatedAnnealing() {
    // 以下三行用于初始化随机数生成器（C++推荐写法），等同于C语言中的 rand() srand()
    static default_random_engine e;                               // 设置随机数生成引擎
    static uniform_int_distribution<int> intRandom(0, 3);         // 整型随机数分布
    static uniform_real_distribution<double> doubleRandom(0, 1);  // 浮点型随机数分布
    Point result;                                                 // 移动的结果
    Point source = p[0];  // 移动的出发点。最初的选择是随机的，这里使用 p[0]
    double t = T;         // 初始化温度
    double ans = INF;     // 初始答案
    while (t > EPS) {
        int direction = intRandom(e);  // 随机选择移动方向
        result.x = source.x + dxy[direction][0];
        result.y = source.y + dxy[direction][1];
        // 计算答案
        double cur = getDistanceSum(result);
        // 若此移动导致状态变好则采取此移动
        if (ans > cur) {
            ans = cur;
            source = result;
        } else {
            // 否则仅有一定概率采取此移动
            if (doubleRandom(e) < exp((ans - cur) / t)) {
                ans = cur;
                source = result;
            }
        }
        // 走一步退一次火
        t *= DELTA;
    }
    // 当温度小于阈值时就可以输出了
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n) {
        for (int i = 1; i <= n; i++) {
            cin >> p[i].x >> p[i].y;
        }
        // 不能转换成 int（向零取整），要四舍五入
        cout << fixed << setprecision(0) << simulatedAnnealing() << endl;
    }
    return 0;
}
