bool cmp(int x, int y){
    if (group[x] != group[y])
        return group[x] < group[y];
    return group[x + t] < group[y + t];
}
void suffixarray(){
    t = 1;
    int len = (int)s.size();
    for (int i = 0; i < len; i++){
        group[i] = s[i] - 'a';
        sa[i] = i;
    }
    while(t <= len){
        group[len] = -1;
        sort(sa, sa + len, cmp);
        tmp[sa[0]] = 0;
        for(int i = 1; i<len; i++){
            if( cmp( sa[i-1], sa[i] )) tmp[sa[i]] = tmp[sa[i-1]] + 1;
            else tmp[sa[i]] = tmp[sa[i-1]];
        }
        for(int i = 0; i<len; i ++){
            group[i] = tmp[i];
        }
        t<<=1;
    }
}
void longestcommonprefix(){
    int len = (int)s.size();
    int cnt = 0;
    for(int i = 0; i<len; i++){
        r[sa[i]] = i;
    }
    for(int i = 0; i<len; i++){
        int k = r[i];
        if(k){
            int j = sa[k-1];
            while( s[i + cnt] == s[j + cnt] ) cnt++;
            lcp[k] = cnt;
            if(cnt) cnt--;
        }
    }
}