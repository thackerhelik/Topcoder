/*
We only care about triangles. Any polygon can be split into triangles -- polygon triangulation
We only care about triangles with no interior points in input -- if there is we can split the triangle into multiple without increasing the area
dp[i] be the minimum area needed to cover the subset having mask i. DP with bitmask. Base case : all points covered so return 0
we have to try all the three points. O(2^n*n^3)
*/
#include <bits/stdc++.h>
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)
typedef long long int ll;
using namespace std;

const int nax = 16;
double dp[(1 << nax)];
vector <int> X;
vector <int> Y;
int n;

struct PolygonCover
{

	double area(int a, int b, int c){
		//cross product
		double ans = 0;
		int ab[2]; int ac[2];
		ab[0] = X[b] - X[a]; ab[1] = Y[b] - Y[a];
		ac[0] = X[c] - X[a]; ac[1] = Y[c] - Y[a];
		ans = abs(ab[0]*ac[1] - ab[1]*ac[0]);
		ans = ans / 2.0;

		return ans;
	}

	double solve(int mask){
		double& ans = dp[mask];
		if(ans >= 0.0)return dp[mask];
		if(__builtin_popcount(mask) == n)return 0.0;
		ans = 1e100;
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				if(i == j)continue;
				for(int k = 0; k < n; ++k){
					if(i == k || j == k)continue;
					if(!(mask & (1 << i)) || !(mask & (1 << j) || !(mask & (1 << k)))){
						ans = min(ans, solve(mask | (1 << i) | (1 << j) | (1 << k)) + area(i, j, k));
					}
				}
			}
		}
		return ans;
	}

	double getArea(vector <int> x, vector <int> y)
	{
		for(int i = 0; i < (1 << nax); ++i)
			dp[i] = -1.0;
		X = x; Y = y;
		n = (int)x.size();
		double ans = solve(0);
		return ans;
	}
};
