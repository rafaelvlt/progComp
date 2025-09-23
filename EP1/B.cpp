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
    vi ch(n);

    //A melhor solução era fazer um vetor de tamanho 5
    /*
    vi c(5,0)
    forn(i,n){
    int s; cin >> s;
    c[s]++;
    }
    então teriamos a qtd de crianças solo no idx 1, qtd de pares no idx 2, etc
    */
    forn(i,n) cin >> ch[i];
    sort(ch.begin(), ch.end());
    int ans = 0;

    auto idx = upper_bound(ch.begin(), ch.end(), 3);
    ans += ch.end() - idx;
    auto idxS = upper_bound(ch.begin(), idx, 1);
    int solo = idxS - ch.begin();
    auto idxP = upper_bound(idxS, idx, 2);
    int dup = idxP - idxS;
    auto idxT = upper_bound(idxP, idx, 3);
    int trio = idxT - idxP;
    
    /*dava pra dar min entre as crianças de 3 e 1
    então adicionar o resultado do min a uma var
    e depois subtrair do c[3] e c[1] essa var
    dai adicionava a var a resposta
    dps somava ans com os 3 que sobraram
    */
    ans += trio;
    solo -= trio;
    if (solo < 0) solo = 0;

    if (dup % 2 == 0) {
        ans += dup/2;
        dup = 0;
    }
    else{
        ans += dup/2;
        dup = 1;
    }
    if (dup == 1 && solo >= 2){
        ans += 1;
        dup = 0;
        solo -= 2;
    }

    //faz com que a divisão sempre arredonde para cima
    /*
    se for 0 : (0 + 3)/4 = 0
    se for 1; (1 + 3)/4 = 1;
    se for 2; (2 + 3)/4 = 1;
    etc
    */
    ans += (solo+dup+3)/4;
    

    cout << ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);



	//int tt; cin >> tt; while (tt--) solve();
	solve();
	
	return 0;
}
