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
#define boost                         \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define testcases \
    int t;        \
    cin >> t;     \
    while (t--)
#define rep(i, j, k) for (int i = j; i <= k; i++)
#define repo(i, j, k) for (int i = j; i >= k; i--)
#define pb push_back
#define pf push_front
#define mp make_pair
#define mod 1000000007

int32_t main()
{
    boost;
	testcases
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

struct lexical_compare {
	bool operator() (int a, int b) const {
		return to_string(a) < to_string(b);
	}
};

// write lexical_compare in the comparator place

For ordered set
// include <ext/pb_ds/assoc_container.hpp>
// include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update> // dont't define int as long long when using this

For dfs on a 2D-grid:

            // down right up left
int dRow[] = { 0,  1,     0,  -1 };
int dCol[] = { -1, 0,     1,   0 };

// For Diagonals allowed

            // down up left right up-right up-left down-right down-left
int dRow[] = {  0,  0,  -1,   1,    1,       -1,       1,        -1}
int dCol[] = {  -1, 1,  0,    0,    1,       1,       -1,        -1};

bool isValid(int row, int column) // isValid function for dfs, bfs on grid
{
    if (row <= n && row >= 1 && column <= m && column >= 1 && graph[row][column] != '#' && vis[row][column] == 0)
        return true;
    else
        return false;
}

*/
#include <bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int prime[100001];
void sieve(int range)				 // 0 means prime, -1 means non prime O(n) = nlog(log(n))
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
int factor[1000000];
int sieve_factor(int range) // numbers with only 1 or 2 factors are prime numbers O(n) = nlog(n)
{							// change range acconding to the problem
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
		if (y & 1)
			res = (res * x) % p;
		y = y >> 1;		 // y = y/2
		x = (x * x) % p; // Change x to x^2
	}
	if (res < 0)
		return res + p;
	else
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
	if (res < 0)
		return res + p;
	else
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
long long nPr(long long n, int r, int p) // Returns nCr % p using Fermat's little theorem. O(n + log(p)) = O(n) u
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
string allCombinations(int n) // O(1) but will have to be called 2^n times making it O(2^n)
{							  // reminder : a bitset keeps only set values stored
	// static int i = 0;	 // it contains values from right to left with 0 based indexing
	bitset<25> c(n);
	string s;
	bitset<25> d("1111111111111111111111111");
	c = n;	   // this is the particular arrangement
	d = c ^ d; // xor operation of c with a string of 1's of proper length
	s = c.to_string();
	//	s = d.to_string(); // use this to return opposite i.e., to convert 1 to 0 and 0 to 1
	// i++;
	return s;
}
string Combinations(int r) // O(1) but will have to be called 2^n times making it O(2^n)
{						   // reminder : a bitset keeps only set values stored
						   // loop this nCr times to get all the answers
	static int i = 0;
	string s;
	static bitset<10> c(0);
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
int floorSqrt(int x)	  // floor of square root of a number using binary search O(n) = log(n)
{						  // precatuion : x must be less than equal to 10^9
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
	int count = 0;							// if getting TLE int 10^4 test cases, dont't use map, use vector of pairs that you return,										//  delete all the lines related to map.
	if (n == 0)								// that way no need to clear the map 10^4 times, which may sometime cause TLE,
		return prime_pairs;					// IF THE NUMBER IS 1 IT RETURNS NOTHING, KEEP THAT IN MIND
	else									// Use it with sieve to better time complexity,
	{										// so that we run the for loop only only for the prime numbers from 1 to sqrt(n)
		while (n % 2 == 0)					// and not every value from 1 to sqrt(n)
		{
			count++;
			n = n / 2;
		}
		if (count != 0)
		{
			prime_array[2] = count; // map line
			prime_pairs.push_back(make_pair(2, count));
		}
		// for (auto i : primes) // uncomment this line if using with sieve for optimisation, and comment out the below line
		for (int i = 3; i <= sqrt(n); i = i + 2) // this loop we are talking about above
		{
			if (i == 2)
				continue;
			count = 0;
			while (n % i == 0)
			{
				count++;
				n = n / i;
			}
			if (count != 0)
			{
				prime_array[i] = count; // map line
				prime_pairs.push_back(make_pair(i, count));
			}
		}
		if (n > 2)
		{
			prime_array[n] = 1; // map line
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
int sum_of_digits(int num) // O(n) = length of number, returns sum of digits of a number
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
void allFactors(int n) // O(n) = sqrt(n), vector allPrime contains all the factors of n
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
string numToString(int n, int base) // O(n) = log(n), length of the number in that base
{
	string s;
	int index = 0;
	while (n)
	{
		s.push_back((char)(n % base) + '0');
		index++;
		n /= base;
	}
	reverse(s.begin(), s.end());
	return s;
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
bool is_pall(string x) // O(n) = n, checks whether a string is pallindrome or not
{
	string y = x;
	reverse(y.begin(), y.end());
	if (y == x)
		return true;
	else
		return false;
}
void Rotate(string &s, int amt, string dir) // O(n) = n, rotates a string by the given amount, and in the direction mentioned as string in dir
{											// O(n) = n, rotates a string by the given amount, and in the direction mentioned as string
	if (dir == "left")						// input the amount as (amt % size)
		rotate(s.begin(), s.begin() + amt, s.end());
	else
		rotate(s.begin(), s.begin() + (s.size() - amt), s.end());
}
void Rotate(vector<int> &s, int amt, string dir) // O(n) = n, rotates a vector<int> elements by the given amount, and in the direction mentioned as string in dir
{												 // O(n) = n, rotates a string by the given amount, and in the direction mentioned as string
	if (dir == "left")							 // input the amount as (amt % size)
		rotate(s.begin(), s.begin() + amt, s.end());
	else
		rotate(s.begin(), s.begin() + (s.size() - amt), s.end());
}
int pairing_fun(pair<int, int> a) // O(n) = 1, returns a unique integer for a pair of integer, safe to use for if both the integers are less than 10^7
{								  // integers can be positive or negative
	int first = a.first;
	int second = a.second;
	if (first < 0)
		first += 1e8;
	if (second < 0)
		second += 1e8;
	int val = ((first + second) * (first + second + 1)) / 2 + second;
	return val;
}
string smaller_num(string one, string two) // O(n) = n(size of the smaller string), takes two numbers in string format and returns the smaller one.
{										   // two return the bigger number change '<' to '>' from all the places.
	if (one.size() < two.size())
		return one;
	else if (two.size() < one.size())
		return two;
	else
	{
		bool flag = false;
		for (int i = 0; i < one.size(); i++)
		{
			if (one[i] < two[i])
			{
				flag = true;
				return one;
				break;
			}
			else if (two[i] < one[i])
			{
				flag = true;
				return two;
				break;
			}
		}
		if (flag == false)
			return one;
	}
}
vector<pair<int, int>> zero_one(string s) // O(n) = n, n = length of the string.
{										  // returns a vector of pair, containing alternatively 0's and 1's with their no of consecutive occurences
	vector<pair<int, int>> temp;
	char prev = s[0];
	int count = 1;
	if (s.size() == 1)
		temp.push_back(make_pair(s[0] - '0', count));
	else
	{
		for (int i = 1; i < s.size(); i++)
		{
			if (s[i] == '1' && prev == '0')
			{
				temp.push_back(make_pair(0, count));
				count = 1;
				prev = '1';
			}
			else if (s[i] == '0' && prev == '1')
			{
				temp.push_back(make_pair(1, count));
				count = 1;
				prev = '0';
			}
			else
				count++;
			if (i == s.size() - 1)
				temp.push_back(make_pair(s[i] - '0', count));
		}
	}
	return temp;
}
void matrix_mul(int mat1[][3], int mat2[][3], int dim, int p) // it multiplies matrix A and B and store the result in A, modulo p O(n) = n^3, where n is dim
{															  // define N(where 3 is written) one greater than dimension
	int i, j, k;											  // as it's the size of the matrix, with zero based indexing
	int res[3][3];
	for (i = 1; i <= dim; i++)
	{
		for (j = 1; j <= dim; j++)
		{
			res[i][j] = 0;
			for (k = 1; k <= dim; k++)
				res[i][j] = (res[i][j] + (mat1[i][k] * mat2[k][j]) % p) % p;
		}
	}

	for (i = 1; i <= dim; i++)
	{
		for (j = 1; j <= dim; j++)
		{
			mat1[i][j] = res[i][j];
		}
	}
}
void matrix_exp(int res[][3], int n, int dim) // matrix exponentiation, use with matrix multiplication function just above, O(n) = log(n), n is the power
{											  // res is the base, n is the power, dim is the dimension of the matrix
	res[1][1] = 0;							  // final result of matrix exponentiation is stored in res itself.
	res[1][2] = 1, res[2][2] = 1, res[2][1] = 1;
	int iden[3][3] = {{0, 0, 0}, {0, 1, 0}, {0, 0, 1}}; // define identity matrix according to the size of matrix in problem
	while (n)
	{
		if (n % 2 == 0)
		{
			matrix_mul(res, res, 2, mod);
			n /= 2;
		}
		else
		{
			matrix_mul(iden, res, 2, mod); // updating identity matrix by res
			n--;
		}
	}
	for (int i = 1; i <= dim; i++)
	{
		for (int j = 1; j <= dim; j++)
		{
			res[i][j] = iden[i][j];
		}
	}
}
int lexo_compare(string s1, string s2) // O(n) = n, where n is minimum of size of s1 and s2
{									   // returns 1 if s1 is lexicographically after s2, returns -1 if s1 is before s2, else return 0(both are equal).
	if (s1 == s2)
		return 0;
	else
	{
		for (int i = 0; i <= min(s1.size(), s2.size()) - 1; i++)
		{
			if (s1[i] == s2[i])
				continue;
			if (s1[i] < s2[i])
				return -1;
			else if (s1[i] > s2[i])
				return 1;
		}
		if (s1.size() < s2.size())
			return -1;
		else
			return 1;
	}
}
int32_t main()
{
	int a = nCr(5, 3, mod);
	cout << a;
}
