/*input
Greedy solution works. Constraints are small. DP also is a solution.
*/
#include <bits/stdc++.h>
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)
typedef long long int ll;
using namespace std;
struct Piglets
{
	int choose(string trough)
	{
		int n = (int)trough.size();
		if(trough[0] == '-')return 0;
		if(trough[n - 1] == '-')return n - 1;
		for(int i = n - 2; i >= 0; --i){
			if(trough[i] == '-' && trough[i + 1] == '-')return i;
		}
		for(int i = 0; i < n; ++i)
			if(trough[i] == '-')return i;
		return -1;
	}
};
