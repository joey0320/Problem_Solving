const int Range = 128;
const int MX= 2050;
int t, n1, n2;
int cnt;
struct trie{
    int child;
    bool del, isend;
    trie* nxt[Range];
    trie(){
        child = 0;
        del = true;
        isend = false;
        for(int i=0; i<Range; i++) nxt[i] = NULL;
    }

    ~trie(){
        for(int i = 0; i<Range; i++) if(nxt[i]) delete nxt[i];
    }
    void insert(const char* key, bool able){
        if(*key=='\0') {
            isend = able;
            del = able;
        }
        else{
            int idx = *key;
            if(nxt[idx] == NULL)  nxt[idx] = new trie;
            del = able;
            nxt[idx]->insert(key+1, able);
        }
    }
    void dfs(){
        if(del) { ++cnt; return;}
        else if(isend) ++cnt;
        for(int i=0; i<Range; i++){
            if(nxt[i] != NULL){
                nxt[i]->dfs();
            }
        }
    }
};