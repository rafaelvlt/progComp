#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct UnionFind{
    vector<int> parent;
    vector<int> size;

    UnionFind(int n){
        parent.resize(n+1);
        iota(parent.begin() + 1, parent.end(), 1); 
        size.assign(n+1, 1);
    }

    int find(int i){
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j)    {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j)   {
            if (size[root_i] < size[root_j]) swap(root_i, root_j);
            
            parent[root_j] = root_i;
            size[root_i] += size[root_j];
        }
    }

    int getSize(int i){
        return size[find(i)];
    }
};

int main(){
    int n, m; cin >> n >> m;
    UnionFind uf(n);
    int maxRank = 0;

    while (m--){
        int a, b; cin >> a >> b;
        uf.unite(a, b);
    }
    for (int i  = 0; i <= n ; i++){
        maxRank = max(maxRank, uf.getSize(i));
    }

    ll ans = 1;
    if (maxRank > 0) ans = pow(2, maxRank-1);
    else ans = 1;
    cout << ans << '\n';

    return 0;
}