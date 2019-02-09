/*
There can be 26^N strings which is slow to brute
but the number of patterns is limited. (Bell numbers)
So for each pattern find the answer.
*/
#include <bits/stdc++.h>
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)
typedef long long int ll;
using namespace std;
struct PalindromfulString
{

	int N, M, K;
	ll ans;

	ll calcAns(char nextchar){
		ll ret = 1;
		ll base = 26;
		for(int p = 0; p < nextchar - 'a'; ++p){
			ret = ret * base;
			base--;
		}
		return ret;
	}

	void construct(int rem, string sofar, char nextchar){
		if(rem == 0){
			int total = 0;
			for(int t = 0; t < (int)sofar.length() - M + 1; ++t){
				bool check = true;
				int leftptr = t;
				int rightptr = leftptr + M - 1;
				while(rightptr >= t){
					if(sofar[leftptr] != sofar[rightptr]){
						check = false;
						break;
					}
					leftptr++;
					rightptr--;
				}
				if(check)
					total++;
			}
			if(total >= K)
				ans = ans + calcAns(nextchar);
			return;
		}
		construct(rem - 1, sofar + nextchar, nextchar + 1);
		for(char c = 'a'; c < nextchar; ++c)
			construct(rem - 1, sofar + c, nextchar);
		return;
	}

	long long count(int NN, int MM, int KK)
	{
		N = NN;
		M = MM;
		K = KK;
		construct(N, "", 'a');
		return ans;
	}
};
