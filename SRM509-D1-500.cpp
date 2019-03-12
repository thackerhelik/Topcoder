/*
use floyd warshall to get change array : change[i][j] is minimum cost to change i to j
Trick: include Empty character to the alphabet so change[empty][i] means adding i and change[i][empty] means erasing i
find match array using change array : match[i][j] min cost to make i and j same
then normal dp to make palindrome
*/
#include <bits/stdc++.h>
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)
typedef long long int ll;
using namespace std;

const int nax = 51;
const int inf = 2000000000;

struct PalindromizationDiv1
{

	struct helik{
		int idx;
		char op_code;
		char c1, c2;
		int cost;
		helik():idx(-1), cost(-1){}
		helik(int idx, char a, char b, char c, int cost):idx(idx), op_code(a), c1(b), c2(c), cost(cost){}
	};

	string s;
	vector<struct helik>op;
	ll dp[nax][nax];

	ll adj[27][27];
	ll match[27][27];


	ll solve(int l, int r){
		if(l >= r)return 0;
		ll& ans = dp[l][r];
		
		if(ans != -1)return dp[l][r];
		
		ans = inf;

		int a = s[l] - 'a', b = s[r] - 'a';

		ans = min(ans, match[a][b] + solve(l + 1, r - 1));
		ans = min(ans, match[26][a] + solve(l + 1, r));
		ans = min(ans, match[26][b] + solve(l, r - 1));

		return ans;
	}

	int getMinimumCost(string word, vector <string> operations)
	{
		memset(dp, -1, sizeof(dp));

		if(operations.size() == 0){
			int lp = 0; int rp = (int)word.size() - 1;
			while(lp < rp){
				if(word[lp] != word[rp]){
					break;
				}
				lp++; rp--;
			}
			if(lp >= rp)return 0;
			else return -1;
		}

		s = word;
		int ctr = 0;
		for(auto it: operations){
			char c = it[0];
			char c1, c2;
			string cost = "";
			if(c == 'c'){
				int i = 1;
				while(it[i] != ' ')i++;
				i++;
				c1 = it[i];
				i++; i++;
				c2 = it[i];	
				i++; i++;
				while(i < int(it.size())){
					cost.push_back(it[i]);
					i++;
				}
				struct helik item; item.idx = ctr; item.op_code = c; item.c1 = c1; item.c2 = c2; item.cost = stoi(cost);
				op.push_back(item);
			}
			else if(c == 'e'){
				int i = 1;
				while(it[i] != ' ')i++;
				i++;
				c1 = it[i];
				i++; i++;
				while(i < int(it.size())){
					cost.push_back(it[i]);
					i++;
				}
				struct helik item; item.idx = ctr; item.op_code = c; item.c1 = c1; item.c2 = '#'; item.cost = stoi(cost);
				op.push_back(item);
			}
			else{
				int i = 1;
				while(it[i] != ' ')i++;
				i++;
				c1 = it[i];
				i++; i++;
				while(i < int(it.size())){
					cost.push_back(it[i]);
					i++;
				}
				struct helik item; item.idx = ctr; item.op_code = c; item.c1 = '#'; item.c2 = c1; item.cost = stoi(cost);
				op.push_back(item);
			}
			ctr++;
		}

		for(int i = 0; i <= 26; ++i)for(int j = 0; j <= 26; ++j)adj[i][j] = inf;

		for(int i = 0; i < 27; ++i){
			adj[i][i] = 0;
		}

		for(auto it: op){
			// if(it.op_code == 'c'){
				char c1 = it.c1;
				char c2 = it.c2;
				int cc1 = (c1 == '#') ? 26 : (int)c1 - 'a';
				int cc2 = (c2 == '#') ? 26 : (int)c2 - 'a';
				adj[cc1][cc2] = it.cost;
			// }
		}

		for(int k = 0; k < 27; ++k){
			for(int i = 0; i < 27; ++i){
				for(int j = 0; j < 27; ++j){
					if(adj[i][j] > adj[i][k] + adj[k][j])
						adj[i][j] = adj[i][k] + adj[k][j];
				}
			}
		}

		for(int i = 0; i < 27; ++i){
			for(int j = 0; j < 27; ++j){
				match[i][j] = inf;
				for(int k = 0; k < 27; ++k){
					if(adj[i][k] < inf && adj[j][k] < inf)
						match[i][j] = min(match[i][j], adj[i][k] + adj[j][k]);
				}
			}
		}
		
		int ans = solve(0, int(s.size()) - 1);
		if(ans >= inf)ans = -1;
		return ans;
	}
};
