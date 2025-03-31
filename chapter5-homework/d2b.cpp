#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n = 56465;
    stack<int> s;
    while (n){
        s.push(n % 2);
        n /= 2;
    }
    while (!s.empty()){
        cout << s.top();
        s.pop();
    }
    return 0;
}