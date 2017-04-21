#include<cstdio>
#include<cmath>
#include<map>
#include<iostream>
using namespace std;
int mod_pow(long long x, long long p, long long mod_v)
{
	long long v = 1;
	while(p)
	{
		if(p & 1) v = x * v % mod_v;
		x = x * x % mod_v;
		p >>= 1;
	}

	return v;
}

int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}

int baby_step_giant_step(int a, int b, int p)
{
	a %= p, b %= p;
	if(b == 1) return 0;
	int cnt = 0;
	long long t = 1;
	for(int g = gcd(a, p); g != 1; g = gcd(a, p))
	{
		if(b % g) return -1;
		p /= g, b /= g, t = t * a / g % p;
		++cnt;
		if(b == t) return cnt;
	}

	map<int, int> hash;
	int m = int(sqrt(1.0 * p) + 1);
	long long base = b;
	for(int i = 0; i != m; ++i)
	{
		hash[base] = i;
		base = base * a % p;
	}

	base = mod_pow(a, m, p);
	long long now = t;
	for(int i = 1; i <= m + 1; ++i)
	{
		now = now * base % p;
		if(hash.count(now))
			return i * m - hash[now] + cnt;
	}

	return -1;
}

int main()
{
	int a, b, p;
	a = 3;
	p = 2147483647;
    long long n, m;
	while(scanf("%lld%lld", &n, &m)!=EOF)
	{
	    long long x1 = baby_step_giant_step(a, n, p);
	    long long x2 = baby_step_giant_step(a, m, p);
	    if (x1 == -1|| x2 == -1)
	    {
            puts("No Solution");
            continue;
	    }
		long long ans = mod_pow(m, x1, p);
		cout << ans <<endl;
	}
	return 0;
}
