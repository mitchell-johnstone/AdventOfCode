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
int energize(V<string> lines, complex<double> ps, complex<double> dr){
	V<V<bool>> grid(lines.size(), V<bool>(lines[0].size(),false));;
	V<pair<complex<double>,complex<double>>> locs, seen;
	// real = row
	// imag = col
	locs.pb(mp(ps, dr));
	
	while(!locs.empty()){
		auto p = locs.back();
		locs.pop_back();

		if(find(seen.begin(), seen.end(), p) == seen.end()){
			seen.pb(p);
			complex<double> pos = p.first, dir = p.second;

			if(pos.real() < 0 || pos.real() >= lines.size() || pos.imag() < 0 || pos.imag() >= lines[0].size()) continue;

			// eval where we are!
			grid[pos.real()][pos.imag()] = true;

			char c = lines[pos.real()][pos.imag()];

			if(c == '|' && dir.real() == 0){
				dir = 1;
				locs.pb(mp(pos+dir,dir));
				dir = -1;
				locs.pb(mp(pos+dir,dir));
				continue;
			}
			if(c == '-' && dir.imag() == 0){
				dir = 1j;
				locs.pb(mp(pos+dir,dir));
				dir = -1j;
				locs.pb(mp(pos+dir,dir));
				continue;
			}
			if(c == '/') dir = -1 * dir.imag() + -1j * dir.real();
			if(c == '\\') dir = dir.imag() + 1j * dir.real();
			locs.pb(mp(pos+dir,dir));
		}
	}

	int res = 0;
	for(V<bool> v : grid)  for(bool b : v) if(b) res++;
	return res;
}
int main(){
	ifstream inputFile("./AOC2023/input_16.txt");
	//ifstream inputFile("./AOC2023/ex_16.txt");
	V<string> lines;
	for(string cur; getline(inputFile,cur);) lines.pb(cur);

	cout<<"PART 1: "<<energize(lines,0,1j)<<endl;

	int res = 0;
	rep(i,0,lines.size()){
		cout<<"LINE: "<<i+1<<"/"<<lines.size()<<endl;
		if(i == 0){ // from top
			rep(k,0,lines[0].size()){
				res = max(res, energize(lines,i+1j * k, 1));
			}
		}
		if(i == lines.size()-1){ // from bottom
			rep(k,0,lines[0].size()){
				res = max(res, energize(lines,i+1j * k, -1));
			}
		}
		res = max(res, energize(lines, i, 1j));
		res = max(res, energize(lines, i+(1j * (lines[0].size()-1)), -1j));
	}
	cout<<"PART 2: "<<res<<endl;
}

