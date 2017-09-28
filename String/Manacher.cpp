#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int maxn = 111000;
char c[maxn], s[maxn*2];
int p[maxn*2];
void manacher(int n)
{
	int mx = 0, id = 0;
	for (int i = 1; i < n; ++i)
	{
		if (mx > i) p[i] = min(p[2*id-i], mx - i);
		else p[i] = 1;
		while (s[i+p[i]] == s[i-p[i]]) p[i]++;
		if (p[i]+i > mx)
		{
			mx = p[i]+i;
			id = i;
		}
	}
}
int main()
{
	int k, l;
	while (scanf("%s", c)!=EOF)
	{
		l = strlen(c);
		s[0] = '!';
		k = 1;
		for (int i = 0; i < l; ++i)
		{
			s[k++] = '#';
			s[k++] = c[i];
		}
		s[k++] = '#';
		s[k++] = '\0';
		l = strlen(s);
		manacher(l);
		int maxx=0;
/*		for (int i = 1; i < l; ++i)
			cout << p[i] << " ";
		cout << endl;*/
		for (int i = 1; i < l; ++i)
			if (p[i] > maxx)
				maxx = p[i];
		cout << maxx-1 << endl;
	}
	return 0;
}
