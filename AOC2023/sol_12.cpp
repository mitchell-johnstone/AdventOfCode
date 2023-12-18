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
//int arrange(string& cur, int si, vi& nums, int ni){
//    if(ni == -1){
//        while(si >= 0) if(cur[si] == '#') return 0;
//        return 1;
//    }
//    while(si >= 0 && cur[si] == '.') si--;
//    if(si < nums[ni] - 1) return 0;
//    int cnt = 0, ends = 0;
//    bool found = false;
//    rep(i,0,nums[ni]){
//        if(cur[si--] == '?' && !found)
//
//    }
//    while(si >= 0 && cnt >= 0){
//
//    }
//    return cnt;
//}
//int arrange(string log, vi nums){
//    auto loc = log.find('?');
//    if(loc == string::npos) {
//        // no ?
//        // check!
//        //cout<<"cnting "<<log<<endl;
//        stringstream ss(log);
//        bool valid = true;
//        string cur;
//        for(int i : nums){
//            if(ss>>cur) valid = valid && cur.size() == i;
//            else valid = false;
//            if(!valid) break;
//        }
//        if(valid && ss>>cur) valid = false;
//        return valid ? 1 : 0;
//    } else {
//        int cnt = 0;
//        log.replace(loc, 1, " ");
//        //cout<<"TRYING "<<log<<endl;
//        cnt += arrange(log,nums);
//        log.replace(loc, 1, "#");
//        //cout<<"TRYING "<<log<<endl;
//        cnt += arrange(log,nums);
//        return cnt;
//    }
//}
//int arrange(string log, vi nums){
//    if(nums.size() == 0){
//        if(log.find('#') != string::npos) return 0;
//        return 1; //everything blank.
//    }
//    while(!log.empty() && log.back() == '.') log.pop_back(); // get to next # or ?
//    int cnt = 0;
//    queue<char> cur;
//    int val = nums.back();
//    nums.pop_back();
//    bool had_correct = false;
//    while(!log.empty()){
//        char c = log.back();
//        log.pop_back();
//        if(cur.size() < val){
//            cur.insert(c);
//        } else {
//            // at limit! 
//        }
//    }
//}
ll arrange(string log, vi nums){
    // dp -> log x (num of #'s / log) x nums
    ll len = log.size()+1;
    ll num = nums.size()+1;
    ll dp[len][len][num];
    rep(i,0,len) rep(j,0,len) rep(k,0,num) dp[i][j][k] = 0;
    // perform dp
    dp[0][0][0] = 1;
    rep(i,1,len){
        //if(log[i-1] == '#'){
        if(log[i-1] == '#' || log[i-1] == '?'){
            rep(k,0,nums.size()){
                rep(j,1,len){
                    dp[i][j][k] += dp[i-1][j-1][k];
                }
            }
        }
        //if(log[i-1] == '.'){
        if(log[i-1] == '.' || log[i-1] == '?'){
            rep(k,0,num){
                dp[i][0][k] += dp[i-1][0][k];
            }
            rep(k,1,num){ // try to update!
                dp[i][0][k] += dp[i-1][nums[k-1]][k-1];
            }
        }
    }
    ll res = dp[len-1][nums.back()][nums.size()-1] + dp[len-1][0][nums.size()];
    //rep(k,0,num){
    //    rep(i,0,len){
    //        if(i == 0) cout<<" ";
    //        else cout<<log[i-1];
    //        cout<<" : ";
    //        rep(j,0,len){
    //            cout<<dp[i][j][k]<<" ";
    //        }
    //        cout<<endl;
    //    }
    //    cout<<endl;
    //}
    //for(int j = nums.back()-1; j >= 0 && dp[len-1][j][nums.size()-1]; j--){
    //    res += dp[len-1][j][nums.size()-1];
    //}
    //do {
    //    res += dp[log.size()][nums.back()][nums.size()-1];
    //    log.pop_back();
    //} while(log.size() && log.back() != '.');
    return res;
    //return dp[len-1][nums.back()][nums.size()-1];
}
int main(){
	ifstream inputFile("./AOC2023/input_12.txt");
	//ifstream inputFile("./AOC2023/ex_12.txt");
    V<string> lines;
    for(string cur; getline(inputFile,cur);) lines.pb(cur);

    int res1 = 0;
    rep(i,0,lines.size()){
        string cur = lines[i];
        //cout<<"TRYING "<<cur<<endl;
    //for(string cur : lines){
        stringstream ss(cur);
        string log, val;
        getline(ss,log,' ');
        vi vals;
        while(getline(ss,val,',')) vals.pb(stoi(val));
        //for(char& c : log) if(c=='.') c = ' ';
        res1+=arrange(log,vals);
        //break;
        //for(int i : vals) cout<<i<<" ";
        //cout<<log<<endl;
    }
    cout<<"PART 1: "<<res1<<endl;

    ll res2 = 0;
    rep(i,0,lines.size()){
        string cur = lines[i];
        stringstream ss(cur);
        string log, val;
        getline(ss,log,' ');
        vi vals;
        while(getline(ss,val,',')) vals.pb(stoi(val));
        int cnt = vals.size();
        string cpy = log;
        rep(j,0,4){
            log += "?" + cpy;
            rep(k,0,cnt) vals.pb(vals[k]);
        }
        res2+=arrange(log,vals);
    }
    cout<<"PART 2: "<<res2<<endl;
}

