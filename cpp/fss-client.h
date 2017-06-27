#ifndef FSS_CLIENT_H
#define FSS_CLIENT_H

#include "fss-common.h"
#include <cmath>
#include <gmp.h>
#include <gmpxx.h>

// Initializes client. numBits is number of bits in input domain
void initializeClient(Fss* f, uint32_t numBits);

// Creates keys for a function that evaluates to b when input x = a.
void generateTreeEq(Fss* f, ServerKeyEq* k0, ServerKeyEq* k1, uint64_t a_i, uint64_t b_i);

#endif
