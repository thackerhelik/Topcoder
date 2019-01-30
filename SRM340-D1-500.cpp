/*
total states of dp = 51^3
maintain a traceback for building the solution
states are current theoretical skill, current practical skill and current month
dp returns minimum number of courses and then we call construct to build the solution using trace array
*/
#include <bits/stdc++.h>
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)
#define sz(x) (int)(x).size()
typedef long long int ll;
using namespace std;
struct CsCourses
{

	int dp[55][55][55];
	int trace[55][55][55];
	int skillBound_global;
	int mx_size;
	vector<int>TheoreticalValue, PracticalValue, Expire;

	int solve(int t, int p, int m){
		if(t >= skillBound_global && p >= skillBound_global)return 0;
		if(m >= mx_size)return 1000000000;
		if(dp[t][p][m] != -1)return dp[t][p][m];
		int ret = 1000000000;
		for(int i = 0; i < mx_size; ++i){
			if(t >= TheoreticalValue[i] - 1 && p >= PracticalValue[i] - 1 && m < Expire[i]){
				int cur = solve(max(t, TheoreticalValue[i]), max(p, PracticalValue[i]), m + 1) + 1;
				if(cur < ret){
					ret = cur;
					trace[t][p][m] = i;
				}
			}
		}
		return dp[t][p][m] = ret;
	}

	vector<int>construct(){
		vector<int>ret;
		int t = 0, p = 0, m = 0;
		while(t < skillBound_global || p < skillBound_global){
			if(m > 52)break;
			int nxt = trace[t][p][m];
			ret.push_back(nxt);
			t = max(t, TheoreticalValue[nxt]);
			p = max(p, PracticalValue[nxt]);
			m = m + 1;
		}
		return ret;
	}

	vector <int> getOrder(vector <int> theoreticalValue, vector <int> practicalValue, vector <int> expire, int skillBound)
	{
		skillBound_global = skillBound;
		mx_size = sz(theoreticalValue);
		TheoreticalValue = theoreticalValue;
		PracticalValue = practicalValue;
		Expire = expire;
		memset(dp, -1, sizeof(dp));
		vector<int>ret;
		int val = solve(0, 0, 0);
		if(val < 1000000000)
			ret = construct();
		return ret;
	}
};
