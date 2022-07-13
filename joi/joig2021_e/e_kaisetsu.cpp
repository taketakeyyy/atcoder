#include <bits/stdc++.h>
using namespace std;
const int N_MAX=1000;

struct edge{
	int to,cost;
};

struct S{
	int node,rcnt,dist;  // {頂点番号, 反転回数, 累積移動距離}
	bool operator<(const S &x)const{
		return x.dist<dist;
	}
};

int N,M,L;
int D[N_MAX][N_MAX+1];
vector<edge>E[N_MAX],R[N_MAX];
priority_queue<S>pq;

int main(){
	cin>>N>>M>>L;

    // E[u] := 頂点uと隣接する頂点{v, cost}
    // R[u] := 反転グラフ
	for(int i=0;i<M;i++){
		int A,B,C;
		cin>>A>>B>>C;
		A--;
		B--;
		E[A].push_back({B,C});
		R[B].push_back({A,C});
	}

    // D[i][j] := 頂点iへの最短距離。jはそれまでに反転した回数
	for(int i=0;i<N;i++){
		for(int j=0;j<=N;j++){
			D[i][j]=-1;
		}
	}

    // ダイクストラ
	pq.push({0,0,0});
	while(!pq.empty()){
		S s = pq.top(); pq.pop();  // s {node: 頂点番号, rcnt: 反転回数, dist: 累積移動距離}


		if(D[s.node][s.rcnt]==-1&&s.dist<=L){
			D[s.node][s.rcnt]=s.dist;
			for(edge e:E[s.node]){
				pq.push({e.to,s.rcnt,s.dist+e.cost});
			}
			if(s.rcnt<N){
				for(edge e:R[s.node]){
					pq.push({e.to,s.rcnt+1,s.dist+e.cost});
				}
			}
		}
	}

    // 出力
	for(int i=0;i<N;i++){
		if(D[N-1][i]!=-1){
			cout<<i<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
}