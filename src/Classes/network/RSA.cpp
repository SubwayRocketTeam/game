#include "pch.h"
#include "RSA.h"

int modexp(int n, int e, int m){
	int residue = 1;
	while (e > 0) {
		if (e % 2 == 1)
			residue = (residue * n) % m;
		n = (n * n) % m;
		e >>= 1;
	}
	return residue;
}