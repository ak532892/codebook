vector<int> getPrimeFactors(int num) {
	vector<int> pf;
    
    for (int d = 2; d * d <= num; ++d) {
        if (num % d == 0) {
        	pf.push_back(d);
            for (num /= d; num % d == 0; num /= d);
        }
    }
    
    if (num > 1) {
        pf.push_back(num);
    }
    return pf;
}