#include <bits/stdc++.h>
using namespace std;

// var types
typedef long long ll;
typedef long double ld;
#define nn '\n'
#define pb push_back
#define mp make_pair

// collection shorthand
#define V vector
typedef vector<int> vi;
typedef pair<int, int> pii;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()

// fast io
void fast_io(){cin.tie(0)->sync_with_stdio(0);cin.exceptions(cin.failbit);}

// constants
const double PI = 3.1415926585323;
const int MOD = 1e9 + 7;

// -------------------MAIN CODE-------------------//
void tiltW(V<string>& g){
    //for_each(all(g), [=](string& s) { 
    //        stable_sort(all(s), [=](char l, char r) {
    //                return l == '#' || r == '#' || l > r;
    //                });
    //        });
    for(string& s : g)
        rep(i,0,s.size())
            if(s[i] == 'O')
                for(int j = i; j > 0 && s[j-1] == '.'; j--){
                    s[j] = '.';
                    s[j-1] = 'O';
                }
}
void tiltE(V<string>& g){
    for(string& s : g)
        for(int i = s.size()-1; i >= 0; i--)
            if(s[i] == 'O')
                for(int j = i; j < s.size()-1 && s[j+1] == '.'; j++){
                    s[j] = '.';
                    s[j+1] = 'O';
                }
}
void tiltS(V<string>& g){
    for(int i = g.size()-1; i >= 0; i--)
        rep(k,0,g[0].size())
            if(g[i][k] == 'O')
                for(int j = i; j < g.size()-1 && g[j+1][k] == '.'; j++){
                    g[j][k] = '.';
                    g[j+1][k] = 'O';
                }
}
void tiltN(V<string>& g){
    rep(i,0,g[0].size())
        for(auto last = g.begin(), cur = g.begin(); cur != g.end(); cur++)
            if((*cur)[i] == 'O') swap((*cur)[i], (*last)[i]), last++;
            else if((*cur)[i] == '#') last = next(cur);

//    rep(i,0,g.size())
//        rep(k,0,g[0].size())
//            if(g[i][k] == 'O')
//                for(int j = i; j > 0 && g[j-1][k] == '.'; j--){
//                    g[j][k] = '.';
//                    g[j-1][k] = 'O';
//                }
}
int weighN(V<string>& g){
    int res = 0;
    rep(i,0,g.size())
        res += (g.size()-i) * count(g[i].cbegin(), g[i].cend(), 'O');
    return res;
}
void spin(V<string>& g){
    map<V<string>, int> m;
    int to = 1000000000;
    rep(i,0,to){
        tiltN(g);
        tiltW(g);
        tiltS(g);
        tiltE(g);
        if(m.find(g) != m.end()) to = i + ((to-i) % (i-m[g]));
        m[g] = i;
    }
}
int main(){
	ifstream inputFile("./AOC2023/input_14.txt");
	//ifstream inputFile("./AOC2023/ex_14.txt");
    V<string> lines;
    for(string cur; getline(inputFile,cur);) lines.pb(cur);
    tiltN(lines);
    cout<<"PART 1: "<<weighN(lines)<<endl;
    spin(lines);
    cout<<"PART 2: "<<weighN(lines)<<endl;
}

