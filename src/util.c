#include "util.h"

F32 sq_root(U32 x) {
	F32 z = 1.f;
	for (U8 i = 0; i <= 10; ++i)
		z -= (z * z - x) / (2 * z);
	return z;
}

U32 countDigits(I32 num) {
	U32 n = ABS(num);
#ifndef __has_builtin
#define __has_builtin(x) 0
#endif // __has_builtin
#if __has_builtin(__builtin_clz)
		// This increments the upper 32 bits (log10(T) - 1) when >= T is added.
#define K(T) (((sizeof(#T) - 1ull) << 32) - T)
		static const U64 table[] = {
			K(0),          K(0),          K(0),           // 8
			K(10),         K(10),         K(10),          // 64
			K(100),        K(100),        K(100),         // 512
			K(1000),       K(1000),       K(1000),        // 4096
			K(10000),      K(10000),      K(10000),       // 32k
			K(100000),     K(100000),     K(100000),      // 256k
			K(1000000),    K(1000000),    K(1000000),     // 2048k
			K(10000000),   K(10000000),   K(10000000),    // 16M
			K(100000000),  K(100000000),  K(100000000),   // 128M
			K(1000000000), K(1000000000), K(1000000000),  // 1024M
			K(1000000000), K(1000000000)                  // 4B
		};
  		return (n + table[__builtin_clz(n | 1) ^ 31]) >> 32u;
#undef K
#else
		int count = 1;
		for (;;) {
			if (n < 10) return count;
			if (n < 100) return count + 1;
			if (n < 1000) return count + 2;
			if (n < 10000) return count + 3;
			n /= 10000u;
			count += 4;
		}
		return count;
#endif
}

Frac fracAdd(Frac x, Frac y) { return (Frac) {(x.a * y.b) + (y.a * x.b), x.b * y.b}; }
Frac fracSub(Frac x, Frac y) { return (Frac) {(x.a * y.b) - (y.a * x.b), x.b * y.b}; }
Frac fracMul(Frac x, Frac y) { return (Frac) {x.a * y.a, x.b * y.b}; }
Frac fracDiv(Frac x, Frac y) { return (Frac) {x.a * y.b, x.b * y.a}; }

