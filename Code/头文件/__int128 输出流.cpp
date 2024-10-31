ostream &operator << (ostream &os,i128 n)
{
	string s;
	bool neg=n<0;
	if (neg) n=-n;
	while (n)
	{
		s+='0'+n%10;
		n/=10;
	}
	if (neg) s+='-';
	reverse(s.begin(),s.end());
	if (s.empty()) s+='0';
	return os<<s;
}
