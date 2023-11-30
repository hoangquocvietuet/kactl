/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: Wikipedia
 * Description: Subset Sum Convolution \\
 * - f o g(s') = sum(s in s') f(s) * g(s - s')
 */

// Make fhat[][] = {0} and ghat[][] = {0}
for(int mask = 0; mask < (1 << N); mask++) {
    fhat[__builtin_popcount(mask)][mask] = f[mask];
    ghat[__builtin_popcount(mask)][mask] = g[mask];
}

// Apply zeta transform on fhat[][] and ghat[][]
for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
        for(int mask = 0; mask < (1 << N); mask++) {
            if((mask & (1 << j)) != 0) {
                fhat[i][mask] += fhat[i][mask ^ (1 << j)];
                ghat[i][mask] += ghat[i][mask ^ (1 << j)];
            }
        }
    }
}

// Do the convolution and store into h[][] = {0}
for(int mask = 0; mask < (1 << N); mask++) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j <= i; j++) {
            h[i][mask] += fhat[j][mask] * ghat[i - j][mask];
        } 
    }
}

// Apply inverse SOS dp on h[][]
for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
        for(int mask = 0; mask < (1 << N); mask++) {
            if((mask & (1 << j)) != 0) {
                h[i][mask] -= h[i][mask ^ (1 << j)];
            }
        }
    }
}
for(int mask = 0; mask < (1 << N); mask++)  fog[mask] = h[__builtin_popcount(mask)][mask];
