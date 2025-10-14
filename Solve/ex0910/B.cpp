#include <bits/stdc++.h>

using namespace std;

int solve(){
    int l, p; cin >> l >> p;
    if (l == 0) {
        cout << "YES\n";
        return 0;
    }
    vector<int> A(p);
    for (int i = 0 ; i < p; i++) {
        cin >> A[i];
    }
    vector<vector<int>> subsets(pow(2, p+1));
    for (int i = 0; i < (1 << p); i++){
        for (int j = 0; j < p; j++){
            if (i & (1 << j)){
                subsets[i].push_back(A[j]);
            }
        }
    }
   for (int i = 0; i < pow(2, p)+1; i++){
        if (accumulate(subsets[i].begin(), subsets[i].end(), 0) == l){
            cout << "YES\n";
            return 0;
        }
   }
   cout << "NO\n";
   return 0;
   
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int tt; cin >> tt; while(tt--) solve();
}