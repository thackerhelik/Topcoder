/*
Notice the constraints are small
this is optimization problem
We try to spread both the rumors all possible combinations 2^16 total combinations
Now update the known table in N*N
If finally number of days requires is infinite (here 20) answer is -1
*/
#include <bits/stdc++.h>
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)
typedef long long int ll;
using namespace std;
struct Rumor
{
	int getMinimum(string knowledge, vector <string> graph)
	{
		int i, j, n = knowledge.length();

		int ret = 20;

		for(int iter = 0; iter < (1<<n); ++iter){

			int days = 0;

			int know[n][2];
			int know2[n][2];

			for(i = 0; i < n; ++i){
				if(knowledge[i] == 'Y')
					know[i][0] = know[i][1] = 1;
				else
					know[i][0] = know[i][1] = 0;
			}

			for(i = 0; i < n; ++i){
				if(know[i][0] == 1 && know[i][1] == 1)
					continue;
				else break;
			}

			if(i >= n)return 0;


			int spreading[n];
			int spreaded[n];

			for(i = 0; i < n; ++i){
				spreading[i] = -1;
				spreaded[i] = -1;
			}

			for(i = 0; i < n; ++i){
				if(iter & (1 << i)){
					spreading[i] = 2; //rumor 2
				}
				else{
					spreading[i] = 1; //rumor 1
				}
			}


			while(true){

				days++;

				bool flag = false;

				for(i = 0; i < n; ++i){
					for(j = 0; j < 2; ++j){
						know2[i][j] = know[i][j];
					}
				}

				for(i = 0; i < n; ++i){
					for(j = 0; j < n; ++j){
						if(graph[j][i] == 'Y'){
							if(spreading[j] == 1 && know[j][0] == 1){
								spreaded[j] = 1;
								if(know[i][0] == 0){
									flag = true;
									know2[i][0] = 1;
								}
							}
							else if(spreading[j] == 2 && know[j][1] == 1){
								spreaded[j] = 1;
								if(know[i][1] == 0){
									flag = true;
									know2[i][1] = 1;
								}
							}
						}
					}
				}

				// know = know2;
				for(i = 0; i < n; ++i){
					for(j = 0; j < 2; ++j){
						know[i][j] = know2[i][j];
					}
				}

				for(i = 0; i < n; ++i){
					if(knowledge[i] == 'N'){
						if(know[i][1] == 1 && (iter & (1 << i))){
							spreading[i] = 2; //rumor 2
						}
						else if(know[i][1] == 2 && !(iter & (1 << i))){
							spreading[i] = 1; //rumor 1
						}
					}
				}


				for(i = 0; i < n; ++i){
					if(spreaded[i] == 1){
						if(iter & (1 << i)){
							spreading[i] = 1; //rumor 1
						}
						else{
							spreading[i] = 2; //rumor 2
						}
					}
				}

				for(i = 0; i < n; ++i){
					if(know[i][0] == 1 && know[i][1] == 1)
						continue;
					else break;
				}

				if(i >= n){
					ret = min(ret, days);
					break;
				}

				if(!flag)
					break;
			}

		}


		if(ret == 20)ret = -1;
		return ret;

	}
};
