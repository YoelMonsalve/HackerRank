#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

typedef uint32_t elem_t ;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N;
    elem_t S, P, Q, cnt;
    vector<elem_t> a;
        
    cin >> N >> S >> P >> Q;
    //cout << "I read: " << N << " : " << S << " : " << P << " : " << Q << endl;
    if (N<1) return -1;
    
    // creating 2^31 bitwise
    elem_t mask = (1u << 31)-1u;
    
    std::unordered_set<elem_t> elems;
    
    a.resize(N);
    a[0] = S;
    elems.insert(a[0]);
    cnt = 1;

    // ---comment this line
    // std::printf("a[%d] = %lu\n", 0, a[0]);
    
    for (int i=1; i<N; i++) {
        a[i] = (a[i-1]*P + Q) & mask;
        auto r = elems.insert(a[i]);

        // ---comment this line
        //std::printf("a[%d] = %lu\n", i, a[i]);

        //if (a[i] == a[i-1]) break;
        if (r.second == false) break;
        cnt++;
    }

    //cout << "there were " << cnt << " different elements" << endl;
    //cout << cnt << endl;
    cout << elems.size() << endl;
    return 0;
}
