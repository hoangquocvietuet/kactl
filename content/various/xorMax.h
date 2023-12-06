/**
 * Description: Given an array of integers, find the maximum XOR subarray value in given array.
 * Time: O(nlog(max(a[i])))
 */
typedef long long int ll;
typedef unsigned long long int ull;

ull check_bit(ull N, int POS) { return (N & (1ULL << POS)); }

vector<ull> v;
ull gaussian_elimination(vector<ull> v)
{
    sort(v.rbegin(), v.rend());
    int n = v.size();
    int ind = 0; // Array index
    for (int bit = log2(v[0]); bit >= 0; bit--)
    {
        int x = ind;
        while (x < n && check_bit(v[x], bit) == 0)
            x++;
        if (x == n)
            continue; // skip if there is no number below ind where current bit is 1
        swap(v[ind], v[x]);
        for (int j = 0; j < n; j++)
        {
            if (j != ind && check_bit(v[j], bit))
                v[j] ^= v[ind];
        }
        ind++;
    }
    ull ans = v[0];
    for (int i = 1; i < n; i++)
        ans = max(ans, ans ^ v[i]);
    return ans;
}