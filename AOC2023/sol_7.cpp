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
enum h_type { high, pair1, pair2, three, full, four, five };
struct hand{
    string cards;
    ll bid;
};
h_type score1(hand& h){
    map<char, int> m;
    for(char c : h.cards) m[c] = m[c] + 1;
    if(m.size() == 5) return high;
    if(m.size() == 4) return pair1;
    if(m.size() == 3) { // either pair2 or three
        for(auto p : m) if(p.second == 3) return three;
        return pair2;
    }
    if(m.size() == 2) { // either full or four
        if((*m.begin()).second == 3 || (*m.begin()).second == 2) return full;
        return four;
    }
    return five;
}
h_type score2(hand& h){
    map<char, int> m;
    for(char c : h.cards) m[c] = m[c] + 1;
    int jokers = m['1'];
    if(jokers >= 4) return five;
    if(jokers == 3) {// either 5 or 4 or a kind
        if(m.size() == 2) return five;
        return four;
    }
    if(jokers == 2) {
        if(m.size() == 2) return five;
        if(m.size() == 3) return four;
        return three;
    }
    if(jokers == 1) {
        if(m.size() == 5) return pair1;
        if(m.size() == 4) return three;
        if(m.size() == 3) {
            for(auto p : m) {
                if(p.first == '1') continue;
                if(p.second == 2) return full;
                return four;
            }
        }
        return five;
    }
    return score1(h);
//    if(jokers == 0) return score1(h);
//    h_type best = high;
//    int i = 0;
//    while(h.cards[i] != '1') i++;
//    rep(v,2,15){
//        if(v == 11) continue;
//        char prev = h.cards[i];
//        h.cards[i] = '0' + v;
//        best = max(best, score2(h));
//        h.cards[i] = prev;
//    }
//    return best;
}
int main(){
	ifstream inputFile("./AOC2023/input_7.txt");
	//ifstream inputFile("./AOC2023/ex_7.txt");
    V<hand> hands;
    string cur;
    ll bid;
    while(inputFile >> cur && inputFile >> bid) {
        //cout<<cur<<endl;
        for(char& c : cur){
            if(c == 'A') c = '0' + 14;
            if(c == 'K') c = '0' + 13;
            if(c == 'Q') c = '0' + 12;
            if(c == 'J') c = '0' + 11;
            if(c == 'T') c = '0' + 10;
        }
        hands.pb({cur, bid});
    }

    auto cmp1 = [=](hand& h1, hand& h2){
        h_type t1 = score1(h1), t2 = score1(h2);
        return t1 != t2 ? t1 < t2 : h1.cards < h2.cards;
    };
    sort(hands.begin(), hands.end(), cmp1);
    int wins = 0;
    rep(i,0,hands.size()){ wins += hands[i].bid * (i+1); }
    cout<<"PART 1: "<<wins<<endl;

    for(hand& h : hands) for(char& c : h.cards) if(c == '0'+11) c = '1';
    auto cmp2 = [=](hand& h1, hand& h2){
        //return tie(score2(h1), h1.cards) < tie(score2(h2), h2.cards);
        h_type t1 = score2(h1), t2 = score2(h2);
        return tie(t1, h1.cards) < tie(t2, h2.cards);
        //return t1 != t2 ? t1 < t2 : h1.cards < h2.cards;
    };
    sort(hands.begin(), hands.end(), cmp2);
    wins = 0;
    rep(i,0,hands.size()){ wins += hands[i].bid * (i+1); }
    cout<<"PART 2: "<<wins<<endl;
}

