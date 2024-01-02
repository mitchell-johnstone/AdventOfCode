#include <bits/stdc++.h>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
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
const double PI = 3.1415926585323;
const int MOD = 1e9 + 7;

// -------------------MAIN CODE-------------------//
struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};
ll test(V<pii>& edges, int sz, int a, int b, int c){
	UF uf(sz);
	rep(i,0,edges.size()){
		if(i == a || i == b || i == c) continue;
		uf.join(edges[i].first, edges[i].second);
	}
	int res = 1;
	for(int i : uf.e){
		if(i < 0) res *= i;
	}
	return res;
}
/* Returns true if there is a path from source 's' to sink 't' in 
residual graph. Also fills parent[] to store the path */
bool bfs(V<vi> rGraph, int s, int t, int parent[]) 
{ 
    // Create a visited array and mark all vertices as not visited 
    bool visited[rGraph.size()]; 
    memset(visited, 0, sizeof(visited)); 
 
    // Create a queue, enqueue source vertex and mark source vertex 
    // as visited 
    queue <int> q; 
    q.push(s); 
    visited[s] = true; 
    parent[s] = -1; 
 
    // Standard BFS Loop 
    while (!q.empty()) 
    { 
        int u = q.front(); 
        q.pop(); 
 
        for (int v=0; v<rGraph.size(); v++) 
        { 
            if (visited[v]==false && rGraph[u][v] > 0) 
            { 
                q.push(v); 
                parent[v] = u; 
                visited[v] = true; 
            } 
        } 
    } 
 
    // If we reached sink in BFS starting from source, then return 
    // true, else false 
    return (visited[t] == true); 
} 

// A DFS based function to find all reachable vertices from s.  The function
// marks visited[i] as true if i is reachable from s.  The initial values in
// visited[] must be false. We can also use BFS to find reachable vertices
void dfs(V<vi> rGraph, int s, bool visited[])
{
    visited[s] = true;
    for (int i = 0; i < rGraph.size(); i++)
       if (rGraph[s][i] && !visited[i])
           dfs(rGraph, i, visited);
}
 
