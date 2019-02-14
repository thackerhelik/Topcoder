/*
We have to prove that if there exists any vertex such that it is a part of cycle and it is reachable from 0 and it has outdegree > 1
then answer is out of bounds (that is -1). Can be done by finding transitive closure of graph (using floyd warshall)
It is obvious that if the above is true the answer is out of bounds since for that vertex it will at some point generate a copy of itself
and there will be atleast one other copy of a pingu since outdegree > 1 and this will keep on continuing
We have to prove that if the above condition doesn't hold then answer is finite
It is obvious we consider only nodes that are reachable from 0
If deg[i] == 1 and it is a part of cycle, all such cycles are disjoint (since to not be disjoint outdegree > 1)
so there is no new pinguo generation from cycles.
Removing cycles we get DAG, which is the source of the generation of pinguos
Now one more thing is that the number of pinguos after N moves becomes constant (If it doesn't go out of bounds)
? (This is because after atmost N moves all vertices of reachable from 0 will have been visited and so the process stops
   If it is part of cycle the number of pingous still remains same, but type changes) ?
So simulate the process until N moves and find the answer.
*/
#include <bits/stdc++.h>
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)

const int mod = 1000000007;

typedef long long int ll;
using namespace std;
struct MonsterFarm
{
	int numMonsters(vector <string> transforms)
	{
		int n = (int)transforms.size(), x;
		bool reachable[n][n];
		int adj[n][n];
		int outdeg[n];
		memset(reachable, false, sizeof(reachable));
		memset(adj, 0, sizeof(adj));
		memset(outdeg, 0, sizeof(outdeg));

		for(int i = 0; i < n; ++i){
			stringstream st;
			st << transforms[i];
			while(st >> x){
				outdeg[i]++;
				adj[i][x - 1]++;
				reachable[i][x - 1] = true;
			}
		}
		
		for(int k = 0; k < n; ++k){
			for(int i = 0; i < n; ++i){
				for(int j = 0; j < n; ++j){
					reachable[i][j] = reachable[i][j] || (reachable[i][k] && reachable[k][j]);
				}
			}
		}

		for(int i = 0; i < n; ++i){
			if(reachable[0][i] && outdeg[i] > 1 && reachable[i][i]){
				return -1;
			}
		}

		//Number grows only till maximum of N moves, after that becomes constant. (because after that all the vertices will be visited atleast once)
		//so simulate it
		ll ans = 0;
		ll monster[2][n];

		memset(monster, 0, sizeof(monster));

		monster[0][0] = 1; //we have initially 1 pingu


		for(int steps = 0; steps < n; ++steps){
			for(int i = 0; i < n; ++i)monster[1][i] = 0;
			for(int i = 0; i < n; ++i){
				for(int j = 0; j < n; ++j){
					monster[1][j] = (monster[1][j] + (monster[0][i]*adj[i][j])%mod)%mod;
				}
			}
			for(int i = 0; i < n; ++i)monster[0][i] = monster[1][i];
		}

		for(int i = 0; i < n; ++i){
			ans = (ans + monster[0][i])%mod;
		}

		return ans;
	}
};
