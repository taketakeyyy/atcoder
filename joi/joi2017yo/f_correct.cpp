#include<cstdio>
#include<vector>
#include<utility>
#include<queue>

using namespace std;

const int MAX_N = 10000;
const int MAX_X = 200;

const int inf = 1e9;

struct Edge{
	int to, cost;
	Edge(){}
	Edge(int to, int cost):to(to), cost(cost){}
};

vector<Edge> G[MAX_N];
int color[MAX_N]; //temperature (0/1/2)

int N, X;

int dis[MAX_N][2][MAX_X + 1];

typedef pair<int, int> P; //<temperature of the nearest non-comfortable room (0 or 2), distance from there>
typedef pair<int, P> P2; //<vertex, P>
typedef pair<int, P2> P3; //<distance from s, P2>

P update_state(P p, Edge e){  // {最後に入った部屋の温度, 最後に入った部屋からの累積移動距離} を返す
	if(color[e.to] == 0){  // 行き先の部屋の温度が寒すぎならば
		if(p.first == 2 && p.second + e.cost < X){
			return P(-1, -1);  // 行けないとき
		}else{
			return P(0, 0);  // 行けるとき
		}
	}else if(color[e.to] == 1){  // 行き先の部屋の温度が快適ならば
		int d = min(X, p.second + e.cost);
		return P(p.first, d);
	}else{  // 行き先の部屋の温度が暑すぎならば
		if(p.first == 0 && p.second + e.cost < X){
			return P(-1, -1);
		}else{
			return P(2, 0);
		}
	}
}

void dijkstra(){
	priority_queue<P3, vector<P3>, greater<P3> > que;
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < 3; ++j){
			for(int k = 0; k < MAX_X + 1; ++k){
				dis[i][j][k] = inf;
			}
		}
	}

	dis[0][0][0] = 0;
	que.push(P3(0, P2(0, P(0, 0))));

	while(!que.empty()){
		P3 p3 = que.top();
		que.pop();
		int d = p3.first;  // コスト
		int v = p3.second.first;  // 頂点
		P prv_state = p3.second.second;  // {最後に入った部屋の温度, 最後に入った部屋からの累積移動距離}
		if(dis[v][prv_state.first / 2][prv_state.second] < d) continue;
		for(int i = 0; i < G[v].size(); ++i){
			P np = update_state(prv_state, G[v][i]);
			if(np == P(-1, -1)) continue;
			int nd = d + G[v][i].cost;
			int nv = G[v][i].to;
			if(dis[nv][np.first / 2][np.second] <= nd) continue;
			dis[nv][np.first / 2][np.second] = nd;
			que.push(P3(nd, P2(nv, np)));
		}
	}
}

int solve(){
	dijkstra();
	int ans = inf;
	for(int c = 0; c < 2; ++c){
		for(int d = 0; d <= X; ++d){
			ans = min(ans, dis[N - 1][c][d]);
		}
	}
	for(int v = 0; v < N; ++v){
		int tmp = inf;
		for(int c = 0; c < 2; ++c){
			for(int d = 0; d <= X; ++d){
				tmp = min(tmp, dis[v][c][d]);
			}
		}
	}
	return ans;
}

void input(){
	int M;
	scanf("%d%d%d", &N, &M, &X);
	for(int i = 0; i < N; ++i){
		scanf("%d", color + i);
	}
	for(int i = 0; i < M; ++i){
		int u, v, d;
		scanf("%d%d%d", &u, &v, &d);
		u--;
		v--;
		G[u].push_back(Edge(v, d));
		G[v].push_back(Edge(u, d));
	}
}

int main(){
	input();
	int ans = solve();
	printf("%d\n", ans);
	return 0;
}