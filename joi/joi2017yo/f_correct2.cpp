#include<cstdio>
#include<vector>
#include<utility>
#include<queue>
#include<tuple>

using namespace std;
using ll = long long;

const int MAX_N = 10000;
const int MAX_X = 200;

const int inf = 1e9;

struct Edge{
	int to, cost;
	Edge(){}
	Edge(int to, int cost):to(to), cost(cost){}
};

vector<Edge> G[MAX_N];
int T[MAX_N]; //temperature (0/1/2)

int N, X;

int dis[MAX_N][2][MAX_X + 1];

typedef pair<int, int> P; //<temperature of the nearest non-comfortable room (0 or 2), distance from there>
typedef pair<int, P> P2; //<vertex, P>
typedef pair<int, P2> P3; //<distance from s, P2>

pair<int, int> update_state(int last_t, int sum_d, Edge e){  // {最後に入った部屋の温度, 最後に入った部屋からの累積移動距離} を返す
	if(T[e.to] == 0){  // 行き先の部屋の温度が寒すぎならば
		if(last_t == 2 && sum_d + e.cost < X){
			return P(-1, -1);  // 行けないとき
		}else{
			return P(0, 0);  // 行けるとき
		}
	}else if(T[e.to] == 1){  // 行き先の部屋の温度が快適ならば
		int d = min(X, sum_d + e.cost);
		return P(last_t, d);
	}else{  // 行き先の部屋の温度が暑すぎならば
		if(last_t == 0 && sum_d + e.cost < X){
			return P(-1, -1);
		}else{
			return P(2, 0);
		}
	}
}

void dijkstra(){
	// priority_queue<P3, vector<P3>, greater<P3> > que;
	priority_queue<tuple<int,int,int,int>, vector<tuple<int,int,int,int>>, greater<tuple<int,int,int,int>>> que;
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < 3; ++j){
			for(int k = 0; k < MAX_X + 1; ++k){
				dis[i][j][k] = inf;
			}
		}
	}

	dis[0][0][0] = 0;
	que.push({0,0,0,0});

	while(!que.empty()){
		auto[cost, u, last_t, sum_d] = que.top(); que.pop();

		if(dis[u][last_t / 2][sum_d] < cost) { continue; }

		for(int i = 0; i < G[u].size(); ++i){
			Edge e = G[u][i];
			int ncost = cost + e.cost;

			if(T[e.to] == 0){  // 行き先の部屋の温度が寒すぎならば
				if(last_t == 2 && sum_d + e.cost < X){ continue; }
				if(dis[e.to][0][0] <= ncost) { continue; }
				dis[e.to][0][0] = ncost;
				que.push({ncost, e.to, 0, 0});
			}else if(T[e.to] == 1){  // 行き先の部屋の温度が快適ならば
				if(dis[e.to][last_t / 2][min(X, sum_d + e.cost)] <= ncost) continue;
				dis[e.to][last_t / 2][min(X, sum_d + e.cost)] = ncost;
				que.push({ncost, e.to, last_t, min(X, sum_d + e.cost)});
			}else{  // 行き先の部屋の温度が暑すぎならば
				if(last_t == 0 && sum_d + e.cost < X){ continue; }
				if(dis[e.to][1][0] <= ncost) continue;
				dis[e.to][1][0] = ncost;
				que.push({ncost, e.to, 2, 0});
			}
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
		scanf("%d", T + i);
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