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

// fast io
void fast_io(){cin.tie(0)->sync_with_stdio(0);cin.exceptions(cin.failbit);}

// constants
const double PI = 3.1415926585323;
const int MOD = 1e9 + 7;

// -------------------MAIN CODE-------------------//
ll dists(V<string>& lines, V<bool>& rows, V<bool>& cols, ll off){
    off--;
    ll res = 0, r_off = 0;
    V<pair<ll,ll>> gal;
    rep(i,0,lines.size()) {
        ll c_off = 0;
        if(rows[i]) r_off += off;
        else rep(j,0,lines[i].size()) {
            if(cols[j]) c_off += off;
            else if(lines[i][j] == '#'){
                for(auto p : gal) res += abs(p.first-(i+r_off)) + abs(p.second-(j+c_off));
                gal.pb({i+r_off,j+c_off});
            }
        }
    }
    return res;
}
int main(){
	ifstream inputFile("./AOC2023/input_11.txt");
	//ifstream inputFile("./AOC2023/ex_11.txt");
    V<string> lines;
    for(string cur; getline(inputFile,cur);) lines.pb(cur);

    V<bool> rows(lines.size(),true), cols(lines[0].size(),true); // empty rows and cols
    rep(i,0,lines.size()){
        rep(j,0,lines[0].size()){
            rows[i] = rows[i] && lines[i][j] == '.';
            cols[j] = cols[j] && lines[i][j] == '.';
        }
    }

    cout<<"PART 1: "<<dists(lines,rows,cols,2)<<endl;
    cout<<"PART 2: "<<dists(lines,rows,cols,1e6)<<endl;
}

