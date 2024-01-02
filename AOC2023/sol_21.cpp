#include <bits/stdc++.h>
#include <functional>
#include <unordered_set>
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
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	P origin(V<string>& lines) { 
		T nx = x%lines.size();
		while(nx < 0) nx+=lines.size();
		T ny = y%lines[0].size();
		while(ny < 0) ny+=lines[0].size();
		return P(nx, ny); 
	}
	double dist() const { return abs(x)+abs(y); }
};
template <class A>
struct hash<Point<A>>{
	size_t operator()(const Point<A>& p) const {
		return p.x * 10000 + p.y;
		 //return hash<A>{}(p.x) ^ hash<A>{}(p.y);
	}
};
typedef Point<ll> P;
int main(){
	ifstream inputFile("./AOC2023/input_21.txt");
	//ifstream inputFile("./AOC2023/ex_21.txt");
	V<string> lines;
	for(string cur; getline(inputFile,cur);) lines.pb(cur);

	//V<V<int>> cur;
	//for(string line : lines){
	//	cur.pb(V<int>());
	//	for(char c : line){
	//		cur.back().pb(c=='S' ? 0 : c=='#' ? -2 : -1);
	//	}
	//}
	//auto within = [=](pii pt, V<string>& lines){
	//	return pt.first >= 0 && pt.first < lines.size() && pt.second>= 0 && pt.second < lines[0].size();
	//};
	//while(cur[0][0] == -1){
	//	V<V<int>> next(cur.size(),V<int>(cur[0].size(),-1));
	//	rep(r,0,lines.size()){
	//		rep(c,0,lines[0].size()){
	//			next[r][c] = cur[r][c];
	//			if(cur[r][c] == -1) {
	//				if(r > 0 && cur[r-1][c] >= 0) next[r][c] = max(next[r][c], cur[r-1][c]+1);
	//				if(r < cur.size()-1 && cur[r+1][c] >= 0) next[r][c] = max(next[r][c], cur[r+1][c]+1);
	//				if(c > 0 && cur[r][c-1] >= 0) next[r][c] = max(next[r][c], cur[r][c-1]+1);
	//				if(c < cur.size()-1 && cur[r][c+1] >= 0) next[r][c] = max(next[r][c], cur[r][c+1]+1);
	//			}
	//		}
	//	}
	//	rep(r,0,lines.size()) {
	//		rep(c,0,lines.size()) cout<<setw(4)<<setfill(' ')<<cur[r][c];
	//		cout<<endl;
	//	}
	//	swap(next,cur);
	//}
	//cout<<cur[0][0]<<endl;
	//cout<<cur.back()[0]<<endl;
	//cout<<cur[0].back()<<endl;
	//cout<<cur.back().back()<<endl;
	//ll res = 0;
	//for(V<bool> v : cur) for (bool b : v) if(b) res++;
	//cout<<"PART 1: "<<res<<endl;
	
	auto within = [=](P pt, V<string>& lines){
		return pt.x >= 0 && pt.x < lines.size() && pt.y >= 0 && pt.y < lines[0].size();
	};
	P up(-1,0), down(1,0), left(0,-1), right(0,1);

	unordered_set<P> seen, cur, next;
	rep(r,0,lines.size()) rep(c,0,lines[0].size()){
		if(lines[r][c] == 'S') cur.insert(P(r,c));
		if(lines[r][c] == '#') seen.insert(P(r,c));
	}

	ll steps = 64;
	ll cnt[2] = {0,0};
	rep(step,0,steps+1){
		for(P p : cur){
			if(seen.find(p) != seen.end()) continue;
			if(!within(p,lines)) continue;
			seen.insert(p);
			cnt[step&1]++;
			next.insert(p+up);
			next.insert(p+down);
			next.insert(p+left);
			next.insert(p+right);
		}
		cur = next;
		next.clear();
	}
	cout<<"PART 1: "<<cnt[steps&1]<<endl;

	seen.clear(), cur.clear(), next.clear();
	unordered_set<P> wall;
	rep(r,0,lines.size()) rep(c,0,lines[0].size()){
		if(lines[r][c] == 'S') cur.insert(P(r,c));
		if(lines[r][c] == '#') wall.insert(P(r,c));
	}
	P start = *(cur.begin());
	cout<<start.x<<" "<<start.y<<endl;

	ll inside[2] = {0,0};
	ll outside[2] = {0,0};
	ll count = 0;
	for(int step = 0; !cur.empty(); step++){
		for(P p : cur){
			if(wall.find(p) != wall.end()) continue;
			if(!within(p, lines)) continue;
			if(seen.find(p) != seen.end()) continue;
			seen.insert(p);
			count++;
			if((p-start).dist() <= 65) inside[step&1]++;
			else outside[step&1]++;
			next.insert(p+up);
			next.insert(p+down);
			next.insert(p+left);
			next.insert(p+right);
		}
		swap(cur,next);
		next.clear();
	}
	steps = 26501365/131;
	ll res = inside[1];

	// Too high: 732075201817458
	// still high  732075210718680
	// Too low:  598044223436180
	rep(i,1,steps+1){
		res += (outside[0] + outside[1]) * 4 * i / 2; // div by 2 because of copy
		res += inside[(i-1)&1] * 4 * i;
	}

	cout<<lines.size()<<"x"<<lines[0].size()<<endl;
	cout<<"WALL: "<<wall.size()<<endl;
	cout<<"NON WALL: "<<(lines.size() * lines[0].size()) - (wall.size())<<endl;

	cout<<"INSIDE: "<<inside[0] + inside[1]<<endl;
	cout<<"OUTSIDE: "<<outside[0] + outside[1]<<endl;
	cout<<"TOTAL: "<<inside[0] + inside[1] + outside[0] + outside[1]<<endl;
	cout<<"TOTAL C: "<<count<<endl;

	cout<<steps/131<<endl;
	cout<<steps%131<<endl;
	cout<<"PART 2: "<<res<<endl;
	rep(r,0,lines.size()){ rep(c,0,lines[0].size()) {
		if(wall.find(P(r,c)) != wall.end()) cout<<"W";
		else if(seen.find(P(r,c)) != seen.end()) cout<<"#";
		else cout<<".";
		//if(!within(P(r,c),lines))cout<<"OH NO!"<<endl;
		} 
		cout<<endl;
	}
}

