#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<set>
#include<stack>
#include<queue>
#include<vector>

using namespace std;
#define ll long long
#define list vector<point>

const int maxn = 100009;

struct point{
    double x,y;
    bool operator <(point b)const{
        double th1 = atan2( y, x);
        double th2 = atan2( b.y, b.x);

        if(fabs(th1 - th2) < 1e-8)
            return x*x + y*y < b.x*b.x + b.y*b.y;
        return th1 < th2;
    }

    point operator -(point b)const{
        return (point){ x - b.x, y - b.y };
    }

    point operator +(point b)const{
        return (point){ x + b.x, y + b.y };
    }
};


bool cross(point P0, point P1, point P2){
    // printf("-------->>>>>>%.3f %.3f %.3f %.3f\n",P0.x, P0.y, P1.x, P1.y);
    P0 = P0 - P1;
    // printf("%.3f %.3f\n",P0.x, P0.y);
    P2 = P2 - P1;
    // printf("-------->>>>>>%.3f %.3f %.3f %.3f\n",P2.x, P2.y, P0.x, P0.y);
    // assert(0);
    double ans = P2.x * P0.y - P0.x * P2.y;
    return ans > 0;
}

double dis(point x, point y){
    return sqrt( (x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y) );
}

double Graham(list &vec){

    point min = vec[0];
    for(int i=1; i<vec.size(); ++i)
        if( vec[i].y < min.y )
            min = vec[i];

    for(int i=0; i<=vec.size(); ++i)
        vec[i] = vec[i] - min;

    sort(vec.begin(), vec.end());

    list sta;
    sta.push_back(vec[0]);
    sta.push_back(vec[1]);

    int i = 2;
    while( i < vec.size() ){
        if( cross( sta[sta.size()-2], sta.back(), vec[i] ) )
            sta.push_back(vec[i++]);
        else
            sta.pop_back();
    }    

    double ans = dis(sta[0], sta.back() );
    for(int i=1; i<sta.size(); ++i)
        ans += dis( sta[i-1], sta[i] );
    
    return ans;
}

int main(){
    int n;
    vector<point> vec;
    point buf;
    while(scanf("%d",&n) && n){
        vec.clear();
        for(int i=0; i<n; ++i){
            scanf("%lf %lf",&buf.x, &buf.y);
            vec.push_back(buf);
        }
        if( n == 1 )
            printf("0.00\n");
        else{
            if(n == 2){
                printf("%.2f\n", 2 * dis( vec[0], vec[1] ) );
            }
            else{
                double ans = Graham(vec);
                printf("%.2f\n", ans);
            }

        }
    }
}