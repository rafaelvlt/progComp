#include <bits/stdc++.h>

using namespace std;

int main(){
    int n, m; cin >> n >> m;
    map<int, int> A;
    int maxRank = 0;
    while(m--){
        int a, b; cin >> a >> b;
        if (A[a] > A[b] || A[a] > 0) {
            A[a] += 1;
            maxRank = max(A[a], maxRank);
        }
        else if (A[b] > A[a] || A[a] > 0){
             A[b] += 1;
            maxRank = max(A[b], maxRank);
            }
        else {
            A[a] += 1;
            maxRank = max(A[a], maxRank);
        }

    }
    long long ans = pow(2, maxRank);
    cout << ans;
}