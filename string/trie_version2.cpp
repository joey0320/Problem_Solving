const int maxn = 10;

struct Trie {
    struct Node {
        bool end;
        int child;
        Node *nxt[maxn];

        Node () : end(false), child(0) {
            for ( int i = 0; i < maxn; i++ ) nxt[i] = NULL;
        }

        ~Node() {
            for ( int i = 0; i < maxn; i++ ) delete nxt[i];
        }
    };

    Node* root = new Node();

    void insert ( string s ) {
        Node* cur = root;
        for ( auto c : s ) {
            int x = c - '0';
            if ( !cur->nxt[x] ) {
                cur->nxt[x] = new Node();
                cur->child++;
            }
            cur = cur->nxt[x];
        }
        cur->end = true;
    }
};
