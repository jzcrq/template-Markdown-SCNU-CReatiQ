vector<int> manacher(vector<int> s)
{
	vector<int> t{0};
	for (auto c:s)
	{
		t.push_back(c);
		t.push_back(0);
	}
	int n=t.size();
	vector<int> r(n);
	for (int i=0,j=0;i<n;i++)
	{
		if (j*2-i>=0&&j+r[j]>i) r[i]=min(r[j*2-i],j+r[j]-i);
		while (i-r[i]>=0&&i+r[i]<n&&t[i-r[i]]==t[i+r[i]]) r[i]++;
		if (i+r[i]>j+r[j]) j=i;
	}
	return r;
}
