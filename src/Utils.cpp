#include <bits/stdc++.h>
#include "Utils.h"
using namespace std;

bool isPositive(const string &s) {
    for(int i = 0; i < s.length(); i++) {
        if(s[i] < '0' || s[i] > '9')
            return false;
        if(stoi(s) == 0)
            return false;
    }
    return true;
}

void replace(string &s, const string &a, const string &b) {
    string::size_type pos = s.find(a);
    while(pos != string::npos) {
        s.replace(pos, 1, b);
        pos = s.find(a);
    }
}

string getTime() {
    time_t t;
    time(&t);
    string st = ctime(&t);
    st.pop_back();
    replace(st, " ", "_");
    return st;
}
