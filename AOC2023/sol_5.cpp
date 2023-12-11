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
struct M{
    ll dest;
    ll source;
    ll range;
};
int main(){
	ifstream inputFile("AOC2023/input_5.txt");
	//ifstream inputFile("AOC2023/ex_5.txt");
    V<string> lines;
    for(string cur; getline(inputFile,cur);) lines.pb(cur);

    V<ll> seeds;
    {
        stringstream ss(lines[0]);
        string cur;
        ss>>cur;
        for(ll s; ss>>s;) seeds.pb(s);
    }

    V<V<M>> maps(1,V<M>());
    rep(i, 3, lines.size()){
        if(lines[i] == ""){
            maps.pb(V<M>());
            i++;
        } else {
            stringstream ss(lines[i]);
            ll d,s,r;
            ss>>d>>s>>r;
            maps.back().pb({d,s,r});
        }
    }

    ll min_loc = 1e9;
    for(ll val : seeds){
        for(V<M> m : maps){
            for(M cur : m){
                if(cur.source <= val && cur.source + cur.range > val){
                    val = (val - cur.source) + cur.dest;
                    break;
                }
            }
        }
        min_loc = min(min_loc,val);
    }
    cout<<"PART 1: "<<min_loc<<endl;

    V<pair<ll,ll>> segs;
    {
        stringstream ss(lines[0]);
        string cur;
        ss>>cur;
        for(ll s,r; ss>>s && ss>>r;) segs.pb({s,r});
    }

    for(V<M> m : maps){
        V<pair<ll,ll>> next_segs;
        //cout<<"NEXT MAP"<<endl;
        int i = 0;
        //cout<<segs.size()<<endl;
        while(segs.size()){
            pair<ll,ll> seg = segs.back();
            //cout<<"PROCESSING "<<seg.first<<" "<<seg.second<<endl;
            segs.pop_back();
            bool used = false;
            for(M cur : m){
                // seg out of range
                if(seg.first >= cur.source+cur.range) continue;
                if(seg.first+seg.second <= cur.source) continue;
                // seg in range
                if(cur.source <= seg.first){ // start in range!
                    ll nrange = min(cur.source+cur.range-seg.first, seg.second);
                    //cout<<"Transforming "<<seg.first<<" "<<seg.second<<" ";
                    //cout<<"to "<<seg.first+cur.dest-cur.source<<" "<<nrange<<endl;
                    //cout<<seg.second - nrange<<endl;
                    next_segs.pb({seg.first+cur.dest-cur.source,nrange});

                    if(seg.second - nrange){
                        segs.pb({cur.source+cur.range, seg.second-nrange});
                    }
                } else { // start is outside of range!
                    ll nrange = cur.source-seg.first;
                    segs.pb({seg.first, nrange});
                    segs.pb({cur.source, seg.second-nrange});
                }
                used = true;
                break;
            }
            if(!used) next_segs.pb(seg);
        }
        sort(next_segs.begin(), next_segs.end());
        for(pair<ll,ll> p : next_segs) {
            //cout<<p.first<<"-"<<p.first+p.second<<" ";
            if(segs.size() && segs.back().first + segs.back().second == p.first){
                segs.back().second+=p.second;
            } else {
                segs.pb(p);
            }
        }
        //cout<<endl;
    }
    min_loc = 1e9;
    for(pair<ll,ll> p : segs) min_loc = min(min_loc, p.first);
    cout<<"PART 2: "<<min_loc<<endl;
}

