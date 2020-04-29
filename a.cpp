/*
 * we can use dp bitmask to choose the order of visiting the cities
 * we use dijkstra to know the shortest path value between every pair of the special cities
*/
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 200
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll mod=1e15 + 37;
const ll inf=1e18*4;
const ld pai=acos(-1);
int n , m , k ;
vpi v [20009] ;
int need [29] , dp[ ( 1 << 19 ) ][20] ; 
int dis [21][20009] , done [20009] ;
void dijkstra ( int st ) {
	for ( int i = 0 ; i < n ; i ++ ) dis [st][i] = 1e9 , done[i] = 0 ;
	priority_queue < pi , vpi , greater < pi > > pq ;
	dis [st][st] = 0 ;
	pq .push ( { 0 , st } ) ;
	while ( pq.size() ) {
		int node = pq.top().se ;
		int t = pq.top().fi ;
		pq.pop();
		if ( t > dis [st][node] ) C ;
		done [ node ] = 1 ;
		for ( auto U : v [node] ) {
			int u = U .fi ;
			int x = U .se ;
			if ( done [u] ) C ;
			if ( t+x < dis [st][u] ) {
				dis [st][u] = t + x ;
				pq .push ( { dis [st][u] , u } ) ;
			}
		}
	}
}
int edit ( int mask , int last ) {
	int Mask = ( mask & ( ( 1 << last ) -1 ) ) ;
	mask >>= last +1 , mask <<= last ;
	mask |= Mask ;
	return mask ;
}
int bt ( int mask , int last ) {
	int Mask = edit ( mask , last ) ;
	if ( mask == ( 1 << k ) - 1 ) return dis [last+1][n-1] ;
	int &ret = dp [Mask][last] ;
	if ( ret != -1 ) return ret ;
	ret = 1e9 ;
	for ( int i = 0 ; i < k ; i ++ ) {
		if ( ( mask & ( 1 << i ) ) || i == last || ( mask & need [i] ) != need [i] ) C ;
		ret = min ( ret , bt ( ( mask | ( 1 << i ) ) , i ) + dis [last+1][i+1] ) ;
	}
	return ret ; 
}
int main () {
	mem ( dp , -1 ) ;
	scanf("%d%d%d",&n,&m,&k);
	for ( int i = 0 ; i < m ; i ++ ) {
		int a , b , c ;
		scanf("%d%d%d",&a,&b,&c);
		a -- , b -- ;
		v [a] .pb ( { b , c } ) ;
		v [b] .pb ( { a , c } ) ;
	}
	int q ;
	scanf("%d",&q);
	for ( int i = 0 ; i < q ; i ++ ) {
		int f , s ;
		scanf("%d%d",&f,&s) ;
		f -= 2 , s -= 2 ;
		need [s] |= ( 1 << f ) ;
	}
	for ( int i = 0 ; i <= k ; i ++ ) dijkstra ( i ) ;
	int ans = 1e9 ;
	if ( !k ) ans = dis[0][n-1] ;
	for ( int i = 0 ; i < k ; i ++ ) {
		if ( need [i] ) C ;
		int ret = bt ( ( 1 << i ) , i ) + dis [0][i+1] ;
		ans = min ( ans , ret ) ;
	}
	printf("%d\n",ans);
}
