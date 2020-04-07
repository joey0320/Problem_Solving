  
//https://github.com/KwanghyunOn/Competitive-Programming/blob/master/String/Aho-Corasick.cpp 온광현 블로그 
const int alphabet = 26;
int chartoint(const char c){
    return c-'a';
}
struct node{
    node* next[alphabet];
    node* f; node* o;
    bool isend;
    node(){
        f = NULL, o = NULL;
        isend = false;
        for(int i=0; i<alphabet; i++) next[i]=NULL;
    }
    ~ node(){for(int i=0; i<alphabet; i++) if(next[i]) delete next[i]; }
    // void insert(const char *key) {
    //     if (*key == '\0') isend = true;
    //     else {
    //         int idx = chartoint(*key);
    //         if (!next[idx] == NULL) next[idx] = new node;
    //         next[idx]->insert(key + 1);
    //     }
    // }
};
node* root = new node();
void insert(string &s){
    auto cur = root;
    for(auto c: s){
        int idx = chartoint(c);
        if(!cur->next[idx]) cur->next[idx] = new node();
        cur = cur->next[idx];
    }
    cur->isend = true;
}
void buildtree(){
    queue<node*> q;
    for(int i = 0; i<alphabet; i++){
        if( root->next[i] ){
             root->next[i]->f = root;
             q.push( root->next[i] );
        }
    }
    while(!q.empty()){
        auto u = q.front(); q.pop();
        if(u->isend) u->o = u;
        else u->o = u->f->o;
        for(int i =0;i<alphabet; i++)if( u->next[i] ){
            auto v = u->next[i];
            v->f = u->f;
            while(v->f!=root && !v->f->next[i]) v->f = v->f->f;
            if(v->f->next[i]) v->f = v->f->next[i];
            q.push(v);
        }
    }
}
bool search(string& s){
    auto u = root;
    for(auto c: s){
        int idx = chartoint(c);
        while(u!=root && !u->next[idx]) u = u->f;
        if(u->next[idx]) u = u->next[idx];
        if(u->o) return true;
    }
    return false;
}