#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

using namespace std;
// using namespace __gnu_pbds;

#ifndef ONLINE_JUDGE
#define now(x) cout << #x << " : " << x << '\n'; //" on line : "<<__LINE__<<'\n';
#define pm(m)            \
    cout << #m << " : "; \
    for (auto it : m)    \
        cout << it.fs << " " << it.ss << '\n';
#define fv(v)              \
    cout << #v << " : ";   \
    for (auto it : v)      \
        cout << it << " "; \
    cout << '\n';
#else
#define now(x) ;
#define fv(v) ;
#define pm(m) ;
#endif

template <typename T>
istream &operator>>(istream &istream, vector<T> &v)
{
    for (auto &it : v)
    {
        cin >> it;
    }
    return istream;
}

template <typename T>
ostream &operator<<(ostream &ostream, vector<T> &v)
{
    for (auto &it : v)
    {
        cout << it << " ";
    }
    return ostream;
}

const int mod = 1000000007;
const double pi = 3.1415926536;
const long long oo = 1e18;
#define FOR(i, z, n) for (int i = z; i < n; i++)
#define f(n) for (int i = 0; i < n; i++)
#define int ll
typedef long long ll;
typedef map<int, int> mii;
typedef vector<int> vi;
#define fs first
#define ss second
#define itf(v) v.begin(), v.end()
#define itr(v) v.rbegin(), v.rend()
int modu(int a, int b = mod) { return (a % b + b) % b; }
int log2(int x) { return __builtin_clzll(1LL) - __builtin_clzll(x); }
template <typename T>
T maxxx() { return numeric_limits<T>::max(); }
const int maxx = maxxx<int>();

// pbds
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
// template <typename T>
// using ordered_mset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

// find_by_order(K): Returns an iterator to the Kth largest element (counting from zero)
// order_of_key (K): Returns the number of items that are strictly smaller than K
// less_equal -> multisets

/* ---------------TEMPLATE ENDS HERE-------------*/

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int const N = 4001;
int tree[4001];
int lazy[4001];

void buildTree(int index, int s, int e, vector<int> &arr)
{
    // base case(s)
    if (s == e)
    {
        tree[index] = arr[s];
        return;
    }

    int mid = (s + e) / 2;
    buildTree(2 * index, s, mid, arr);
    buildTree(2 * index + 1, mid + 1, e, arr);
    tree[index] = tree[2 * index] + tree[2 * index + 1];
}

void updateRange(int index, int s, int e, int l, int r, int incr, vector<int> &arr)
{
    if (lazy[index] != 0)
    {
        tree[index] += (e - s + 1) * lazy[index];
        if (s != e)
        {
            lazy[2 * index] += lazy[index];
            lazy[2 * index + 1] += lazy[index];
        }
        lazy[index] = 0;
    }
    // no overlapping
    if (e < l || s > r)
    {
        return;
    }

    // complete overlapping
    if (l <= s && e <= r)
    {
        tree[index] += (e - s + 1) * incr;
        if (s != e)
        {
            lazy[2 * index] += incr;
            lazy[2 * index + 1] += incr;
        }
        return;
    }

    // partial overlapping
    int mid = (s + e) / 2;
    updateRange(2 * index, s, mid, l, r, incr, arr);
    updateRange(2 * index + 1, mid + 1, e, l, r, incr, arr);
    tree[index] = tree[2 * index] + tree[2 * index + 1];
}

int queryRange(int index, int s, int e, int l, int r, vector<int> &arr)
{

    if (lazy[index] != 0)
    {
        tree[index] += (e - s + 1) * lazy[index];
        if (s != e)
        {
            lazy[2 * index] += lazy[index];
            lazy[2 * index + 1] += lazy[index];
        }
        lazy[index] = 0;
    }

    if (e < l || s > r)
    {
        return 0;
    }
    // complete overlapping
    if (l <= s && e <= r)
    {
        return tree[index];
    }
    // partial overlapping
    int mid = (s + e) / 2;
    int leftSum = queryRange(2 * index, s, mid, l, r, arr);
    int rightSum = queryRange(2 * index + 1, mid + 1, e, l, r, arr);
    return leftSum + rightSum;
}

void solve()
{
    int n = 0, m = 0, k = 0, x = 0, count = 0, sum = 0, ans = 0;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    buildTree(1, 0, n - 1, arr);
    updateRange(1, 0, n - 1, 2, 4, 2, arr);
    for (int i = 0; i <= 16; i++)
    {
        cout << tree[i] << ' ';
    }
    cout << '\n';
    while (true)
    {
        int l, r;
        cin >> l >> r;
        sum = queryRange(1, 0, n - 1, l, r, arr);
        cout << sum << '\n';
    }
    cout << endl;
}

int32_t main()
{
    // ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /*
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    */

    int test_case = 1;
    // cin >> test_case;
    for (int _ = 0; _ < test_case; _++)
    { // cout<<"Case #"<<_+1<<": ";
        solve();
    }
    return 0;
}