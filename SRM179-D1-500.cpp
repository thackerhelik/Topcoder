/*
Assume our co-ordinate system is shifted by 0.5 so the center of the cell is integral
Now we have two integral co-ordinates (x1, y1) and (x2, y2) 
This segment can be split into gcd(|x1 - x2|, |y1 - y2|) segments
How?
Equation of line segment is (y - y1)/(x - x1) = (y2 - y1)/(x2 - x1)
So for every 1 unit change in x we have to change y by (y2 - y1)/(x2 - x1) i.e (x2 - x1) change in x for (y2 - y1) change in y
and we have to get integral co-ordinates. Reducing (y2 - y1) and (x2 - x1) to the lowest fraction gives us the answer.
And that is nothing but dividing both by gcd

Now the y2 - y1 and x2 - x1 can be both odd or even and odd
In both odd case it passes through a lattice point and hence we have to subtract 1 from each such segment that is subtract gcd from the Manhattan Distance

Proof of GCD:
Theorem: If a = bq + r (a > b) then gcd(a, b) = gcd(b, r)
Proof: Let d|a, d|b then d|(a - bq) Hence d|r since r = a - bq
       Let e|b, e|r then e|(bq + r) Hence e|a since a = bq + r
       
       That is d is a common divisor of a and b IFF d is a common divisor of b and r and gcd is the highest among all such d
*/
#include <bits/stdc++.h>
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)
typedef long long int ll;
using namespace std;
struct Regions
{
	int gcd(int a, int b){
		if(!b)return a;
		return gcd(b, a % b);
	}
	int numTaxes(vector <int> row, vector <int> col)
	{
		ll ans = 0;
		int n = (int)row.size();
		for(int i = 0; i < n - 1; ++i){
			int rowdiff = abs(row[i] - row[i + 1]);
			int coldiff = abs(col[i] - col[i + 1]);
			int g = gcd(rowdiff, coldiff);
			if(g == 0)continue;
			ans = ans + (rowdiff + coldiff - (((rowdiff/g)%2 == (coldiff/g)%2)?g:0));
		}
		return ans > 2e9 ? -1: (int)ans;
	}
};
