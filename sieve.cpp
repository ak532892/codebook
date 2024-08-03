int maxPrimeSize = size + 1; //should be larger than max value
vector<bool> isPrime(maxPrimeSize + 1, true);
vector<int> primeTable;
void sieve(int size) {
	if (size < 0) {
		return;
	}
	if (size == 0) {
		isPrime[0] = false;
		return;
	}
	isPrime[0] = isPrime[1] = false;
	if (size == 1) {
		return;
	}
	int sqrt_size = sqrt(size);
	// size = sqrt_size
	// if we don't need primeTable, we can use only sqrt_size
	// that can reduce time complexity to sqrt(N)loglog(sqrt(N))
	// if we need primeTable, we would use [2, size]
	// time: O(Nloglog(N))
	for(int i = 2; i <= size; i++) {
		if(isPrime[i]) {
			primeTable.push_back(i);
			for(long long j = (long long)i * i; j <= size; j += i) {
				isPrime[j] = false;
			}
		}
	}
}
int main () {
	if (primeTable.empty()) {
		sieve(maxPrimeSize);
	}
}
