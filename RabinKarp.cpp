vector<int> RabinKarp(string &text, string &pattern) {
    int sLen = text.size(), pLen = pattern.size();
    vector<int> match_index;

    if (pLen == 0) return match_index;
    if (sLen == 0) return match_index;

    const int MOD = 1e9 + 7;
    long long power = 1, base = 29;

    for (int i = 0; i < pLen; i++) {
        power = (power * base) % MOD;
    }

    long long pattern_hash2 = 0;
    for (int i = 0; i < pLen; i++) {
        pattern_hash2 = (pattern_hash2 * base + (pattern[i] - 'a')) % MOD;
    }

    long long text_hash1 = 0;
    for (int i = 0; i < sLen; i++) {
        text_hash1 = (text_hash1 * base + (text[i] - 'a')) % MOD;
        if (i < pLen - 1) {
            continue;
        }

        if (i >= pLen) {
            text_hash1 = (text_hash1 - (text[i - pLen] - 'a') * power) % MOD;

            if (text_hash1 < 0) {
                text_hash1 += MOD;
                text_hash1 %= MOD;
            }
        }

        if (text_hash1 == pattern_hash2) {
            int start = i - pLen + 1;
            // bool equal = true;
            // for (int j = start, k = 0; j <= i; j++, k++) {
            //     if (text[j] != pattern[k]) {
            //         equal = false;
            //         break;
            //     }
            // }

            // if (equal) {
                match_index.push_back(start);
            // }
        }
    }

    return match_index;
}
