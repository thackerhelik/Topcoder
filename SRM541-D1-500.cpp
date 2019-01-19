/*
There are a few things in this problem.
We introduce a string hack = left + * + middle + * + right.
length of the string at t^th iteration will be lenth[t] = 2*length[t - 1] + |left| + |middle| + |right|
and result[t] = 2*result[t - 1] + A(t)
where A(t) is the number of times F occurs as substring such that it touches left, middle or right.
Notice that A(t) becomes constant after |F| iterations.
*/
#include <bits/stdc++.h>
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)
typedef long long int ll;
using namespace std;

const int MOD = 1e9+7;
const int basic = 50;

struct AkariDaisukiDiv1
{
	string hack; //this is equal to left*middle*right
	string S, F;

	ll len[basic];

	//get the pth character of f^t(S)
	char get(ll t, ll p){	
		if(t == 0){
			if(p >= S.length()){
				return '-';
			}
			return S[(int)p];
		}
		ll x = len[t - 1];
		for(int i = 0; i < hack.size(); ++i){
			if(hack[i] == '*'){
				if(p < x)return get(t - 1, p);
				p -= x;
			}
			else if(p == 0)return hack[i];
			else p--;
		}
		return '-';
	}

	//count number of times F is a substring of f^t(S) such that some part is overlapping with left or middle or right
	int A(int t){
		cout << t << endl;
		int res = 0;
		ll p = 0, x = len[t - 1];
		vector<ll>valid;

		for(int i = 0; i < hack.size(); ++i){
			if(hack[i] == '*'){
				for(int o = 1; o <= x && o < F.length(); ++o){
					valid.push_back(p+x-o);
				}
				p += x;
			}
			else{
				valid.push_back(p);
				p++;
			}
		}	
		for(int i = 0; i < valid.size(); ++i){
			bool ok = true;
			for(int j = 0; j < F.length() && ok; ++j){
				ok = (get(t, valid[i] + j) == F[j]);
			}
			res = res + ok;
		}
		return res;
	}

	int countF(string Waai, string Akari, string Daisuki, string S, string F, int k)
	{
		hack = Waai + "*" + Akari + "*" + Daisuki;
		this->S = S;
		this->F = F;

		len[0] = (int)S.length();
		for(int i = 1; i < basic; ++i){
			len[i] = 2*len[i - 1] + (int)hack.length() - 2;
		}

		//calculate how many times F is a substring of S
		ll a = 0;
		ll r = 0;
		for(int i = 0; i < (int)S.length(); ++i){
			int x = (int)F.length();			
			r = r + (S.substr(i,x) == F);
		}

		for(int i = 1; i <= k; ++i){
			if(i < basic){
				a = A(i);
			}
			r = (2*r + a)%MOD;
		}
		return r;

	}
};
