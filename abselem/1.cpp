#include <bits/stdc++.h>
#include <algorithm>
#include <execution>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

typedef uint64_t result_t;

/* This structure stores info about each element in dara `arr`.
 * There exist, as much, 4001 different values as
 *   -2000 <= arr[i] <= 2000
 */
struct point
{
	int value;
	int freq;
};
typedef struct point point_t;

/* Calculates the result of query `q` applied over array sample */
result_t calculateQueryResult(vector<point_t> &sample, const int &q)
{
    result_t abs_sum = 0;
    
    /*for (vector<point_t>::size_type i = 0; i < sample.size(); i++) {
	    abs_sum += sample[i].freq * abs(sample[i].value += q);
    };*/
    for (auto it = sample.begin(); it != sample.end(); it++) {
	    abs_sum += it->freq * abs(it->value += q);
    };
    return abs_sum;
}

/** This maps a value into an index of the array of samples */
//inline size_t map(int value) { return 2000 + value; }
#define map(value) (2000 + (value))

/* This builds the sample from array `arr`: values and number 
 * of occurrences for each
 */  
void characterizeSample(vector<int> &arr, vector<point_t> &sample) 
{	
	size_t j;
	
	// nullify frequencies at the beginning
	for (auto &s: sample) {
		s.freq = 0;
	}
	// compute frequencies
	for (auto &a: arr) {
		j = map(a);
		sample[j].value = a;
		++sample[j].freq;
	}
	/*for (j = 0; j < sample.size(); j++) {
		if (sample[j].freq) {
			printf("%d: %d\n", sample[j].value, sample[j].freq);
		}
	}*/
}

/*
 * Complete the 'playingWithNumbers' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY arr
 *  2. INTEGER_ARRAY queries
 */
vector<result_t> playingWithNumbers(vector<int> &arr, const vector<int> &queries) {

    // result is initially populated with zeros
    vector<result_t> result = vector<result_t>(queries.size(), 0);
    if (!arr.size() || !queries.size()) return result;

    // initial sum of the array
    result_t r = 0;

	int sample_len = 4001;
	vector<point_t> sample(sample_len);
	characterizeSample(arr, sample);
	
    for (vector<result_t>::size_type j = 0; j < queries.size(); j++) {
        result[j] = calculateQueryResult(sample, queries[j]);
    }
    return std::move(result);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    string queries_temp_temp;
    getline(cin, queries_temp_temp);

    vector<string> queries_temp = split(rtrim(queries_temp_temp));

    vector<int> queries(q);

    for (int i = 0; i < q; i++) {
        int queries_item = stoi(queries_temp[i]);

        queries[i] = queries_item;
    }

	//sort(queries.begin(), queries.end());
    vector<result_t> result = playingWithNumbers(arr, queries);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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
