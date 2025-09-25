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
    int n; cin >> n;
    priority_queue<int> A;
    forn(i, n){
        int b; cin >> b;
        A.push(b);
    }
    deque<int> sub;
    
    while(A.size() > 1){
        for(i = 0, i < 3; i++) 
        {
            sub.push_front(A.front());   
            A.pop();
        }

        if ((sub[0] + sub[1]> sub[2]) && (sub[0] + sub[2] > sub[1]) && (sub[1] + sub[2] > sub[0])){
            A.push(sub[0]);
            sub.clear();
        }
        
    }
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	#ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif


	int tt; cin >> tt; while (tt--) solve();
	//solve();
	
	return 0;
}
