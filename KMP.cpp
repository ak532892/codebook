vector<int> calculateMaxMatchLengths(string pattern) {
    int n = pattern.size();
    vector<int> maxMatchLengths(n, 0);
    int maxLength = 0;
    for (int i = 1; i < n; ++i) {
        while (maxLength > 0 && pattern[maxLength] != pattern[i]) {
            maxLength = maxMatchLengths[maxLength - 1];
        }
        if (pattern[maxLength] == pattern[i]) {
            maxLength++;
        }
        maxMatchLengths[i] = maxLength;
    }
    return maxMatchLengths;
}

vector<int> kmp(string &text, string &pattern) {
    vector<int> maxMatchLengths = calculateMaxMatchLengths(pattern);
    vector<int> positions;
    int count = 0;
    for (int i = 0; i < text.length(); i++) {
        while (count > 0 && pattern[count] != text[i]) {
            count = maxMatchLengths[count - 1];
        }
        if (pattern[count] == text[i]) {
            count++;
        }
        if (count == pattern.size()) {
            positions.push_back(i - pattern.size() + 1);
            count = maxMatchLengths[count - 1];
        }
    }
    return positions;
}