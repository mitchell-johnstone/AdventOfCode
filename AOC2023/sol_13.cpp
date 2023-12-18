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
ll checkH(V<string> grid){
    V<ll> ti;
    rep(i,0,grid.size()-1) if(grid[i] == grid[i+1]) ti.pb(i);
    for(int i : ti){
        ll diff = 1;
        bool reflect = true;
        for(ll diff = 1; reflect && i-diff >= 0 && i+diff+1 < grid.size(); diff++){
            reflect = reflect && grid[i-diff] == grid[i+diff+1];
        }
        if(reflect) return i+1;
    }
    return 0;
}
int dist(string& a, string& b){
    int diff = 0;
    rep(i,0,a.size()) diff += (a[i] == b[i] ? 0 : 1);
    return diff;
}
ll checkSmudge(V<string> grid){
    rep(i,0,grid.size()-1){
        int smudges = 0; 
        for(int diff = 0; i-diff >= 0 && i+diff+1 < grid.size(); diff++){
            smudges += dist(grid[i-diff],grid[i+diff+1]);
            if(smudges > 1) break;
        }
        if(smudges == 1) return i+1;
    }
    return 0;
}
V<string> transpose(V<string> grid){
    V<string> t(grid[0].size(), "");
    for(string line : grid)
        rep(i,0,line.size())
            t[i] += string(1,line[i]);
    return t;
}
int main(){
	ifstream inputFile("./AOC2023/input_13.txt");
	//ifstream inputFile("./AOC2023/ex_13.txt");
    V<string> lines;
    for(string cur; getline(inputFile,cur);) lines.pb(cur);

    ll res = 0;
    V<string> grid;
    for(string line : lines){
        if(!line.empty()){
            grid.pb(line);
        } else {
            res += checkH(transpose(grid)) + 100 * checkH(grid);
            grid.clear();
        }
    }
    res += checkH(transpose(grid)) + 100 * checkH(grid);
    cout<<"PART 1: "<<res<<endl;

    res = 0;
    grid.clear();
    for(string line : lines){
        if(!line.empty()){
            grid.pb(line);
        } else {
            res += checkSmudge(transpose(grid)) + 100 * checkSmudge(grid);
            grid.clear();
        }
    }
    res += checkSmudge(transpose(grid)) + 100 * checkSmudge(grid);
    cout<<"PART 2: "<<res<<endl;
}

