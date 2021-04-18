// Competitive programming ready to use functions - Utkarsh Nanda LNMIIT
//Add your own functions with proper comments :)
/* To do input/output through files
#ifndef ONLINE_JUDGE 
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); 
#endif
*/
/* TEMPLATE:

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,j,k) for(int i = j; i <= k; i++)
#define pb push_back
#define pf push_front
#define mp make_pair
#define pi 3.14159265358979323846
#define mod 1000000007

int32_t main()
{
    ios_base::sync_with_stdio(false); // remove it at the time of debugging
	cin.tie(NULL);
	cout.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {

	}
}	

For sortng container of pairs : 

bool sortpair(pair<int, int> a, pair<int, int> b)
{
	if (a.first < b.first)
		return true;
	else
		return false;
}

*/
#include <bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int range = 10000000;
int prime[10000000];
void sieve()						 // 0 means prime, -1 means non prime O(n) = nlog(n)
{									 // change range according to the problem
	memset(prime, 0, sizeof(prime)); // initializes all the values in array "prime" with 0
	prime[1] = -1;
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
{				   // change range acconding to the problem
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
long long nPr(long long n, int r, int p) // Returns nPr % p using Fermat's little theorem. O(n + log(p)) = O(n) u
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

	return ((fac[n] % p) * (modInverse(fac[n - r], p) % p)) % p;
}
int digitcount(int n, int b) // O(1)
{
	// n shouldn't have leading zeros
	if (n == 0)
		return 1;
	else if (n < 0)
		n *= -1;
	int digits = floor(log10(n) / log10(b)) + 1;
	return digits;
}
string allCombinations() // O(1) but will have to be called 2^n times making it O(2^n)
{						 // reminder : a bitset keeps only set values stored
	static int i = 0;	 // it contains values from right to left with 0 based indexing
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
int floorSqrt(int x) // floor of square root of a number using binary search O(n) = log(n)
{
	if (x == 0 || x == 1) // Base cases
		return x;
	int start = 1, end = x, ans;
	while (start <= end)
	{
		int mid = (start + end) / 2;
		if (mid * mid == x)
			return mid;
		if (mid * mid < x) // Since we need floor, we update answer when mid*mid is smaller than x, and move closer to sqrt(x)
		{
			start = mid + 1;
			ans = mid;
		}
		else
			end = mid - 1;
	}
	return ans;
}
map<int, int> prime_array;					// map stores index - exponent pairs, if number of test cases is < 10^4 then it can be used
vector<pair<int, int>> prime_factors(int n) // as clear() function works in O(n)
{											//O(n) = sqrt(n)
	vector<pair<int, int>> prime_pairs;		//it returns a vector of pair of prime number and its power
	int count = 0;
	if (n == 0)
		return prime_pairs;
	else
	{
		while (n % 2 == 0)
		{
			count++;
			n = n / 2;
		}
		if (count != 0)
		{
			prime_array[2] = count;
			prime_pairs.push_back(make_pair(2, count));
		}
		for (int i = 3; i <= sqrt(n); i = i + 2)
		{
			count = 0;
			while (n % i == 0)
			{
				count++;
				n = n / i;
			}
			if (count != 0)
			{
				prime_array[i] = count;
				prime_pairs.push_back(make_pair(i, count));
			}
		}
		if (n > 2)
		{
			prime_array[n] = 1;
			prime_pairs.push_back(make_pair(n, 1));
		}
		return prime_pairs;
	}
}
float area(int x1, int y1, int x2, int y2, int x3, int y3) // to calclulate area of a triangle, given the three points
{
	return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}
pair<int, int> longest_consecutive_chain(int ar[], int size) // O(n) = n, returns the pair of element and length of
{															 //longest consecutive chain of number in the array
	pair<int, int> mxm;										 // if multiple chain with same length then return the first
	int prev = -1;
	int count = 0;
	int j = 0;
	while (j < size)
	{
		int i = 0;
		count = 0;
		while (ar[i + j] == ar[j] && ar[i + j] != size - 1)
		{
			count++;
			i++;
		}
		if (count > mxm.second) // make this '>=' to get the last chain with largest length
		{
			mxm = {ar[j], count};
		}
		j += count;
	}
	return mxm;
}
int longest_consecutive_chain_of_one(int ar[], int size) // O(n) = n, returns the length of longest consecutive chain of 1
{
	int mxm = 0;
	int prev = 0;
	int count = 0;
	for (int j = 0; j < size; j++)
	{
		if (ar[j] == 1)
		{
			count++;
			prev = 1;
		}
		else if (prev == 1 && ar[j] == 0)
		{
			prev = 0;
			mxm = max(count, mxm);
			count = 0;
		}
		if (j == size - 1)
		{
			mxm = max(count, mxm);
		}
	}
	return mxm;
}
int nCr(int n, int r) // O(n) = n/2, this is the most optimal way to count nCr. // function overriding with another function
{
	int a = n - r;
	int b = r;
	int mim = 0, mxm = 0;
	if (a > b) // reduce the part from numerator which is greater among a and b
	{
		mxm = a;
		mim = b;
	}
	else
	{
		mxm = b;
		mim = a;
	}
	int numerator = 1;
	for (int i = mxm + 1; i <= n; i++)
	{
		numerator *= i;
		numerator /= (i - mxm); // dividing by the smaller among a and b, doing here so that numerator doesn't overflow long long capacity
	}
	return numerator;
}
int sum_of_digits(int num) // O(n) = length of number
{
	int sum = 0ll;
	while (num != 0)
	{
		sum += (num % 10);
		num /= 10;
	}
	return sum;
}
vector<int> allPrime;
void allPrimeFactors(int n) // O(n) = sqrt(n), vector allPrime contains all the factors of n
{
	// Note that this loop runs till square root
	for (int i = 1; i <= sqrt(n); i++)
	{
		if (n % i == 0)
		{
			// If divisors are equal, print only one
			if (n / i == i)
				allPrime.push_back(i);

			else // Otherwise print both
			{
				allPrime.push_back(i);
				allPrime.push_back(n / i);
			}
		}
	}
}
vector<int> num_in_diff_base(int n, int base) // O(n) = log(n), returns a vector of number in a given base
{											  // values are indexed from right to left, reverse it to convert into standard form
	vector<int> v;							  // vector size represents length of nubmer in that base
	int index = 0;
	while (n)
	{
		v.push_back(n % base);
		index++;
		n /= base;
	}
	return v;
}
bool isBalanced(string exp) // O(n) = n(length of the string), tells whether a sequence of small brackets is balanced or not
{
	bool flag = true;
	int count = 0;
	for (int i = 0; i < exp.length(); i++)
	{
		if (exp[i] == '(')
			count++;
		else
			count--;
		if (count < 0)
		{
			flag = false;
			break;
		}
	}
	if (count != 0)
		flag = false;
	return flag;
}
bool is_pall(string x) // O(n) = n
{
	string y = x;
	reverse(y.begin(), y.end());
	if (y == x)
		return true;
	else
		return false;
}
void rotate(int *ar, int size, int indexing, string dir)		 // O(n) = n, ar = array of which elements to rotate
{																 // size = total size of the array
	int temp = dir == "right" ? ar[size - 1] : ar[0 + indexing]; // indexing = indexing used in the array, 0 based or 1 based
	int ar2[size] = {0};										 // dir = direction to rotate the array, right or left

	if (dir == "right") // it manipulates the string sent as parameter, thus doesn't return anything
	{
		for (int i = 1 + indexing; i <= size - 1; i++)
			ar2[i] = ar[i - 1];
	}
	else
	{
		for (int i = 1 + indexing; i <= size - 1; i++)
			ar2[i - 1] = ar[i];
	}
	dir == "right" ? ar2[0 + indexing] = temp : ar2[size - 1] = temp;
	for (int i = 0; i <= size - 1; i++)
		ar[i] = ar2[i];
}
void rotate(vector<int> &ar, int size, int indexing, string dir)		 // O(n) = n, ar = array of which elements to rotate
{																 // size = total size of the array
	int temp = dir == "right" ? ar[size - 1] : ar[0 + indexing]; // indexing = indexing used in the array, 0 based or 1 based
	vector<int> ar2(size);									 // dir = direction to rotate the array, right or left

	if (dir == "right") // it manipulates the string sent as parameter, thus doesn't return anything
	{
		for (int i = 1 + indexing; i <= size - 1; i++)
			ar2[i] = ar[i - 1];
	}
	else
	{
		for (int i = 1 + indexing; i <= size - 1; i++)
			ar2[i - 1] = ar[i];
	}
	dir == "right" ? ar2[0 + indexing] = temp : ar2[size - 1] = temp;
	for (int i = 0; i <= size - 1; i++)
		ar[i] = ar2[i];
}
string rotate(string ar, string dir) // O(n) = n, string ar = string to rotate, dir = direction to rotate
{									 // returns rotated string
	int size = ar.size();
	char temp = dir == "right" ? ar[size - 1] : ar[0];
	string ar2;
	for (int i = 0; i < size; i++)
	{
		ar2 += '.';
	}
	if (dir == "right")
	{
		for (int i = 1; i <= size - 1; i++)
			ar2[i] = ar[i - 1];
	}
	else
	{
		for (int i = 1; i <= size - 1; i++)
			ar2[i - 1] = ar[i];
	}
	dir == "right" ? ar2[0] = temp : ar2[size - 1] = temp;
	return ar2;
}
int32_t main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout << nPr(5, 3, mod);
}
