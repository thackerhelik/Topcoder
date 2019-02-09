/*
given n a's and m z's the first string is 
aaa.......azzz.......z
  n times    m times
if we shift the first z to the left we get
aaaa....aazazz.......z
 n - 1         m - 1
 now we have m!/(1!*(m-1)!) ways
 
 In general, length!/(a!z!) ways to permute a string having a a's and z z's of length 'length'
 Now we keep shifting the first z until K becomes negative
 the previous step was the final position of first k
 and the problem reduces to (n - number of times z is shifted, m - 1, new k)
 make the string on the go
*/
#include <bits/stdc++.h>
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)
typedef long long int ll;
using namespace std;
struct TheDictionary
{

	int K;

	int position(int n, int m){

		int pos = n + 1, a = 0, length = m - 1;
		ll subtract = 1;
		while(1){
			if(K - subtract <= 0)return pos;
			pos--;
			if(pos <= 0)return pos;
			K = K - subtract;
			a++;
			length++;
			subtract = (subtract*length)/a;
		}
		return pos;

	}

	string find(int n, int m, int k)
	{
		string ans = ""; //build this answer on the go
		K = k;
		while(K >= 1){
			int pos = position(n, m);

			if(pos <= 0)return "";

			for(int i = 1; i < pos; ++i){
				ans.push_back('a');
				n--;
			}
			ans.push_back('z');
			m--;
			if(m <= 0 || n <= 0)break;
		}

		if(n > 0)while(n--)ans.push_back('a');
		if(m > 0)while(m--)ans.push_back('z');
		return ans;
	}
};
