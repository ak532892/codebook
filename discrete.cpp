template <typename T>
vector<T> discrete(const vector<T>& nums, int& size) {
    auto sorted_nums = nums;
    ranges::sort(sorted_nums);
    sorted_nums.erase(unique(sorted_nums.begin(), sorted_nums.end()), sorted_nums.end());
    size = sorted_nums.size();
    return sorted_nums;
}
template <typename T>
// lower_bound：找出sorted_nums中 >= val的最小值的位置(最左邊的位置)
int findIdx(const vector<T>& sorted_nums, T val) {
    return ranges::lower_bound(sorted_nums, val) - sorted_nums.begin();
}
template <typename T>
// upper_bound - 1: 找出sorted_nums中 <= val的最小值的位置(最左邊的位置)：
int findIdx2(const vector<T>& sorted_nums, T val) {
    return ranges::upper_bound(sorted_nums, val) - sorted_nums.begin() - 1;
}
