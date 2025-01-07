vector<int> RabinKarp(string &text, string &pattern) {
    int s_len = text.size(), p_len = pattern.size();
    vector<int> match_index;

    if (p_len == 0) return match_index;
    if (s_len == 0) return match_index;

    const int MOD = 1e9 + 7;
    long long power = 1, base = 29;

    for (int i = 0; i < p_len; i++) {
        power = (power * base) % MOD;
    }

    long long pattern_hash = 0;
    for (int i = 0; i < p_len; i++) {
        pattern_hash = (pattern_hash * base + (pattern[i] - 'a')) % MOD;
    }

    long long text_hash = 0;
    for (int i = 0; i < s_len; i++) {
        text_hash = (text_hash * base + (text[i] - 'a')) % MOD;
        if (i < p_len - 1) {
            continue;
        }

        if (i >= p_len) {
            text_hash = (text_hash - (text[i - p_len] - 'a') * power) % MOD;

            if (text_hash < 0) {
                text_hash += MOD;
                text_hash %= MOD;
            }
        }

        if (text_hash == pattern_hash) {
            int start = i - p_len + 1;
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
