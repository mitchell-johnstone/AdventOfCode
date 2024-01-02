#include <bits/stdc++.h>
#include <string>
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
void setTextColor(const std::string& colorHex) {
	// ANSI escape sequence to set the text color.
	cout << "\033[38;2;" << stoi(colorHex.substr(0, 2), nullptr, 16) << ";"
		<< stoi(colorHex.substr(2, 2), nullptr, 16) << ";"
		<< stoi(colorHex.substr(4, 2), nullptr, 16) << "m";
}
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	T cross(P p) const { return x*p.y - y*p.x; }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
};
typedef Point<ll> PT;
PT colorToPoint(string& color){
	ll i = stoi(color.substr(2,5),NULL,16);
	PT pt;
	if(color[7] == '0') pt = PT(i,0);
	if(color[7] == '1') pt = PT(0,-i);
	if(color[7] == '2') pt = PT(-i,0);
	if(color[7] == '3') pt = PT(0,i);
	return pt;
}
ll area(V<PT>& pts){
	ll res = 0, border = 0;
	PT cur(0,0);
	for(PT pt : pts){
		//cout<<r.color<<endl;
		PT next = cur + pt;
		res += cur.cross(next);
		border += pt.dist();
		cur = next;
	}
	return abs(res/2) + border/2 + 1;
}
int main(){
	ifstream inputFile("./AOC2023/input_18.txt");
	//ifstream inputFile("./AOC2023/ex_18.txt");
	V<string> lines;
	for(string cur; getline(inputFile,cur);) lines.pb(cur);
	V<PT> p1, p2;
	for(string line : lines) {
		char c;
		int i;
		string color;
		stringstream ss(line);
		ss>>c>>i>>color;

		if(c=='L') p1.pb(PT(-i,0));
		if(c=='R') p1.pb(PT(i,0));
		if(c=='U') p1.pb(PT(0,i));
		if(c=='D') p1.pb(PT(0,-i));

		p2.pb(colorToPoint(color));
	}
	cout<<"PART 1: "<<area(p1)<<endl;
	cout<<"PART 1: "<<area(p2)<<endl;
}
