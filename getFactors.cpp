vector<int> getFactors(int num) {
    vector<int> result;
    for (int i = 1; i * i <= num; i++) {
        if (num % i == 0) {
            result.push_back(i);
            if (i != (num / i)) {
                result.push_back(num / i);
            }
        }
    }
    return result;
}