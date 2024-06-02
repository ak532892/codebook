class Solution {
public:
    struct PolyHash {
        /*
        WARNING: make sure the values in the array or string are in the range [0, 5e8]
        */
        vector<long long> powers;
        vector<long long> powers2;
        vector<long long> hashes;
        vector<long long> hashes2;
        long long seed = 500002961;
        long long seed2 = 500003263;
        const long long mod = (long long)1e9+7;
        const long long mod2 = 998244353;
        vector<long long> arr;
        void init(long long n) {
            powers.resize(n + 5);
            powers[0] = 1;
            powers2.resize(n + 5);
            powers2[0] = 1;
            hashes.resize(n + 5);
            hashes2.resize(n + 5);
            for (long long i = 1; i <= n; i++) {
                powers[i] = powers[i - 1] * seed;
				powers[i] %= mod;
                powers2[i] = powers2[i - 1] * seed2;
				powers2[i] %= mod2;
            }
            for (long long i = 1; i <= n; i++) {
                hashes[i] = hashes[i - 1] * seed+arr[i];
                hashes[i] %= mod;
                hashes2[i] = hashes2[i - 1] * seed2+arr[i];
                hashes2[i] %= mod2;
            }
        }
        void init(long long n, string& s) {
            //string is 0 indexed
            arr.resize(n + 5);
            for (long long i = 1; i <= n; i++) {
                arr[i] = s[i - 1];
            }
            init(n);
        }
        void init(long long n, vector<long long> num) {
            //num is 0 indexed
            arr.resize(n + 5);
            for (long long i = 1; i <= n; i++) {
                arr[i] = num[i - 1];
            }
            init(n);
        }
        pair<long long,long long> subhash(long long l, long long r) {
            // inclusive
            // 1 indexed
            long long hsh = hashes[r] - hashes[l - 1] * powers[r - l + 1] % mod;
			hsh += mod; hsh %= mod;
            long long hsh2 = hashes2[r] - hashes2[l - 1] * powers2[r - l + 1] % mod2;
			hsh2 += mod2; hsh2 %= mod2;
            return {hsh, hsh2};
        }
    };
    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        int n = nums.size(), m = pattern.size();
        vector<long long> s2(n - 1, 0), strPattern2(m, 0);
        string s;
        for (int i = 0; i < n - 1; ++i) {
            if (nums[i + 1] > nums[i]) {
                s += 'a';
                s2[i] = 1;
            }
            else if (nums[i + 1] == nums[i]) {
                s += 'b';
                s2[i] = 2;
            }
            else if (nums[i + 1] < nums[i]) {
                s += 'c';
                s2[i] = 3;
            }
        }
        string strPattern;
        int j = 0;
        for (auto p : pattern) {
            if (p == 1) {
                strPattern += 'a';
                strPattern2[j] = 1;
            }
            else if (p == 0) {
                strPattern += 'b';
                strPattern2[j] = 2;
            }
            else if (p == -1) {
                strPattern += 'c';
                strPattern2[j] = 3;
            }
            ++j;
        }
        int res = 0;
        PolyHash p1, p2;
        p1.init(s.size(), s);
        p2.init(strPattern.size(), strPattern);
        for (int i = 0; i + m - 1 < s.size(); ++i) {
            if (p1.subhash(i + 1, i + m) == p2.subhash(1, m)) {
                res++;
            }
        }

        int res2 = 0;
        PolyHash p3, p4;
        p3.init(n - 1, s2);
        p4.init(m, strPattern2);
        for (int i = 0; i + m - 1 < n - 1; ++i) {
            if (p3.subhash(i + 1, i + m) == p4.subhash(1, m)) {
                res2++;
            }
        }
        return res;
    }
};
