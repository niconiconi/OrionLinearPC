#pragma once
#include "expanders.h"

prime_field::field_element *scratch[2][100];

bool __encode_initialized = false;

int encode(const prime_field::field_element *src, prime_field::field_element *dst, int n, int dep = 0)
{
    if(!__encode_initialized)
    {
        __encode_initialized = true;
        for(int i = 0; (n >> i) > 1; ++i)
        {
            scratch[0][i] = new prime_field::field_element[2 * n >> i];
            scratch[1][i] = new prime_field::field_element[2 * n >> i];
        }
    }
    if(n <= distance_threshold)
    {
        for(int i = 0; i < n; ++i)
            dst[i] = src[i];
        return n;
    }
    for(int i = 0; i < n; ++i)
    {
        scratch[0][dep][i] = src[i];
    }
    int R = alpha * n;
    for(int j = 0; j < R; ++j)
        scratch[1][dep][j] = prime_field::field_element(0ULL);
    //expander mult
    for(int i = 0; i < n; ++i)
    {
        const prime_field::field_element &val = src[i];
        for(int d = 0; d < C[dep].degree; ++d)
        {
            int target = C[dep].neighbor[i][d];
            scratch[1][dep][target] = scratch[1][dep][target] + C[dep].weight[i][d] * val;
        }
    }
    int L = encode(scratch[1][dep], &scratch[0][dep][n], R, dep + 1);
    assert(D[dep].L = L);
    R = D[dep].R;
    for(int i = 0; i < R; ++i)
    {
        scratch[0][dep][n + L + i] = prime_field::field_element(0ULL);
    }
    for(int i = 0; i < L; ++i)
    {
        prime_field::field_element &val = scratch[0][dep][n + i];
        for(int d = 0; d < D[dep].degree; ++d)
        {
            int target = D[dep].neighbor[i][d];
            scratch[0][dep][n + L + target] = scratch[0][dep][n + L + target] + val * D[dep].weight[i][d];
        }
    }
    for(int i = 0; i < n + L + R; ++i)
    {
        dst[i] = scratch[0][dep][i];
    }
    return n + L + R;
}