// Prints the minimum s-t cut
void minCut(V<vi> graph, int s, int t)
{
    int u, v;
 
    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
	V<vi> rGraph(graph);
 
    int parent[graph.size()];  // This array is filled by BFS and to store path
 
    // Augment the flow while there is a path from source to sink
    while (bfs(rGraph, s, t, parent))
    {
        // Find minimum residual capacity of the edges along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
		cout<<"another one"<<endl;
 
        // update residual capacities of the edges and reverse edges
        // along the path
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
    }
 
    // Flow is maximum now, find vertices reachable from s
	cout<<"start"<<endl;
    bool visited[graph.size()];
    memset(visited, false, sizeof(visited));
    dfs(rGraph, s, visited);
	cout<<"end"<<endl;
 
    // Print all edges that are from a reachable vertex to
    // non-reachable vertex in the original graph
    for (int i = 0; i < graph.size(); i++)
      for (int j = 0; j < graph.size(); j++)
         if (visited[i] && !visited[j] && graph[i][j])
              cout << i << " - " << j << endl;
 
    return;
}
// Returns the maximum number of edge-disjoint paths from s to t. 
// This function is copy of forFulkerson() discussed at http://goo.gl/wtQ4Ks 
int findDisjointPaths(V<vi> graph, int s, int t) 
{ 
    int u, v; 
 
    // Create a residual graph and fill the residual graph with 
    // given capacities in the original graph as residual capacities 
    // in residual graph 
	V<vi> rGraph(graph); // Residual graph where rGraph[i][j] indicates 
                    // residual capacity of edge from i to j (if there 
                    // is an edge. If rGraph[i][j] is 0, then there is not) 
 
    int parent[rGraph.size()]; // This array is filled by BFS and to store path 
 
    int max_flow = 0; // There is no flow initially 
 
    // Augment the flow while there is path from source to sink 
    while (bfs(rGraph, s, t, parent)) 
    { 
        // Find minimum residual capacity of the edges along the 
        // path filled by BFS. Or we can say find the maximum flow 
        // through the path found. 
        int path_flow = INT_MAX; 
 
        for (v=t; v!=s; v=parent[v]) 
        { 
            u = parent[v]; 
            path_flow = min(path_flow, rGraph[u][v]); 
        } 
 
        // update residual capacities of the edges and reverse edges 
        // along the path 
        for (v=t; v != s; v=parent[v]) 
        { 
            u = parent[v]; 
            rGraph[u][v] -= path_flow; 
            rGraph[v][u] += path_flow; 
        } 
 
        // Add path flow to overall flow 
        max_flow += path_flow; 
    } 
 
    // Return the overall flow (max_flow is equal to maximum 
    // number of edge-disjoint paths) 
    return max_flow; 
}
int main(){
	ifstream inputFile("./AOC2023/input_25.txt");
	//ifstream inputFile("./AOC2023/ex_25.txt");
	V<string> lines;
	for(string cur; getline(inputFile,cur);) lines.pb(cur);

	unordered_map<string, int> mtoi;
	int idx = 0;
	set<pii> edges;
	for(string cur : lines){
		stringstream ss(cur);
		string from, to;
		ss>>from;
		from.pop_back();
		if(mtoi.find(from) == mtoi.end()) mtoi[from] = idx++;
		while(ss>>to){
			if(mtoi.find(to) == mtoi.end()) mtoi[to] = idx++;
			edges.insert(mp(mtoi[from],mtoi[to]));
		}
	}
	//V<unordered_set<int>> adj(idx);
	//for(pii p : edges) adj[p.first].insert(p.second), adj[p.second].insert(p.first);
	V<vi> adj(idx,vi(idx,0));
	for(pii p : edges) adj[p.first][p.second] = 1, adj[p.second][p.first] = 1;
	// check disjoint edge paths
	ll res = 0;
	//rep(i,1,idx){
	//	if(findDisjointPaths(adj, 0, i) > 3) res++;
	//	cout<<i<<" -> "<<res<<endl;
	//}
	//minCut(adj, 0, 9);
	
	// from doing find disjoint, I found that 0 and 9 are in the different components.
	// then, doing minCut(0,9), I found the following edge cuts:
	//  234 - 232
	//  862 - 849
	//  1434 - 1168
	queue<int> next({0});
	V<bool> visited(idx,false);
	res = 3;
	while(!next.empty()){
		int i = next.front();
		next.pop();
		if(visited[i]) continue;
		if(i == 234 || i == 232 || i == 862 || i == 849 || i == 1434 || i == 1168) continue;
		visited[i] = true;
		res++;
		rep(j,0,idx) if(adj[i][j]) next.push(j);
	}
	res = res * (idx - res);


	// try coloring?
	//ll res = 0;
	//rep(i,0,idx-1){
	//	cout<<i<<"/"<<idx<<endl;
	//	rep(j,i+1,idx){
	//		// I think i and j are connected.
	//		// Let's try to paint!
	//		vi cnt(idx,0);
	//		cnt[i] = cnt[j] = 2;
	//		bool valid = true;
	//		int sz = 0;
	//		do{
	//			int i = 0;
	//			while(i < idx && cnt[i] < 2) i++;
	//			if(i == idx) valid = false;
	//			else { // we found a good one!
	//				cnt[i] = -1;
	//				sz++;
	//				for(int n : adj[i]){
	//					if(cnt[n] >= 0) cnt[n]++;
	//				}
	//			}
	//		} while(valid);
	//		res = max(res,(ll)sz * (idx - sz));
	//		//if(sz != idx && sz > 3) res = sz * (idx - sz);
	//		//if(res != 0) break;
	//	}
	//	//if(res != 0) break;
	//}
	
	// 538270 is not the right answer
	// 9138 is too low
	// 4578 is too low
	// 3054 is too low
	cout<<"PART 1: "<<res<<endl;
	//ll res = 0;
	//rep(i,0,idx-2){
	//	cout<<i<<endl;
	//	rep(j,i+1,idx-1){
	//		rep(k,j+1,idx){
	//			res = max(res,test(edges,idx,i,j,k));
	//		}
	//	}
	//}
	//cout<<"PART 1: "<<res<<endl;
}

