#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int maxV = 2e4+1;
const int maxE = 3e5+1;
const int IF = 1e9;

int v, e, w;
int start;

#if 0
void sol()
{
	cin >> v >> e;
	cin >> start;

    int g[v][v];
    memset(g, 0, sizeof(g));

	for (int i = 0; i < e; i++) {
		for (int j = 0; j < e; j++)
			if (i != j) g[i][j] = IF;
	}

	for (int i = 0; i < e; i++) {
		int tmpu, tmpv, tmpw;
		cin >> tmpu >> tmpv >> tmpw;
		g[tmpu][tmpv] = tmpw;
	}

	int D[maxV];

	memset(D, IF, sizeof(D));

	for (int i = 0; i < e; i++) {
		D[i] = g[start][i];
	}

	for (int i = 0; i < v; i++) {
		if (D[i] > 0) {
			for (int j = 0; j < v; j++) {
				D[i] = min(D[i], g[j][i] + D[j]);
			}
		}
	}

	for (int i = 1; i <= v; i++) {
		if (D[i] == IF) cout << "INF" << endl;
		else            cout << D[i] << endl;
	}
}
#endif

void sol1()
{
    int cnt = 0;
    cin >> v >> e;
    cin >> start;

    vector<pair<int,int>> G[v+1];
    for(int i=0; i<e; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        G[u].push_back(make_pair(v,w));
    }

    int Dist[v+1];
    fill(Dist, Dist+v+1, IF);
    Dist[start] = 0;
    priority_queue<pair<int,int>> pq;

    pq.push(make_pair(Dist[start], start));

    while(!pq.empty()) {
        int w = pq.top().first;
        int here = pq.top().second;
        pq.pop();

        for(int i=0; i<G[here].size(); i++) {
            int next = G[here][i].first;
            int nextcost = G[here][i].second;

            if(Dist[next] > Dist[here] + nextcost) {
                Dist[next] = Dist[here] + nextcost;
                pq.push(make_pair(-Dist[next], next));
            }
        }
    }

    for(int i=1; i<=v; i++) {
        if(Dist[i]== IF)    cout << "INF" << endl;
        else                cout << Dist[i] << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    sol();
    //sol1();
}