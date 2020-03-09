// Time: 30 min
#include <iostream>
using namespace std;

int buf[9] = {};
int pos[9] = {};

void search(int k) {
    if (k > 8) {
        for (int i = 1; i <= 8; i++) {
            cout << pos[i] << "\n "[i < 8];
        }
        exit(0);
    }
    int x = 0;
    for (int i = 1; i < k; i++) {
        x |= (buf[i] | buf[i] << (k - i) | buf[i] >> (k - i));
    }
    for (int i = 1; i <= 8; i++) {
        if (!(x & 1 << i)) {
            pos[k] = i;
            buf[k] = 1 << i;
            search(k + 1);
        }
    }
}

int main() {
    cin >> pos[1] >> pos[2];
    buf[1] = 1 << pos[1];
    buf[2] = 1 << pos[2];
    search(3);
}