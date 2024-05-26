vector<int> getPrimeFactors(int num) {
    vector<int> result;
    for (int i = 2; i * i <= num; i++) {
        //if (num % i == 0) {
            while (num % i == 0) {
                num /= i;
                result.push_back(i);
            }
        //}
    }
    if (num != 1) {
        result.push_back(num);
    }
    return result;
}