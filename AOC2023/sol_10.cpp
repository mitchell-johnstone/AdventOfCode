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
enum direction { u,d,l,r };

int main(){
	ifstream inputFile("./AOC2023/input_10.txt");
	//ifstream inputFile("./AOC2023/ex_10.txt");
    V<string> lines;
    int row, col;
    for(string cur; getline(inputFile,cur);) {
        rep(i,0,cur.size()) if(cur[i] == 'S') row=lines.size(), col=i;
        lines.pb(cur);
    }

    direction dir;
    if(row > 0 && (lines[row-1][col] == '|' || lines[row-1][col] == 'F' || lines[row-1][col] == '7')) dir = u;
    else if(col > 0 && (lines[row][col-1] == '-' || lines[row][col-1] == 'F' || lines[row][col-1] == 'L')) dir = l;
    else dir = d;

    int pts = 0;
    int area2 = 0;
    do {
        int pr = row, pc = col;
        if(dir == u) {
            row--;
            if(lines[row][col] == '7') dir = l;
            if(lines[row][col] == 'F') dir = r;
        } else if(dir == d) {
            row++;
            if(lines[row][col] == 'J') dir = l;
            if(lines[row][col] == 'L') dir = r;
        } else if(dir == l) {
            col--;
            if(lines[row][col] == 'F') dir = d;
            if(lines[row][col] == 'L') dir = u;
        } else if(dir == r) {
            col++;
            if(lines[row][col] == '7') dir = d;
            if(lines[row][col] == 'J') dir = u;
        }
        area2 += pc * row - pr * col;
        pts++;
    } while (lines[row][col] != 'S');
    // furthest point = total path / 2 = pts / 2
    cout<<"PART 1:" <<pts/2<<endl;
    // using Pick's algorithm (area2 = a + b/2 - 1, where a = number pts inside and b = number integer boundary pts).
    // we have 2*area from shoelace
    // and we have the # of boundary points in pts
    // and we want a, the number of pts inside!
    cout<<"PART 2: "<<abs(area2)/2-pts/2+1<<endl;
        //rep(i,0,lines.size()){
        //    rep(j,0,lines[0].size()){
        //        if(paint[i][j]) cout<<lines[i][j];
        //        else cout<<' ';
        //    }
        //    cout<<endl;
        //}
    //cout<<"PART 2: "<<abs(polygonArea2(pts))-pts.size()<<endl;
    //int cnt = 0;
    //rep(i,0,lines.size()){
    //    rep(j,0,lines[0].size()){
    //        cnt += inPolygon(pts, Point(i,j));
    //    }
    //}
    //cout<<cnt<<endl;

    

//    queue<pair<location,int>> q;
//    rep(i,0,lines.size()) rep(j,0,lines[0].size()) if(lines[i][j] == 'S') q.push({{i,j,s},0});
//    int furthest = 0;
//    while(!q.empty()){
//        auto p = q.front();
//        q.pop();
//        location loc = p.first;
//        if(check(loc,lines) && !paint[loc.x][loc.y]){
//            paint[loc.x][loc.y] = true;
//            furthest = max(furthest, p.second);
//            char c = lines[loc.x][loc.y];
//            if(c == 'S'){
//                q.push({{loc.x+1,loc.y,d},p.second+1});
//                q.push({{loc.x-1,loc.y,u},p.second+1});
//                q.push({{loc.x,loc.y+1,r},p.second+1});
//                q.push({{loc.x,loc.y-1,l},p.second+1});
//            }
//            if(c == '-') {
//                q.push({{loc.x,loc.y+1,r},p.second+1});
//                q.push({{loc.x,loc.y-1,l},p.second+1});
//            }
//            if(c == '|') {
//                q.push({{loc.x+1,loc.y,d},p.second+1});
//                q.push({{loc.x-1,loc.y,u},p.second+1});
//            }
//            if(c == 'F') {
//                q.push({{loc.x+1,loc.y,d},p.second+1});
//                q.push({{loc.x,loc.y+1,r},p.second+1});
//            }
//            if(c == 'L') {
//                q.push({{loc.x-1,loc.y,u},p.second+1});
//                q.push({{loc.x,loc.y+1,r},p.second+1});
//            }
//            if(c == 'J') {
//                q.push({{loc.x-1,loc.y,u},p.second+1});
//                q.push({{loc.x,loc.y-1,l},p.second+1});
//            }
//            if(c == '7') {
//                q.push({{loc.x,loc.y-1,l},p.second+1});
//                q.push({{loc.x+1,loc.y,d},p.second+1});
//            }
//            //system("cls");
//            rep(i,0,lines.size()){
//                rep(j,0,lines[0].size()){
//                    if(paint[i][j]) cout<<lines[i][j];
//                    else cout<<' ';
//                }
//                cout<<endl;
//            }
//        }
//    }

    // paint has a map of the loop
    // so we iterate across!
    //rep(i,0,lines.size()){
    //    int in = 0;
    //    rep(j,0,lines[0].size()){
    //        if(paint[i][j]){
    //            if(lines[i][j] == 'F' || lines[i][j] == 'S') {
    //                do j++; while(lines[i][j] != 'J' && lines[i][j] != '7');
    //                in ^= 1;
    //            } else if(lines[i][j] == '|') in ^= 1;
    //            else if(lines[i][j] == 'L') {
    //                do {
    //                    j++;
    //                } while(lines[i][j] != 'J' && lines[i][j] != '7');
    //                in ^= 1;
    //            }
    //        } else pts += in;
    //        //if(paint[i][j]) cout<<lines[i][j];
    //        //else cout<<'.';
    //    }
    //    //cout<<endl;
    //}
//    for(V<bool> v : paint){
//        ll in = 0LL;
//        for(bool b : v){
//            if(b) in ^= 1LL;
//            else pts += in;
//        }
//        //cout<<endl;
//    }
}

