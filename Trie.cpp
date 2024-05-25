class Trie {
public:
    Trie* next[26];
    int isEnd;
    Trie() {
        memset(next, 0, sizeof(next));
        isEnd = 0;
    }
    void insert(string& word) {
        Trie* cur = this;
        for (auto& ch : word) {
            if (cur->next[ch - 'a'] == NULL) {
                cur->next[ch - 'a'] = new Trie();
            }
            cur = cur->next[ch - 'a'];
        }
        cur->isEnd++;
    }
    void erase(string& word) {
        Trie* cur = this;
        for (auto& ch : word) {
            cur = cur->next[ch - 'a'];
            if (cur == NULL) {
                return;
            }
        }
        cur->isEnd--;
    }
    bool search(string& word) {
        Trie* cur = this;
        for (auto& ch : word) {
            cur = cur->next[ch - 'a'];
            if (cur == NULL) {
                return false;
            }
        }
        return cur->isEnd >= 1;
    }
};

Trie TrieNode;
TrieNode.insert("apple");
TrieNode.insert("bug");
TrieNode.insert("ape");
TrieNode.search("ape");