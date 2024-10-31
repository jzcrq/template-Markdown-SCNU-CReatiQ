#include <bits/stdc++.h>
using namespace std;
using i64=long long;
using i128=__int128;

namespace DBG
{
	template <class T>
	void _dbg(const char *f,T t) { cerr<<f<<'='<<t<<'\n'; }

	template <class A,class... B>
	void _dbg(const char *f,A a,B... b)
	{
		while (*f!=',') cerr<<*f++;
		cerr<<'='<<a<<",";
		_dbg(f+1,b...);
	}

	template <class T>
	ostream& operator << (ostream& os,const vector<T> &v)
	{
		os<<"[ ";
		for (const auto &x:v) os<<x<<", ";
		os<<"]";
		return os;
	}

	#define dbg(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
}

using namespace DBG;
