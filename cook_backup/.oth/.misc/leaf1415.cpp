
#include <bits/stdc++.h>
#define rep(x, s, t) for(ll x = (s); (x) <= (t); (x)++)
#define per(x, s, t) for(ll x = (s); (x) >= (t); (x)--)

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct edge{
  ll to, cost;
  edge(){}
  edge(ll a, ll b){ to = a, cost = b;}
};

const int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
const double PI = 3.1415926535897932384626433;
//const int mod = 1000000007;
const int mod = 998244353;

struct mint{
  int x;
  mint(ll y = 0){if(y < 0 || y >= mod) y = (y%mod+mod)%mod; x = y;}
  mint(const mint &ope) {x = ope.x;}
  mint operator-(){return mint(-x);}
  mint operator+(const mint &ope){return mint(x) += ope;}
  mint operator-(const mint &ope){return mint(x) -= ope;}
  mint operator*(const mint &ope){return mint(x) *= ope;}
  mint operator/(const mint &ope){return mint(x) /= ope;}
  mint& operator+=(const mint &ope){x += ope.x; if(x >= mod) x -= mod; return *this;}
  mint& operator-=(const mint &ope){x += mod - ope.x; if(x >= mod) x -= mod; return *this;}
  mint& operator*=(const mint &ope){ll tmp = x; tmp *= ope.x, tmp %= mod; x = tmp; return *this;}
  mint& operator/=(const mint &ope){
    ll n = mod-2; mint mul = ope;
    while(n){if(n & 1) *this *= mul; mul *= mul; n >>= 1;}
    return *this;
  }
  mint inverse(){return mint(1) / *this;}
  bool operator ==(const mint &ope){return x == ope.x;}
  bool operator !=(const mint &ope){return x != ope.x;}
  bool operator <(const mint &ope)const{return x < ope.x;}
};
mint modpow(mint a, ll n){
  if(n == 0) return mint(1);
  if(n % 2) return a * modpow(a, n-1);
  else return modpow(a*a, n/2);
}
istream& operator >>(istream &is, mint &ope){ll t; is >> t, ope.x = t; return is;}
ostream& operator <<(ostream &os, mint &ope){return os << ope.x;}
ostream& operator <<(ostream &os, const mint &ope){return os << ope.x;}

ll modpow(ll a, ll n, ll mod){
  if(n == 0) return 1;
  if(n % 2) return ((a%mod) * (modpow(a, n-1, mod)%mod)) % mod;
  else return modpow((a*a)%mod, n/2, mod) % mod;
}

vector<mint> fact, fact_inv;
void make_fact(int n){
  fact.resize(n+1), fact_inv.resize(n+1);
  fact[0] = mint(1); rep(i, 1, n) fact[i] = fact[i-1] * mint(i);
  fact_inv[n] = fact[n].inverse(); per(i, n-1, 0) fact_inv[i] = fact_inv[i+1] * mint(i+1);
}
mint comb(int n, int k){ if(n < 0 || k < 0 || n < k) return mint(0); return fact[n] * fact_inv[k] * fact_inv[n-k];}
mint perm(int n, int k){ return comb(n, k) * fact[k]; }
template<typename T> T comb2(ll n, ll k){ if(n < 0 || k < 0 || n < k) return 0; T ret = 1; rep(i, 1, k) ret *= n-k+i, ret /= i; return ret;}

vector<int> prime, pvec, qrime;
void make_prime(int n){
  prime.resize(n+1);
  rep(i, 2, n){
    if(prime[i] == 0) pvec.push_back(i), prime[i] = i;
    for(auto p : pvec){ if(i*p > n || p > prime[i]) break; prime[i*p] = p;}
  }
}
void make_qrime(int n){
  qrime.resize(n+1);
  rep(i, 2, n){int ni = i / prime[i]; if(prime[i] == prime[ni]) qrime[i] = qrime[ni] * prime[i]; else qrime[i] = prime[i];}
}

bool exceed(ll x, ll y, ll m){return y > 0 && x >= m / y + 1;}
ll floor(ll a, ll b){ if(b < 0) a *= -1, b *= -1; if(a >= 0) return a/b; else return -((-a+b-1)/b); }
ll ceil(ll a, ll b){ if(b < 0) a *= -1, b *= -1; if(a >= 0) return (a+b-1)/b; else return -((-a)/b); }
ll modulo(ll a, ll b){ b = abs(b); return a - floor(a, b) * b;}
ll sgn(ll x){ if(x > 0) return 1; if(x < 0) return -1; return 0;}
ll gcd(ll a, ll b){if(b == 0) return a; return gcd(b, a%b);}
ll lcm(ll a, ll b){return a/gcd(a, b)*b;}
ll arith(ll x){return x*(x+1)/2;}
ll arith(ll l, ll r){return arith(r) - arith(l-1);}
ll digitnum(ll x, ll b = 10){ll ret = 0; for(; x; x /= b) ret++; return ret;}
ll digitsum(ll x, ll b = 10){ll ret = 0; for(; x; x /= b) ret += x % b; return ret;}
string lltos(ll x, ll b = 10){string ret; for(;x;x/=b) ret += x % b + '0'; reverse(ret.begin(),ret.end()); return ret;}
ll stoll(string &s, ll b = 10){ll ret = 0; for(auto c : s) ret *= b, ret += c - '0'; return ret;}
template<typename T> void uniq(T &vec){sort(all(vec)); vec.erase(unique(all(vec)), vec.end());}
int popcount(ull x){
  x -= ((x>>1)&0x5555555555555555ULL), x = (x & 0x3333333333333333ULL) + ((x>>2) & 0x3333333333333333ULL);
  return (((x + (x>>4)) & 0x0F0F0F0F0F0F0F0FULL) * 0x0101010101010101ULL) >> 56;
}

template<class S, class T> pair<S, T>& operator+=(pair<S, T> &s, const pair<S, T> &t){s.first += t.first, s.second += t.second; return s;}
template<class S, class T> pair<S, T>& operator-=(pair<S, T> &s, const pair<S, T> &t){s.first -= t.first, s.second -= t.second; return s;}
template<class S, class T> pair<S, T> operator+(const pair<S, T> &s, const pair<S, T> &t){return pair<S,T>(s.first+t.first, s.second+t.second);}
template<class S, class T> pair<S, T> operator-(const pair<S, T> &s, const pair<S, T> &t){return pair<S,T>(s.first-t.first, s.second-t.second);}
template<class T> T dot(const pair<T, T> &s, const pair<T, T> &t){return s.first*t.first + s.second*t.second;}
template<class T> T cross(const pair<T, T> &s, const pair<T, T> &t){return s.first*t.second - s.second*t.first;}

void dump_func(){cout << endl;}
template <class Head, class... Tail>
void dump_func(Head &&head, Tail &&... tail){cout << head; if(sizeof...(Tail) > 0) cout << " "; dump_func(std::move(tail)...);}
#define dbg(...) dump_func(__VA_ARGS__)

int main(void)
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  return 0;
}
 
 