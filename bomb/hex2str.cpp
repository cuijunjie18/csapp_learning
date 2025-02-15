#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    string ans = "";
    unsigned int n;
    while (cin >> hex >> n){
        cout << hex << n << "\n";
        while (n){
            int x = n % 256;
            ans += x;
            n /= 256;
        }
    }
    cout << ans << "\n";
    return 0;
}