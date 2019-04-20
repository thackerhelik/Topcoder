/*
  for a character c, Group all the word having first and last same as c.
  Then add any word beginning with c to end and ending with c to start
  After all the characters a to z are done, we get few words. Group them and if they violate answer is IMPOSSIBLE
  If they dont violate see how many words are there. If only one then that word is answer. else return MANY
*/
#include <bits/stdc++.h>
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)
typedef long long int ll;
using namespace std;
struct GroupedWord
{
	string restore(vector <string> parts)
	{
		for(char c = 'a'; c <= 'z'; ++c){
			string word = "";
			for(int i = 0; i < (int)parts.size(); ){
				if(parts[i][0] == parts[i][parts[i].size() - 1] && parts[i][0] == c){
					word = word + parts[i];
					parts.erase(parts.begin() + i);
				}
				else{
					i++;
				}
			}
			for(int i = 0; i < (int)parts.size(); ){
				if(parts[i][parts[i].size() - 1] == c){
					word = parts[i] + word;
					parts.erase(parts.begin() + i);
					break;
				}
				else{
					i++;
				}
			}
			for(int i = 0; i < (int)parts.size(); ){
				if(parts[i][0] == c){
					word = word + parts[i];
					parts.erase(parts.begin() + i);
					break;
				}
				else{
					i++;
				}
			}
			if(word.size() > 0)
				parts.push_back(word);
		}
		
		// cout << parts.size() << endl;

		vector<char>word;
		for(auto it: parts){
			for(auto it2: it)
				word.push_back(it2);
		}

		
		

		auto it = unique(word.begin(), word.end());
		word.resize(distance(word.begin(), it));
		bool used[26];
		for(int i = 0; i < 26; ++i)
			used[i] = false;
		for(int i = 0; i < word.size(); ++i){
			if(used[word[i] - 'a'] == true)
				return "IMPOSSIBLE";
			used[word[i] - 'a'] = true;
		}

		if(parts.size() == 1)return parts[0];
		else return "MANY";
	}
};
