
#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char const *argv[]) {
    int n, b, p;
    cin >> n >> b >> p;
    int m = n;
    int player_bottles = 0, judge_bottles = 0;
    while ( m != 1 ) {
        int matches = trunc( log2( m ) );
        judge_bottles += matches;
        player_bottles += matches * b * 2;
        m -= matches;
    }
    cout << judge_bottles + player_bottles << " " << n * p << endl;
    return 0;
}