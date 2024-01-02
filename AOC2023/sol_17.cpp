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
/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
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
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P flip() const { return P(y, -x); } // rotates -90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};
typedef Point<long long> Point_t;
struct location {
	Point_t pos;
	Point_t dir;
	int cnt;
	int loss;
	friend bool operator<(const location& l, const location& r){ return true; }
	friend bool operator==(const location& l, const location& r){
		return l.pos == r.pos && l.dir == r.dir && l.cnt == r.cnt;
	}
};
struct loc_hash {
	size_t operator()(const location& l) const {
		return l.pos.x + 117 * (l.pos.y + 100 * (l.dir.x + 100 * (l.dir.y + 100 * (l.cnt))));
	}
};
int dist(V<string>& lines, Point_t pos){
	return lines.size() - pos.x + lines[0].size()-pos.y;
}
int path(V<string>& lines, int min, int max){
	priority_queue<pair<int,location>> pq;
	pq.push({0,{Point_t(1,0),Point_t(1,0),0,0}});
	pq.push({0,{Point_t(0,1),Point_t(0,1),0,0}});

	auto left = [=](Point_t& d){ return d.perp(); };
	auto right = [=](Point_t& d){ return d.flip(); };
	auto within = [=](Point_t& p){ return p.x >= 0 && p.x < lines.size() && p.y >= 0 && p.y < lines[0].size(); };

	int res = 0;
	unordered_set<location, loc_hash> sn;

	while(!pq.empty()){
		auto p = pq.top();
		pq.pop();

		int h = p.first;
		location cur = p.second;

		if(!within(cur.pos)) continue;
		cur.loss += lines[cur.pos.x][cur.pos.y] - '0';

		// if(cur.cnt == 3) continue; // cant move 3 in a row
		if(cur.cnt >= max) continue;

		unordered_set<string> New_set;
		if(sn.find(cur) != sn.end()) continue;
		sn.insert(cur);

		//cout<<"AT "<<cur.pos<<endl;
		if(cur.pos.x == lines.size()-1 && cur.pos.y == lines[0].size()-1) {
			res = cur.loss; 
			break;
		}

		Point_t n; // find next positions
		n = cur.pos + cur.dir;
		pq.push({-cur.loss, {n,cur.dir,cur.cnt+1,cur.loss}});
		if(cur.cnt >= min){
			n = cur.pos + left(cur.dir);
			pq.push({-cur.loss, {n,left(cur.dir),0,cur.loss}});
			n = cur.pos + right(cur.dir);
			pq.push({-cur.loss, {n,right(cur.dir),0,cur.loss}});
		}
	}
	return res;
}
int main(){
	ifstream inputFile("./AOC2023/input_17.txt");
	//ifstream inputFile("./AOC2023/ex_17.txt");
	V<string> lines;
	for(string cur; getline(inputFile,cur);) lines.pb(cur);

	cout<<"PART 1: "<<path(lines, 0, 3)<<endl;
	cout<<"PART 2: "<<path(lines, 3, 10)<<endl;
}

