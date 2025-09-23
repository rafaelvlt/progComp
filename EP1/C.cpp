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

int solve()
{
    string s; getline(cin, s);
    stack<char> p;
    for (char c : s){
        if (c == '(') p.push(')');
        else if(c == '[') p.push(']');
        else if (p.empty() || p.top() != c) return 0;
        else
            p.pop();
    }
    if (p.empty()) return 1;
    else return 0;

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

	int tt; cin >> tt;
	cin.ignore();
    while (tt--) {
        if (solve()) cout << "Yes\n";
        else cout << "No\n";
    }
	//solve();
	
	return 0;
}
