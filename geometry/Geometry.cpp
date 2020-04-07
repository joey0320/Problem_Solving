struct Point{
    double x, y;
    Point operator + (Point rhs){
        return {x + rhs.x, y + rhs.y};
    }
    Point operator - (Point rhs){
        return {x - rhs.x, y - rhs.y};
    }
    bool operator < (Point rhs){
        if(x!=rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
};
typedef vector<Point> Polygon;
double dot(Point a, Point b){
    return a.x * b.x + a.y * b.y;
}
double dis_square(Point a, Point b){
    return dot(a-b, a-b);
}
double ccw(Point a, Point b){
    return a.x * b.y - a.y * b.x;
}
double ccw(Point a, Point b, Point c){
    return ccw(b - a, c - b);
}
bool cmpxy(Point a, Point b){
    if(a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
bool cmpccw(Point a, Point b){
    if(ccw(a, b) != 0) return ccw(a, b) > 0;
    return dot(a, a) < dot(b, b);
}
bool segmentintersect(Point a, Point b, Point c, Point d){// 선분 ab & cd가 교차하는지 확인
    double r1 = ccw(a, b, c) * ccw(a, b, d);
    double r2 = ccw(c, d, a) * ccw( c, d, b);
    if(r1 == 0 && r2 == 0){ //a, b, c, d가 한 직선위에
        if( b < a) swap( a,b);
        if( d < c) swap( c,d);
        return !(b < c || d < a);
    }
    return (r1 <= 0)&& (r2<=0);
}
bool isinside(Point x, Polygon p){
    int cnt = 0;
    int num = (int) p.size();
    for(int i = 0; i<num; i++){
        int ni = (i + 1) %num;
        if( (x.y < p[i].y) != (x.y < p[ni].y) ){
            double x_intersect = (x.y - p[i].y) * ( p[ni].x - p[i].x ) / (p[ni].y - p[i].y) + p[i].x;
            if(x_intersect > x.x) cnt++;
        }
    }
    return cnt%2 > 0;
}
bool polygonintersect(Polygon p, Polygon q){
    int sp = (int)p.size();
    int sq = (int)q.size();

    //하나의 convexhull이 다른 하나의 convexhull에 포함되는지 check
    // bool pinq = true, qinp = true;
    // for(int i = 0 ;i<sp;i++){
    //     if(!isinside(p[i], q)) pinq = false;
    // }
    // for(int i = 0; i<sq; i++){
    //     if(!isinside(q[i], p)) qinp = false;
    // }
    // if(pinq || qinp) return false; //하나가 다른 하나에 완전히 포함되면 교점 없음
    if(isinside(p[0], q) || isinside(q[0], p)) return true;

    for(int i=0; i<sp; i++){
        for(int j=0; j<sq; j++){
            int ni = (i+1)%sp, nj = (j+1)%sq;
            if( segmentintersect(p[i], p[ni], q[j], q[nj]) ) return true;
        }
    }
    return false;
}
vector<Point> convexhull(vector<Point> p){
    int num = (int)p.size();
    sort(all(p), cmpxy);
    double x0 = p[0].x, y0 = p[0].y;
    for(auto& t : p){
        t.x -= x0;
        t.y -= y0;
    }
    sort(p.begin() + 1, p.end(), cmpccw);
    vector<Point> s;
    s.push_back(p[0]);
    s.push_back(p[1]);
    int next = 2;
    while(next < num){
        while(s.size() >= 2){
            Point sec = s.back(); s.pop_back();
            Point fir = s.back();
            if( ccw(fir, sec, p[next] ) > 0){
                s.push_back(sec);
                break;
            }
        }
        s.push_back(p[next++]);
    }
    for(auto& v: s){
        v.x += x0;
        v.y += y0;
    }
    return s;
}
double rotcal(Polygon p){
    int sz = (int)p.size();
    ll dmax = 0;
    if(sz==2) return sqrt( dis_square(p[0], p[1]) );
    for(int i = 0, j = 0; i < sz; ){
        int ni = (i + 1) % sz, nj = (j + 1) % sz;
        if( ccw(p[i] - p[ni], p[j] - p[nj]) >= 0) j = nj;
        else i++;
        if( i==sz ) break;
        if( dis_square(p[i], p[j]) > dmax) dmax = dis_square(p[i], p[j]);
    }
    return sqrt(dmax);
}