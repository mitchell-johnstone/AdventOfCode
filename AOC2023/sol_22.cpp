#include <algorithm>
#include <bits/stdc++.h>
#include <iterator>
#include <sstream>
#include <unordered_map>
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
#define all(x) x.begin(), x.end()

// fast io
void fast_io(){cin.tie(0)->sync_with_stdio(0);cin.exceptions(cin.failbit);}

// constants
const double PI = 3.1415926585323;
const int MOD = 1e9 + 7;

// -------------------MAIN CODE-------------------//
struct brick{
	int x,y,z,len; // lower left
	char dir;
	unordered_set<brick*> on, under;
};
brick getBrick(string s){
	int x[2], y[2], z[2];
	stringstream ss(s);
	char c;
	ss>>x[0]>>c>>y[0]>>c>>z[0]>>c>>x[1]>>c>>y[1]>>c>>z[1];
	int len = 1;
	len *= abs(x[1]-x[0])+1;
	len *= abs(y[1]-y[0])+1;
	len *= abs(z[1]-z[0])+1;
	if(x[1] != x[0]) c = 'x';
	else if(y[1] != y[0]) c = 'y';
	else c = 'z';
	return {min(x[0], x[1]), min(y[0], y[1]), min(z[0], z[1]), len, c};
}
int main(){
	ifstream inputFile("./AOC2023/input_22.txt");
	//ifstream inputFile("./AOC2023/ex_22.txt");
	V<string> lines;
	for(string cur; getline(inputFile,cur);) lines.pb(cur);

	V<brick> bs;
	for(string line : lines) bs.pb(getBrick(line));
	sort(all(bs),[=](brick& a, brick& b){return a.z < b.z;});
	// all x/y are non-negative
	V<V<pair<int,brick*>>> grid(1000,V<pair<int,brick*>>(1000,pair<int,brick*>(0,NULL)));
	for(brick& b : bs){
		if(b.dir == 'x' || b.dir == 'y'){
			int best = 0;
			unordered_set<brick*> on;
			int d = b.dir == 'x' ? 1 : 0;
			rep(i,0,b.len){
				pair<int,brick*> p = grid[b.x+i*d][b.y+i*(1-d)];
				if(p.second != NULL){
					if(best == p.first) {
						on.insert(p.second);
					} else if(best < p.first){
						best = p.first;
						on.clear();
						on.insert(p.second);
					}
				}
			}
			for(brick* o: on){
				b.on.insert(o);
				o->under.insert(&b);
			}
			rep(i,0,b.len){
				grid[b.x+i*d][b.y+i*(1-d)] = {best+1,&b};
			}
		} else {
			if(grid[b.x][b.y].second != NULL) {
				b.on.insert(grid[b.x][b.y].second);
				grid[b.x][b.y].second->under.insert(&b);
			}
			grid[b.x][b.y] = {b.len+grid[b.x][b.y].first,&b};
		}
	}
	ll possible = 0;
	for(brick& b : bs){
		if(b.under.size() == 0){
			possible++;
		} else {
			bool valid = true;
			for(brick* br : b.under){
				valid = valid && br->on.size() > 1;
			}
			if(valid) possible++;
		}
	}
	cout<<"PART 1: "<<possible<<endl;

	ll other = 0;
	for(brick& b : bs){
		unordered_set<brick*> collapsed = {&b};
		queue<brick*> next;
		for(brick* br : b.under) next.push(br);
		while(!next.empty()){
			brick* n = next.front();
			next.pop();
			bool valid = true;
			for(brick* test : n->on) valid = valid && collapsed.find(test) != collapsed.end();
			if(valid){
				collapsed.insert(n);
				for(brick* br : n->under) next.push(br);
			}
		}
		other += collapsed.size()-1;
	}
	cout<<"PART 2: "<<other<<endl;
}

