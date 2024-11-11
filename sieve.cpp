int SIZE = ; // [0, SIZE] find prime number 
vector<int> is_prime(SIZE + 1, 1);
// vector<int> prime_table; 

auto Sieve = [] () -> int {
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
    /*
    for (int i = 2; i <= SIZE; ++i) {
        if (is_prime[i]) {
            prime_table.push_back(i);
        }
    }
    */
    return 0;
}();
