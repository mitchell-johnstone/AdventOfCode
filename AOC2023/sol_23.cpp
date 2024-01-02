#include <bits/stdc++.h>
using namespace std;

// var types
typedef long long ll;
typedef long double ld;
#define nn '\n'
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()

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
enum dir {up,down,left,right};
int dfs(V<string>& lines, pii&& cur){
	if(!(cur.first >= 0 && cur.first < lines.size() && cur.second >= 0 && cur.second < lines[0].size())) return -1000000;
	char c = lines[cur.first][cur.second];
	if(c == '#') return -1000000;
	if(cur.first == lines.size()-1) return 0;
	lines[cur.first][cur.second] = '#';
	int res = -10000000;
	if(c == 'v') {
		res = 1+dfs(lines, {cur.first+1, cur.second});
	} else if(c == '>') {
		res = 1+dfs(lines, {cur.first, cur.second+1});
	} else {
		res = max(res,1+dfs(lines, {cur.first+1, cur.second}));
		res = max(res,1+dfs(lines, {cur.first-1, cur.second}));
		res = max(res,1+dfs(lines, {cur.first, cur.second+1}));
		res = max(res,1+dfs(lines, {cur.first, cur.second-1}));
	}
	lines[cur.first][cur.second] = c;
	return res;
}
int dfs2(V<string>& lines, pii&& cur){
	if(!(cur.first >= 0 && cur.first < lines.size() && cur.second >= 0 && cur.second < lines[0].size())) return -1000000;
	char c = lines[cur.first][cur.second];
	if(c == '#') return -1000000;
	if(cur.first == lines.size()-1) return 0;
	lines[cur.first][cur.second] = '#';
	int res = -10000000;
	res = max(res,1+dfs2(lines, {cur.first+1, cur.second}));
	res = max(res,1+dfs2(lines, {cur.first-1, cur.second}));
	res = max(res,1+dfs2(lines, {cur.first, cur.second+1}));
	res = max(res,1+dfs2(lines, {cur.first, cur.second-1}));
	lines[cur.first][cur.second] = c;
	return res;
}
int main(){
	ifstream inputFile("./AOC2023/input_23.txt");
	//ifstream inputFile("./AOC2023/ex_23.txt");
	V<string> lines;
	for(string cur; getline(inputFile,cur);) lines.pb(cur);
	int res = 0;
	rep(i,0,lines[0].size()) res = max(res,dfs(lines,{0,i}));
	cout<<"PART 1: "<<res<<endl;

	// 6556 is too high
	res = 0;
	rep(i,0,lines[0].size()) res = max(res,dfs2(lines,{0,i}));
	cout<<"PART 2: "<<res<<endl;
}

