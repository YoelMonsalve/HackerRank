#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// this declares a type for the adjacency matrix
typedef vector<vector<int> > Matrix2D;
typedef vector<int> row;
// coordinates
typedef vector<int> point;
typedef vector<point> positions;

ostream& operator<<(ostream &o, point p) {
    return o << '(' << p[0] << ',' << p[1] << ')';
}

/**
 * Computes the squared distance from point p1 to p2
 */
inline long sqDistance(point p1, point p2) {
    int dx = p1[0] - p2[0],
        dy = p1[1] - p2[1];
    return dx*dx + dy*dy;
}

/**
 * Computes the adjacency matrix of `N` bikers, respect to `M` bikes.
 * The result is a `NxM` matrix A such that:
 *   A[i][j] = squared distance from i-th biker to j-th bike
 * 
 * @param  bikers  vector of points, representing the coordinates of bikers.
 * @param  bikes   vector of points, representing the coordinates of available bikes.
*/
void computeDistances(positions &bikers, positions &bikes, Matrix2D &A) {
    int N = bikers.size();
    int M = bikes.size();
    int i, j;
    if (!N || !M) return;
    A.resize(N);
    for (i=0; i<N; i++) {
        A[i].resize(M);
        for (j=0; j<M; j++) {
            A[i][j] = sqDistance(bikers[i], bikes[j]);
        }
    }

    // print matrix
#ifdef DEBUG
    cout << '\n';
    for_each(A.begin(), A.end(), [](const row &r) {
        for_each(r.begin(), r.end(), [](const int &a) { cout << "  " << a;});
        cout << endl;
    });  
#endif
}

/**
 * Returns the squared-distance of the nearest biker to a bike
 * (the biker whose trajectory to a possible bike is the less
 * among those possible of the other bikers)
 */
long minSqDistance(positions &bikers, positions &bikes, int &i_biker, int &i_bike) {
    Matrix2D A;
    
    i_biker = i_biker = -1;
    long d2 = std::numeric_limits<long>::max();

    if (bikers.empty() || bikes.empty()) { return d2; }

    computeDistances(bikers, bikes, A);
    int i = 0;
    for_each(A.begin(), A.end(), [&d2, &i_biker, &i, &i_bike](const row &r) -> void {
        // look at the nearest bike for this biker
        auto it = min_element(r.begin(), r.end());
        long this_d2 = *it;

        //cout << "minimum sq-distance is: " << this_d2 << ", to bike: " << (it - r.begin()) << '\n';
        if (d2 > this_d2) { 
            cout << "..choose: " << this_d2 << '\n';
            d2 = this_d2;
            i_biker = i;                // fastest biker so far
            i_bike = it - r.begin();    // nearest bike to fastest biker
        } 
        ++i;
    });

    return d2;
}   

/*
 * Complete the 'bikeRacers' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY bikers
 *  2. 2D_INTEGER_ARRAY bikes
 * 
 * STOP, after the first k bikers have reached a bike.
 */
long bikeRacers(vector<vector<int>> bikers, vector<vector<int>> bikes, int k) {

    int i_fastest_biker, i_nearest_bike;
    long D2_slowest = 0;
    while (k-- && bikers.size() && bikes.size()) {
        
        long d2 = minSqDistance(bikers, bikes, i_fastest_biker, i_nearest_bike);
        if (d2 > D2_slowest) D2_slowest = d2;
        
        point fastest_biker = bikers[i_fastest_biker];
        point nearest_bike  = bikes[i_nearest_bike];
        
        cout << '\n';
        cout << "Best biker: " << fastest_biker << ", to bike: " << nearest_bike << '\n';

        // remove fastest biker and nearest bike from the sequence, and start again
        // until completing the first k bikers
        bikers.erase(bikers.begin() + i_fastest_biker);
        bikes.erase(bikes.begin() + i_nearest_bike);
    }

    return D2_slowest;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    int k = stoi(first_multiple_input[2]);

    vector<vector<int>> bikers(n);

    for (int i = 0; i < n; i++) {
        bikers[i].resize(2);

        string bikers_row_temp_temp;
        getline(cin, bikers_row_temp_temp);

        vector<string> bikers_row_temp = split(rtrim(bikers_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int bikers_row_item = stoi(bikers_row_temp[j]);

            bikers[i][j] = bikers_row_item;
        }
    }

    vector<vector<int>> bikes(n);

    for (int i = 0; i < n; i++) {
        bikes[i].resize(2);

        string bikes_row_temp_temp;
        getline(cin, bikes_row_temp_temp);

        vector<string> bikes_row_temp = split(rtrim(bikes_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int bikes_row_item = stoi(bikes_row_temp[j]);

            bikes[i][j] = bikes_row_item;
        }
    }

    long result = bikeRacers(bikers, bikes, k);

    fout << result << "\n";
    cout << "result: " << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
