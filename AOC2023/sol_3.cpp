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
bool check_part(V<string>& grid, int r, int c){
    bool part = false;
    rep(i,r-1,r+2){
        rep(j,c-1,c+2){
            if(i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) continue; 
            part |= (grid[i][j] < '0' || grid[i][j] > '9') && grid[i][j] != '.';
        }
    }
    return part;
}
int get_val(V<string>& grid, int r, int c){
    if(r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size()) return 0; 
    if(grid[r][c] < '0' || grid[r][c] > '9') return 0;
    while(c >= 0 && grid[r][c] >= '0' && grid[r][c] <= '9') c--;
    int res = 0;
    for(c++; c < grid[0].size() && grid[r][c] >= '0' && grid[r][c] <= '9'; c++) res = res * 10 + (grid[r][c] - '0');
    return res;
}
int gear(V<string>& grid, int r, int c){
    if(grid[r][c] != '*') return 0;
    int u, d, l, r_; 
    u = get_val(grid,r-1,c);
    d = get_val(grid,r+1,c);
    l = get_val(grid,r,c-1);
    r_ = get_val(grid,r,c+1);
    int cnt = 0, prod = 1;
    if(u == 0){
        int ul = get_val(grid,r-1,c-1);
        if(ul != 0) cnt++, prod *= ul; 
        int ur = get_val(grid,r-1,c+1);
        if(ur != 0) cnt++, prod *= ur; 
    } else cnt++, prod *= u; 
    if(d == 0){
        int dl = get_val(grid,r+1,c-1);
        if(dl != 0) cnt++, prod *= dl; 
        int dr = get_val(grid,r+1,c+1);
        if(dr != 0) cnt++, prod *= dr; 
    } else cnt++, prod *= d; 
    if(r_ != 0) cnt++, prod *= r_; 
    if(l != 0) cnt++, prod *= l; 
    return (cnt == 2 ? 1 : 0) * prod;
}
int main(){
    fstream my_file;
	my_file.open("./AOC2023/input_3.txt", ios::in);
	//my_file.open("./AOC2023/ex_3.txt", ios::in);
    V<string> grid;
    string cur;
    while(getline(my_file,cur)){ grid.pb(cur); }
    int rows = grid.size(), cols = grid[0].size();

    int sum = 0;
    rep(i,0,rows){
        int val = 0;
        bool part = false;
        rep(j,0,cols){
            if(grid[i][j] >= '0' && grid[i][j] <= '9'){
                val = val*10 + (grid[i][j] - '0');
                part |= check_part(grid, i, j);
            } else {
                if(part) sum += val;
                part = false, val = 0;
            }
        }
        if(part) sum += val;
    }
    cout<<"Part 1: "<<sum<<endl;
    sum = 0;
    rep(i,0,rows){
        rep(j,0,cols){
            sum += gear(grid,i,j);
        }
    }
    cout<<"Part 2: "<<sum<<endl;
}

