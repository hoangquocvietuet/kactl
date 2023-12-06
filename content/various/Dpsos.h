/**
 * Description: sum over all subsets of a set.
 * Time: O(n \times 2^n).
 * Note: for calculating sum over all superset, just reverse the loop.
 */

#include <bits/stdc++.h>
using namespace std;

const int num_bit = 20;

int a[1 << num_bit];
int f[1 << num_bit]; // sum over subset. i.e: f[mask] = number of x such that x | mask = mask
int g[1 << num_bit]; // sum over superset. i.e: g[mask] = number of x such that x & mask = mask

int main()
{
    for (int i = 0; i < (1 << num_bit); ++i)
    {
        cin >> a[i];
        f[i] = g[i] = a[i];
    }
    for (int i = 0; i < num_bit; ++i)
    {
        for (int mask = 0; mask < (1 << num_bit); ++mask)
        {
            if (mask >> i & 1)
            {
                f[mask] += f[mask ^ (1 << i)];
            }
            else
            {
                g[mask] += g[mask | (1 << i)];
            }
        }
    }
    return 0;
}