// fib_cached.cpp

#include "cmpt_error.h"
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

//
// We define the Fibonacci numbers as follows:
//
//   F(0) = 1
//   F(1) = 1
//   F(n) = F(n-2) + F(n-1)   n > 1
//
// The first few Fibonacci numbers are:
//
//   1 1 2 3 5 8 13...
//

// Purely recursive version is very slow with larger values.
int fib_rec(int n) {
	if (n < 0) cmpt::error("fib_rec: n must be >= 0");
	if (n == 0) return 1;
	if (n == 1) return 1;
	return fib_rec(n-2) + fib_rec(n-1);
}

///////////////////////////////////////////////////////////////////////////////
//
// cache stores already-calculated Fibonacci numbers so they don't need to be
// calculated again.
//
///////////////////////////////////////////////////////////////////////////////

vector<int> cache;

int fib_cached(int n) {
	if (n < 0) cmpt::error("fib: n must be >= 0");
	if (n < cache.size()) {
		return cache[n];
	} else if (n == 0 || n == 1) {
		cache.push_back(1);
		return 1;
	} else {
		int result = fib_cached(n-2) + fib_cached(n-1);
		cache.push_back(result);
		return result;
	}
}

//
// The timings were calculated using the time command at the command-line, e.g.
//
//   $ time ./fib_cached
//   fib_cached(45) = 1836311903
//   0.00user 0.00system 0:00.00elapsed 100%CPU (0avgtext+0avgdata 3376maxresident)k
//   0inputs+0outputs (0major+123minor)pagefaults 0swaps
//
// The user time (the first time) is usually the most accurate time.
//

int main() {
	// cout << "fib_rec(45) = " << fib_rec(45) << "\n";  // 17.35s (no optimization)
	// cout << "fib_rec(45) = " << fib_rec(45) << "\n";  // 8.18s (-O3 optimization)
	cout << "fib_cached(45) = " << fib_cached(45) << "\n";  // 0.00s (no optimization)
}
