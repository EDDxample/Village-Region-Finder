#pragma once

#include <stdint.h>

static inline void setSeed(int64_t *seed)
{
    *seed = (*seed ^ 0x5deece66dLL) & ((1LL << 48LL) - 1);
}

static inline int next(int64_t *seed, const int bits)
{
    *seed = (*seed * 0x5deece66dLL + 0xbLL) & ((1LL << 48LL) - 1);
    return (int)(*seed >> (48 - bits));
}

static inline int nextIntP2(int64_t *seed, const int n)
{
    return (int)((n * (long long)next(seed, 31)) >> 31);
}

static inline int nextInt(int64_t *seed, const int n)
{
    int bits, val;
    const int m = n - 1;
    do
    {
        bits = next(seed, 31);
        val = bits % n;
    } while (bits - val + m < 0);
    return val;
}

static inline void setSeedMC(int64_t *seed, int x, int z)
{
    *seed += x * 341873128712LL + z * 132897987541LL + 10387319LL;
    setSeed(seed);
}

/* Useful for powers of 2 */
static inline void nextIntLoopP2(int64_t *seed, int times)
{
    for (int i = 0; i < times; ++i)
        nextIntP2(seed, 31);
}

static inline void nextIntLoop(int64_t *seed, int value, int times)
{
    for (int i = 0; i < times; ++i)
        nextInt(seed, value);
}