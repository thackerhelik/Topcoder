/*input
say we are solving for segment[l, r] r not included
then we have 2 options
dp[l][r] = 1 + dp[l + 1][r] //just archive mail l
find k such that mail[l] = mail[k] and dp[l][r] = dp[l + 1][k] + dp[k][r] //i will be achived with k so no need to add 1
minimum is answer
*/
#include <bits/stdc++.h>
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)
typedef long long int ll;
using namespace std;
struct MailArchiving
{
	
	vector<string>destFolders_Global;	
	int n;
	int dp[55][55];

	int solve(int l, int r){
		if(l >= r)return 0;
		int& ans = dp[l][r];
		if(ans != -1)return ans;
		ans = 1 + solve(l + 1, r);
		for(int i = l + 1; i < r; ++i){
			if(destFolders_Global[l] == destFolders_Global[i]){
				ans = min(ans, solve(l + 1, i) + solve(i, r));
			}
		}
		return ans;
	}

	int minSelections(vector <string> destFolders)
	{
		destFolders_Global = destFolders;
		n = destFolders.size();
		memset(dp, -1, sizeof(dp));
		return solve(0, n);
	}
};
