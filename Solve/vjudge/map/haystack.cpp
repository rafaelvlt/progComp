//Macros
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define forn(i, n) for(int i=0; i < int(n); ++i)
#include <bits/stdc++.h>
//para compilar: 
//g++ -std=c++17 -O2 -Wall nome.cpp -o nome
//SE FOR DEBUGAR TIRAR O O2
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

void solve()
{
    int m, n; cin >> m >> n;
    map<string, int> dic;
    for (int i = 0; i < m; ++i){
        string a; int b; cin >> a >> b;
        dic[a] = b;
    }
    for (int i = 0; i < n; ++i){
        string word; cin >> word;
        int value = 0;
        while (word != "."){
            value += dic[word];
            cin >> word;
        }
        cout << value << '\n';
    } 
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	//#ifndef ONLINE_JUDGE
    //  freopen("input.txt", "r", stdin);
    //  freopen("output.txt", "w", stdout);
    //#endif


	//int tt; cin >> tt; while (tt--) solve();
	solve();
	
	return 0;
}
