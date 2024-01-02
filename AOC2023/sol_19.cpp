#include <algorithm>
#include <bits/stdc++.h>
#include <sstream>
#include <string>
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

// fast io
void fast_io(){cin.tie(0)->sync_with_stdio(0);cin.exceptions(cin.failbit);}

// constants
const double PI = 3.1415926585323;
const int MOD = 1e9 + 7;

// -------------------MAIN CODE-------------------//
unordered_map<string,V<string>> work;
V<unordered_map<char,ll>> products;

ll process(string label, unordered_map<char, ll>& prod){
	if(label.size() == 1) {
		if(label == "A") return 1;
		if(label == "R") return 0;
	}
	for(string cond : work[label]){
		if(cond.size() == 1) return cond == "A";
		auto it = cond.find(":");
		if(it == string::npos) {
			return process(cond, prod);
		}
		string c = cond.substr(0,it);
		string n = cond.substr(it+1);

		ll cmp = stoi(c.substr(2));
		if(c[1] == '>' && prod[c[0]] > cmp) return process(n, prod);
		if(c[1] == '<' && prod[c[0]] < cmp) return process(n, prod);
	}
	return 0;
}
ll part(unordered_map<char, ll>& prod){
	return prod['x'] + prod['m'] + prod['a'] + prod['s'];
}
#define low first
#define high second 
ll score(unordered_map<char, pair<ll,ll>>& prod){
	ll res = 1;
	for(char c : {'x','m','a','s'})
		res *= prod[c].high - prod[c].low + 1;
	return res;
}
bool valid(unordered_map<char, pair<ll,ll>>& prod){
	for(char c : {'x','m','a','s'})
		if(prod[c].high < prod[c].low) return false;
	return true;
}
ll possible(string label, ll idx, unordered_map<char, pair<ll,ll>> prod){
	if(!valid(prod)) return 0;
	cout<<label<<endl;
	for(char c : {'x','m','a','s'})
		cout<<c<<" "<<prod[c].low<<"-"<<prod[c].high<<endl;
	if(label.size() == 1) {
		// we're at A or R!
		if(label == "A") return score(prod);
		if(label == "R") return 0;
		return possible(label, 0, prod);
	}
	string cond = work[label][idx];
	cout<<"CHECKING COND: "<<cond<<endl;
	auto it = cond.find(":");
	if(it == string::npos) { 
		cout<<"Going to "<<cond<<endl;
		// we've reached end, only 1 way to go
		// cond is the next label
		return possible(cond, 0, prod);
	}

	string next = cond.substr(it+1);
	cond = cond.substr(0,it);

	ll value = stoi(cond.substr(2));
	char var = cond[0];

	if(cond[1] == '>'){
		// check if var is greater than the value
		if(prod[var].low > value)  // already greater than
		{
			cout<<"already good"<<endl;
			return possible(next,0,prod);
		}
		if(prod[var].high <= value) // no valid values
		{
			cout<<"not valid"<<endl; 
			return 0; 
		}
		auto succ = prod, fail = prod;
		// match! var > value!
		succ[var].low = value+1;
		fail[var].high = value;
		cout<<"DOING BOTH!"<<endl;
		return possible(next, 0, succ) + possible(label, idx+1, fail);
	} else {
		// check if var is less than the value
		if(prod[var].high < value) // already greater than			
		{
			cout<<"already good"<<endl;
			return possible(next,0,prod);
		}
		if(prod[var].low >= value)  // no valid values
		{
			cout<<"not valid"<<endl;
			return 0; 
		}
		auto succ = prod, fail = prod;
		// match! var < value!
		succ[var].high = value-1;
		fail[var].low = value;
		cout<<"DOING BOTH!"<<endl;
		return possible(next, 0, succ) + possible(label, idx+1, fail);
	}
}
//ll possible(string label,ll idx,ll lx, ll ux, ll lm, ll um, ll la, ll ua, ll ls, ll us){
//	if(ux < lx || um < lm || ua < la || us < ls) return 0;
//	string cond = work[label][idx];
//	if(cond.size() == 1) {
//		if(cond == "A") return (ux-lx+1) * (um-lm+1)  * (ua-la+1) * (us-ls+1);
//		if(cond == "R") return 0;
//	}
//	auto it = cond.find(":");
//	if(it == string::npos) {
//		return possible(cond, 0, lx, ux, lm, um, la, ua, ls, us);
//	}
//	string c = cond.substr(0,it);
//	string n = cond.substr(it+1);
//
//	ll cmp = stoi(c.substr(2));
//	if(c[1] == '>'){
//		if(c[0] == 'x') 
//			return possible(n, 0, cmp+1, ux, lm, um, la, ua, ls, us) 
//			+ possible(label, idx+1, lx, cmp, lm, um, la, ua, ls, us);
//		if(c[0] == 'm') 
//			return possible(n, 0, lx, ux, cmp+1, um, la, ua, ls, us) 
//			+ possible(label, idx+1, lx, ux, lm, cmp, la, ua, ls, us);
//		if(c[0] == 'a') 
//			return possible(n, 0, lx, ux, lm, um, cmp+1, ua, ls, us) 
//			+ possible(label, idx+1, lx, ux, lm, um, la, cmp, ls, us);
//		if(c[0] == 's') 
//			return possible(n, 0, lx, ux, lm, um, la, ua, cmp+1, us) 
//			+ possible(label, idx+1, lx, ux, lm, um, la, ua, ls, cmp);
//	} else {
//		if(c[0] == 'x') 
//			return possible(label, idx+1, cmp, ux, lm, um, la, ua, ls, us) 
//			+ possible(n, 0, lx, cmp-1, lm, um, la, ua, ls, us);
//		if(c[0] == 'm') 
//			return possible(label, idx+1, lx, ux, cmp, um, la, ua, ls, us) 
//			+ possible(n, 0, lx, ux, lm, cmp-1, la, ua, ls, us);
//		if(c[0] == 'a') 
//			return possible(label, idx+1, lx, ux, lm, um, cmp, ua, ls, us) 
//			+ possible(n, 0, lx, ux, lm, um, la, cmp-1, ls, us);
//		if(c[0] == 's') 
//			return possible(label, idx+1, lx, ux, lm, um, la, ua, cmp, us) 
//			+ possible(n, 0, lx, ux, lm, um, la, ua, ls, cmp-1);
//	}
//	return 0;
//}
int main(){
	ifstream inputFile("./AOC2023/input_19.txt");
	//ifstream inputFile("./AOC2023/ex_19.txt");
	V<string> lines;
	for(string cur; getline(inputFile,cur);) lines.pb(cur);

	while(!lines.back().empty()){
		unordered_map<char,ll> m;
		string val, cur = lines.back();
		cur.pop_back();
		cur = cur.substr(1);

		stringstream ss(cur);
		while(getline(ss,val,',')){
			m[val[0]] = stoi(val.substr(2));
		}
		products.pb(m);
		lines.pop_back();
	}
	lines.pop_back();
	for(string cur : lines) {
		stringstream ss(cur);
		string label, conds, cond;
		getline(ss,label,'{');
		getline(ss,conds,'}');
		stringstream cs(conds);
		V<string> v;
		while(getline(cs,cond,',')) v.pb(cond);
		work[label] = v;
	}
	ll sum = 0;
	for(unordered_map<char, ll>& prod : products){
		//cout<<process("in", prod)<<endl;
		//cout<<part(prod)<<endl;
		sum += process("in", prod) * part(prod);
	}
	cout<<"PART 1: "<<sum<<endl;
	unordered_map<char, pair<ll,ll>> prod;
	for(char c : "xmas")
		prod[c] = mp(1,4000);
	cout<<"PART 2: "<<possible("in",0,prod)<<endl;
}

