/*
Observations:
1) It is useless to light the same cell multiple times
2) Order of lighting does not matter

With this we define the order to be row up to down and then column left to right in each row

Notice that cell (0, 0) can only be lighted by either (0,0) itself or (1,1)
Let us assume we aren't allowed to touch first row or column
Then we have a determined sequence of touches. (From (1,1) to (n, m))
That is (0, 0) can only be toggled by (1, 1), after that (0, 1) can be toggled only by (1, 2) and so on
(i, j) can be only toggled by (i + 1, j + 1)

Now we come back to our problem. We can check for all the possible toggles in first row and column
2^(8 + 8 - 1) max toggles.
Now for each toggle we find minimum.

Answer is -1 if there exists no way to toggle.
*/
#include <bits/stdc++.h>
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)
typedef long long int ll;
using namespace std;
struct LightedPanels
{

	//* means on

	int dx[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	int dy[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

	bool isvalid(int x, int y, int n, int m){
		return (x >= 0 && x < n && y >= 0 && y < m);
	}

	void toggle(int x, int y, vector<string>&board, int n, int m){
		for(int i = 0; i < 9; ++i){
			if(!isvalid(x + dx[i], y + dy[i], n, m))continue;
			if(board[x + dx[i]][y + dy[i]] == '*')board[x + dx[i]][y + dy[i]] = '.';
			else board[x + dx[i]][y + dy[i]] = '*';	
		}
	}

	int solve(vector<pair<int,int>>&toggled, vector<string>board, int n, int m){
		int ret = 0;
		for(auto it: toggled){
			toggle(it.first, it.second, board, n, m);
			ret++;
		}

		for(int i = 1; i < n; ++i){
			for(int j = 1; j < m; ++j){
				if(board[i - 1][j - 1] == '.'){
					toggle(i, j, board, n, m);		
					ret++;
				}
			}
		}

		for(int i = 0; i < n; ++i){
			for(int j = 0; j < m; ++j){
				if(board[i][j] == '.')
					return 10000;
			}
		}
		return ret;
	}

	int minTouch(vector <string> board)
	{
		int n = (int)board.size();
		int m = (int)board[0].size();
		int ans = 10000;
		vector<pair<int,int>>v;
		for(int i = n - 1; i >= 0; --i){
			v.push_back({i, 0});
		}
		for(int i = 1; i < m; ++i){
			v.push_back({0, i});
		}
		for(int i = 0; i < (1 << v.size()); ++i){
			vector<pair<int,int>>toggled;
			for(int j = 0; j < v.size(); ++j){
				if(i & (1 << j)){
					toggled.push_back(v[j]);
				}
			}
			ans = min(ans, solve(toggled, board, n, m));
		}
		if(ans == 10000)ans = -1;
		return ans;
	}
};
