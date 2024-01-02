#include <algorithm>
#include <bits/stdc++.h>
#include <iomanip>
#include <sstream>
#include <type_traits>
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
//class module;
//
//struct entry{
//	module *from, *to;
//	bool sig;
//};
//
//class module {
//public:
//	string name;
//	V<string> conn;
//	V<module*> next;
//
//	module(string s){
//		cout<<"PROCESSING: "<<s<<endl;
//		stringstream ss(s);
//		string cur;
//		getline(ss,this->name,' ');
//		cout<<"NAME: "<<this->name<<endl;
//		getline(ss,cur,' ');
//		while(getline(ss,cur,' ')){
//			if(cur.back() == ',') cur.pop_back();
//			this->conn.pb(cur);
//		}
//	}
//
//	void setNext(unordered_map<string, module*>& m){
//		for(string s : this->conn){
//			this->next.pb(m[s]);
//		}
//	}
//
//	virtual void signal(module* from, bool sig, queue<entry>& q){
//		for(module* m : next){
//			q.push({this,m,sig});
//		}
//	}
//};
//class flipflop : public module {
//public:
//	flipflop(string s) : module(s) { }
//
//	bool on = false;
//	void signal(module* from, bool sig, queue<entry>& q){
//		if(sig) return;
//		on = !on;
//		module::signal(from,on,q);
//	}
//};
//class  conjun: public module {
//public:
//	conjun(string s) : module(s) { }
//
//	int cnt = 0;
//	unordered_map<module*,bool> last;
//	void signal(module* from, bool sig, queue<entry>& q){
//		if(last[from] && !sig) // was high, now low
//			cnt--;
//		if(!last[from] && sig) // was low, now high
//			cnt++;
//		last[from] = sig;
//		module::signal(from,cnt!=this->next.size(),q);
//	}
//};
//module* getModule(string s){
//	if(s[0] == '%') return new flipflop(s.substr(1));
//	if(s[0] == '&') return new conjun(s.substr(1));
//	return new module(s);
//
//}
//int main(){
//	//ifstream inputFile("./AOC2023/input_20.txt");
//	ifstream inputFile("./AOC2023/ex_20.txt");
//	V<string> lines;
//	for(string cur; getline(inputFile,cur);) lines.pb(cur);
//
//	unordered_map<string,module*> ms;
//	V<module*> modules;
//	for(string cur : lines){
//		modules.pb(getModule(cur));
//		ms[modules.back()->name] = modules.back();
//		//cout<<modules.back().name<<endl;
//	}
//	// cout<<"YAY!"<<endl;
//	cout<<ms["broadcaster"]->name<<endl;
//	for(module* m : modules) m->setNext(ms);
//	for(module* m : modules){
//		cout<<m->name<<" is connected to: "<<endl;
//		for(module* n : m->next) cout<<'\t'<<n->name<<endl;
//	}
//	queue<entry> q;
//	int high = 0, low = 0;
//	rep(i,0,1){
//		q.push({NULL,ms["broadcaster"],false});
//		int j = 0;
//		while(!q.empty()){
//			entry e = q.front();
//			q.pop();
//			//if(e.from != NULL) cout<<e.from->name<<" -"<<e.sig<<"- "<<e.to->name<<endl;
//			//else cout<<"button -"<<e.sig<<"- "<<e.to->name<<endl;
//			if(e.sig) high++;
//			else low++;
//			e.to->signal(e.from,e.sig,q);
//			if(j++ > 10) break;
//		}
//	}
//	cout<<"HIGH "<<high<<endl;
//	for(module* m : modules) free(m);
//}

enum type { base, flip, cjtn };
struct entry {
	string from;
	string to;
	bool high;
};
class module{
public:
	type tp = base;
	bool on = false; // for flip
	string name;
	V<string> to;
	unordered_set<string> from;
	ll cnt = 0;
	unordered_map<string,bool> last; // for cjtn

	module(string s) : name(s) {
		if(this->name[0] == '&') 
			this->tp = cjtn, this->name = this->name.substr(1);
		else if(this->name[0] == '%') 
			this->tp = flip, this->name = this->name.substr(1); 
		else this->tp = base;
	}

