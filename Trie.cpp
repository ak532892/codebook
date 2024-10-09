class Trie {
public:
    Trie *next[26];
    int isEnd;
    Trie() {
        memset(next, 0, sizeof(next));
        isEnd = 0;
    }
    void insert(string& word) {
        Trie *cur = this;
        for (char& c : word) {
            if (cur->next[c - 'a'] == nullptr) {
                cur->next[c - 'a'] = new Trie();
            }
            cur = cur->next[c - 'a'];
        }
        cur->isEnd++;
    }
    void erase(string& word) {
        Trie *cur = this;
        for (char& c : word) {
            if (cur->next[c - 'a'] == nullptr) {
                return;
            }
            cur = cur->next[c - 'a'];
        }
        cur->isEnd--;
    }
    bool search(string& word) {
        Trie *cur = this;
        for (char& c : word) {
            if (cur->next[c - 'a'] == nullptr) {
                return false;
            }
            cur = cur->next[c - 'a'];
        }
        return cur->isEnd >= 1;
    }
};

Trie TrieNode;
TrieNode.insert("apple");
TrieNode.insert("bug");
TrieNode.insert("ape");
TrieNode.search("ape");
