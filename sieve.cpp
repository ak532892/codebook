int SIZE = ; // max(num)
int maxPrimeSize = SIZE + 1; //should be larger than max value
vector<bool> isPrime(maxPrimeSize + 1, true);
vector<int> prefixPrimeCount(maxPrimeSize + 1);
auto sieve = [] {
    if (maxPrimeSize < 0) {
        return 0;
    }
    if (maxPrimeSize == 0) {
        isPrime[0] = false;
        return 0;
    }
    isPrime[0] = isPrime[1] = false;
    if (maxPrimeSize == 1) {
        return 0;
    }
    for (int i = 2; i <= maxPrimeSize; i++) {
        if (isPrime[i]) {
            prefixPrimeCount[i] = prefixPrimeCount[i - 1] + 1;
            for (long long j = (long long)i * i; j <= maxPrimeSize; j += i) {
                isPrime[j] = false;
            }
        }
        else {
            prefixPrimeCount[i] = prefixPrimeCount[i - 1];
        }
    }
    return 0;
}();