	ll next_sig(entry e){
		if(this->tp == cjtn){
			bool l = this->last[e.from];
			if(!l && e.high) cnt++;
			if(l && !e.high) cnt--;
			this->last[e.from] = e.high;
			return cnt == this->from.size() ? 0 : 1;
		} else if(this->tp == flip){
			if(e.high) return -1;
			this->on = !this->on;
			return this->on ? 1 : 0;
		} else {
			return e.high ? 1 : 0;
		}
	}

	string state(){
		string res = "";
		if(this->tp == cjtn){
			stringstream ss;
			ss<<setw(2)<<setfill('0')<<cnt;
			ss>>res;
		} else if(this->tp == flip){
			res = on ? "+" : "-";
		}
		return res;
	}
};
int main(){
	ifstream inputFile("./AOC2023/input_20.txt");
	//ifstream inputFile("./AOC2023/ex_20.txt");
	V<string> lines;
	for(string cur; getline(inputFile,cur);) lines.pb(cur);

	unordered_map<string,module*> ms;
	for(string line : lines){
		stringstream ss(line);
		string cur, name;
		getline(ss,name,' ');
		module *m = new module(name);
		getline(ss,cur,' '); // clear ->
		while(getline(ss,cur,' ')){
			if(cur.back() == ',') cur.pop_back();
			m->to.pb(cur);
		}
		ms[m->name] = m;
	}
	for(auto p : ms){
		for(string cur : p.second->to){
			if(ms.find(cur) == ms.end())
				ms[cur] = new module(cur);
			ms[cur]->from.insert(p.first);
		}
	}
	bool p1 = false;
	if(p1){
		ll high = 0, low = 0;
		rep(i,0,1000){
			queue<entry> q;
			//cout<<"NEW ROUND!"<<endl<<endl;
			q.push({"button","broadcaster",false});
			while(!q.empty()){
				entry e = q.front();
				if(e.high) high++;
				else low++;
				q.pop();
				//cout<<e.from<<" -"<<e.high<<"- "<<e.to<<endl;
				ll sig = ms[e.to]->next_sig(e);
				if(sig == -1) continue;
				for(string to : ms[e.to]->to){
					q.push({e.to,to,sig == 1});
				}
			}
		}
		cout<<"PART 1: "<<high*low<<endl;
	} else {
		cout<<"Starting pt 2"<<endl;
		ll press = 0;
		ll step = 0;
		unordered_map<string,V<ll>> cycles;
		for(string s : ms["rx"]->from)
			for(string i : ms[s]->from)
				cycles[i] = V<ll>();
		while(true){
			//unordered_map<string,int> cnt;
			//for(auto p : ms) cnt[p.second->name] = 0;
			queue<entry> q;
			ll cur = 0;
			//cout<<"NEW ROUND!"<<endl<<endl;
			q.push({"button","broadcaster",false});
			while(!q.empty()){
				entry e = q.front();
				q.pop();
				//cnt[e.to]++;
				//if(e.to == "rx" && !e.high) cur++;
				if(e.to == "ns" && e.high) 
					cycles[e.from].pb(press+1);
				step++;
				//cout<<e.from<<" -"<<e.high<<"- "<<e.to<<endl;
				ll sig = ms[e.to]->next_sig(e);
				if(sig == -1) continue;
				for(string to : ms[e.to]->to){
					q.push({e.to,to,sig == 1});
				}
			}
			//for(auto p : cycles)
			//	cout<<p.second.size()<<endl;
			if(all_of(cycles.begin(), cycles.end(), [=](pair<string,V<ll>> p){return p.second.size() > 3;})) break;
			press++;
		}
		ll res = 1;
		for(auto p : cycles){
			int last = 0;
			cout<<p.first;
			for(int i : p.second) 
				cout<<" ("<<(i-last)<<") "<<(last=i);
			cout<<endl;
			res = (res * p.second[0]) / __gcd(res,p.second[0]);
		}
		cout<<"PART 2: "<<res<<endl;
	}
	for(auto p : ms) free(p.second);
}
