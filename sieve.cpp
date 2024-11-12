int SIZE = ; // [0, SIZE] find prime number 
vector<int> is_prime(SIZE + 1, 1);

// if SIZE >= 46340, better use IsPrime function
// #define PRIME_TABLE
#ifdef PRIME_TABLE
vector<int> prime_table; 
#endif

auto Sieve = []() -> int {
    if (SIZE == 0) {
        is_prime[0] = 0;
        return 0;
    }
    if (SIZE >= 1) {
        is_prime[0] = is_prime[1] = 0;
    }
    for (int i = 2; i * i <= SIZE; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= SIZE; j += i) {
                is_prime[j] = 0;
            }
        }
    }
#ifdef PRIME_TABLE
    for (int i = 2; i <= SIZE; ++i) {
        if (is_prime[i]) {
            prime_table.push_back(i);
        }
    }
#endif
    return 0;
}();

#ifdef PRIME_TABLE
bool IsPrime(int num) {
    if (num <= SIZE) {
        return is_prime[num];
    }

    for (int i = 0; i < prime_table.size(); ++i) {
        if (num % prime_table[i] == 0) {
            return false;
        }
    }
    return true;
}
#endif
