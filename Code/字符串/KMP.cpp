vector<int> KMP(const string &s)
{
	int now=0;
	vector<int> pre(s.size(),0);
	for (int i=1;i<s.size();i++)
	{
		while (now&&s[i]!=s[now]) now=pre[now-1];
		if (s[i]==s[now]) now++;
		pre[i]=now;
	}
	return pre;
}
