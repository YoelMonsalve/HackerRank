#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N;
    uint32_t S, P, Q, cnt;
    vector<uint32_t> a;
    
    cin >> N >> S >> P >> Q;
    //cout << "I read: " << N << " : " << S << " : " << P << " : " << Q << endl;
    if (N<1) return -1;
    
    // creating 2^31 bitwise
    uint32_t mask = (1u << 31)-1u;
    
    a.resize(N);
    a[0] = S;
    cnt = 1;

    // ---comment this line
    std::printf("a[%d] = %lu\n", 0, a[0]);
    
    for (int i=1; i<N; i++) {
        a[i] = (a[i-1]*P + Q) & mask;

        // ---comment this line
        std::printf("a[%d] = %lu\n", i, a[i]);

        if (a[i] == a[i-1]) break;
        cnt++;
    }

    //cout << "there were " << cnt << " different elements" << endl;
    cout << cnt << endl;
    return 0;

    // count number of different elements in a
    sort(a.begin(), a.end());

    /** --DEPRECATED-- */   
    uint32_t k=0, elem=a[0];
    #if 0
    while (1) {
        // moves forward the index 'k', while a[k] remains the same as the previous elem
        while (k<N && a[k] == elem) {k++;}
        cnt++;

        if (k<N) { 
            // the next element to be counted
            elem=a[k];
        } else 
            break;
    }
    #endif

    //cout << "there were " << cnt << " different elements" << endl;
    cout << cnt << endl;
    return 0;
}