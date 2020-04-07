void preprocess(){
    int l = p.size();
    int j = 0;
    for(int i = 1; i<l; i++){
        while(j>0 && p[i] != p[j]) j = pi[j-1];
        if(p[i] == p[j]) pi[i] = ++j;
    }
}
void kmp(){
    int tlen = t.size();
    int plen = p.size();
    int j = 0;
    for(int i = 0; i<tlen; i++){
        while(j>0 && t[i] != p[j]) j = pi[j-1];
        if(t[i] == p[j]){
            if(j==plen-1) {
                vec.push_back(i - plen + 1);
                j = pi[j];
            }
            else j++;
        }
    }
}