const long long mod = xxxxxxx;
struct Matrix
{
	long long m[maxn][maxn];
	Matrix()
	{
		memset(m, 0, sizeof(m));
		for (int i = 1; i <= n; ++i)
			m[i][i] = 1;
	}
};

Matrix Mul(Matrix a, Matrix b)
{
	Matrix c;
	for (int i = 0; i < n; ++i)
		for (int k = 0; k < n; ++k)
			for (int j = 0; j < n; ++j)
				c.m[i][j] = (c.m[i][j] + a.m[i][k]*b.m[k][j])% mod;
	return c;
}

Matrix Mpow(Matrix x, long long p, long long mod)
{
	Matrix v;
	while (p)
	{
		if (p&1)
			v = Mul(v, x);
		p >>=1;
		x = Mul(x, x);
	}
	return v;
}
