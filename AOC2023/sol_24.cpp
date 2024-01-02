#include <bits/stdc++.h>
#include <sstream>
#include <string>
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
const ld PI = 3.1415926585323;
const int MOD = 1e9 + 7;

// -------------------MAIN CODE-------------------//
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
	ld dist() const { return sqrt((ld)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	ld angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(ld a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};
template<class T> struct Point3D {
	typedef Point3D P;
	typedef const P& R;
	T x, y, z;
	explicit Point3D(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
	bool operator<(R p) const {
		return tie(x, y, z) < tie(p.x, p.y, p.z); }
	bool operator==(R p) const {
		return tie(x, y, z) == tie(p.x, p.y, p.z); }
	P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
	P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
	P operator*(T d) const { return P(x*d, y*d, z*d); }
	P operator/(T d) const { return P(x/d, y/d, z/d); }
	T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
	P cross(R p) const { return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x); }
	T dist2() const { return x*x + y*y + z*z; }
	ld dist() const { return sqrt((ld)dist2()); }
	//Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
	ld phi() const { return atan2(y, x); } 
	//Zenith angle (latitude) to the z-axis in interval [0, pi]
	ld theta() const { return atan2(sqrt(x*x+y*y),z); }
	P unit() const { return *this/(T)dist(); } //makes dist()=1
	//returns unit vector normal to *this and p
	P normal(P p) const { return cross(p).unit(); }
	//returns point rotated 'angle' radians ccw around axis
	P rotate(ld angle, P axis) const {
		ld s = sin(angle), c = cos(angle); P u = axis.unit();
		return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
	}
	Point<T> get2D(){ return Point<T>(x,y);}
};
template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}
typedef Point3D<ld> P3;
typedef Point<ld> P2;
#define low ((ld)200000000000000) 
#define high ((ld)400000000000000) 
//define low ((ld)7) 
//define high ((ld)27) 

template<class P> vector<P> segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b),
	     oc = a.cross(b, c), od = a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
		return {(a * ob - b * oa) / (ob - oa)};
	set<P> s;
	if (onSegment(c, d, a)) s.insert(a);
	if (onSegment(c, d, b)) s.insert(b);
	if (onSegment(a, b, c)) s.insert(c);
	if (onSegment(a, b, d)) s.insert(d);
	return {all(s)};
}
bool check(P2 p){
	return p.x >= low && p.x <= high && p.y >= low && p.y <= high;
}
// get from https://stackoverflow.com/questions/2931573/determining-if-two-rays-intersect
template<class P> bool RaysIntersection(const P& as, const P& ad, const P& bs, const P& bd, P& result)
{
    if (as == bs) {
        result = as;
        return true;
    }
    auto dx = bs.x - as.x;
    auto dy = bs.y - as.y;
    auto det = bd.x * ad.y - bd.y * ad.x;
    if (det != 0) { // near parallel line will yield noisy results
        double u = (dy * bd.x - dx * bd.y) / (double)det;
        double v = (dy * ad.x - dx * ad.y) / (double)det;
        if (u >= 0 && v >= 0) {
            result = as + ad * u;
            return true;
        }
    }
    return false;
}
bool intersect(pair<P3,P3>& a, pair<P3,P3>& b){
	P2 res;
	return RaysIntersection(a.first.get2D(), a.second.get2D(), b.first.get2D(), b.second.get2D(), res) && check(res);
}
int main(){
	ifstream inputFile("./AOC2023/input_24.txt");
	//ifstream inputFile("./AOC2023/ex_24.txt");
	V<pair<P3,P3>> hail;
	for(string cur; getline(inputFile,cur);) {
		stringstream ss(cur);
		pair<P3,P3> p;
		ss>>p.first.x; getline(ss,cur,',');
		ss>>p.first.y; getline(ss,cur,',');
		ss>>p.first.z; getline(ss,cur,'@');
		ss>>p.second.x; getline(ss,cur,',');
		ss>>p.second.y; getline(ss,cur,',');
		ss>>p.second.z; 
		hail.pb(p);
	}
	//cout<<hail.size()<<endl;
	//for(pair<P3,P3>& p : hail){
	//	cout<<p.first.x<<", "<<p.first.y<<", "<<p.first.z<<" @ ";
	//	cout<<p.second.x<<", "<<p.second.y<<", "<<p.second.z<<endl;
	//}

	ll res = 0;
	rep(i,0,hail.size()) {
		rep(j,i+1,hail.size()){
			if(intersect(hail[i], hail[j])) res++;
		}
	}
	// 25160 is too high
	// 25158 is too high
	// 19783 is too high
	// 19626 is too high
	// 16502 is just right
	// 0 is too low
	cout<<"PART 1:"<<res<<endl;

	// part 2 done in matlab
}

