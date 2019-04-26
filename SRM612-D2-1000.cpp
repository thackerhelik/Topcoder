/*(Approach same as editorial)
We can place a 0 at kth bit by taking even numbers of 2^k and 1 by taking odd number.
solve from the smallest bit and carry over the rest
if we are taking even number then we can carry over value/2. WHY? Because if I take 0 2^k then I can put rest as 2^(k + 1) but if take 2 then only (value - 2)/2 go to 2^(k + 1) but then there is carry over so add 1
in general if i take 2k from value and carry over (value - 2k)/2 then it becomes 2k/2 k as carry over to next bit and add it to value/2 - k it becomes value/2
(THIS IS THE MAIN AND NICE OBSERVATION)
and if we are taking odd number then we carry over (value - 1)/2
*/
#include <bits/stdc++.h>
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)
typedef long long int ll;
using namespace std;

struct PowersOfTwo
{

	long long dp[75][55];

	long long solve(vector<long long>X, int bit, int carry){
		
		if(bit > 70)return 1;

		if(dp[bit][carry] != -1)return dp[bit][carry];
		ll& ans = dp[bit][carry];

		ans = 0;

		ll value = X[bit] + carry;

		ans = ans + solve(X, bit + 1, value / 2); //place 0 bit so use even and value / 2 gets carried over

		if(value > 0)
			ans = ans + solve(X, bit + 1, (value - 1) / 2); // place 1 bit


		return ans;
	}	

	long long count(vector<long long> powers)
	{
		vector<ll>X(75);
		for(int i = 0; i < 75; ++i)
			X[i] = 0;
		for(auto it: powers){
			X[log2(it)]++;
		}
		memset(dp, -1, sizeof(dp));
		return solve(X, 0, 0);
	}
};
