i64 ceilDiv(i64 n,i64 m)
{
	if (n>=0) return (n+m-1)/m;
	else return n/m;
}

i64 floorDiv(i64 n,i64 m)
{
	if (n>=0) return n/m;
	else return (n-m+1)/m;
}

i128 gcd(i128 a,i128 b)
{
	return b?gcd(b,a%b):a;
}
