// Time: 2 min
#include <iostream>
using namespace std;
bool s[10002] = {};
int main() {
    int n;
    cin >> n;
    while (n--) {
        int k;
        cin >> k;
        if (s[k]) {
            cout << k << endl;
            return 0;
        }
        s[k] = true;
    }
}