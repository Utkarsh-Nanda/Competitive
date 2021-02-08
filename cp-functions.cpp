// Competitive programming ready to use functions - Utkarsh Nanda LNMIIT
//Add your own functions with proper comments :)
#include <bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int range = 10000000;
int prime[10000000];
void sieve() // 0 means prime, -1 means non prime O(n) = nlog(n)
{
	memset(prime, 0, sizeof(prime)); // initializes all the values in array "prime" with 0
	for (int p = 2; p * p <= range; p++)
	{
		if (prime[p] == 0)
		{
			for (int i = p * p; i <= range; i += p)
				prime[i] = -1;
		}
	}
}
int factor[10000000];
int sieve_factor() // numbers with only 1 or 2 factors are prime numbers O(n) = nlog(n)
{
	memset(factor, 0, sizeof(factor));
	for (int i = 1; i <= range; i++)
	{
		for (int j = i; j <= range; j += i)
		{
			factor[j]++;
		}
	}
}
int fact_mod(int n, int mo) // to calculate factorial modulo a number O(n) = n
{
	int fact = n;
	if (n == 0)
		return 1;
	else
	{
		while (n-- > 1)
		{
			fact = (fact * n) % mo;
		}
		return fact;
	}
}

long long power(int x, int y, int p) // x raised to y modulo p in O(log(n))
{
	int res = 1; // Initialize result

	while (y > 0)
	{
		// If y is odd, multiply x with result
		if (y & 1)
			res = (res * x) % p;

		// n must be even now
		y = y >> 1;		 // y = y/2
		x = (x * x) % p; // Change x to x^2
	}
	return res;
}

long long modInverse(long long n, int p) // Returns n^(-1) mod p O(log(n)) as it uses logarithmic time to calculate power
{
	int y = p - 2;
	int x = n;
	int res = 1; // Initialize result

	while (y > 0)
	{
		// If y is odd, multiply x with result
		if (y & 1)
			res = (res * x) % p;

		// n must be even now
		y = y >> 1;		 // y = y/2
		x = (x * x) % p; // Change x to x^2
	}
	return res;
}

long long nCr(long long n, int r, int p) // Returns nCr % p using Fermat's little theorem. O(n + log(p)) = O(n) u
{										 // use in combination with modInverse funciton written just above
	// If n<r, then nCr should return 0
	if (n < r)
		return 0;
	// Base case
	if (r == 0)
		return 1;

	long long fac[n + 1];
	fac[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = (fac[i - 1] * i) % p;
	int div1 = modInverse(fac[r], p);

	return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) % p;
}
int digitcount(int n) // O(1)
{
	// n shouldn't have following zeros
	if (n == 0)
		return 1;
	else if (n < 0)
		n *= -1;
	int digits = floor(log10(n)) + 1;
	return digits;
}
string allCombinations() // O(1) but will have to be called 2^n times making it O(2^n)
{						 // reminder : a bitset keeps only set values stored
	static int i = 0;
	bitset<25> c(i);
	string s;
	bitset<25> d("1111111111111111111111111");
	c = i;	   // this is the particular arrangement
	d = c ^ d; // xor operation of c with a string of 1's of proper length
	s = c.to_string();
	//	s = d.to_string(); // use this to return opposite
	i++;
	return s;
}

string Combinations(int r) // O(1) but will have to be called 2^n times making it O(2^n)
{						   // reminder : a bitset keeps only set values stored
						   // loop this nCr times to get all the answers
	static int i = 0;
	string s;
	static bitset<5> c(0);
	while (c.count() != r) // increment i till i has exactly r bits set
	{
		i++;
		c = i;
	}
	s = c.to_string(); // this is the particular arrangement
	i++;
	c = i;
	return s;
}

vector<string> allPerm;					 // global variable
void permutation(string s, int k, int r) // O(n!*n)
{
	// start k with 0, r is 'r' in nPr, length of string is n of nPr
	// use with allPerm vector provided at the top to store all permutations
	static char result[10];
	static int temp[10] = {0};
	int i = 0;

	if (k == r)
	{
		//  cout << result << "\n";
		allPerm.push_back(result); // stores all the permutations
	}
	else
	{
		for (i = 0; s[i] != '\0'; i++)
		{
			if (temp[i] == 0)
			{
				temp[i] = 1;
				result[k] = s[i];
				permutation(s, k + 1, r);
				temp[i] = 0;
			}
		}
	}
}

int32_t main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif // ONLINE_JUDGE
	ios_base::sync_with_stdio(false);
	int count = 0;
	string s;
	cin>>s;
	int n;
	cin>>n;
	permutation(s, 0, n);
	for (auto i : allPerm)
	{
		cout << i << "\n";
	}
}
