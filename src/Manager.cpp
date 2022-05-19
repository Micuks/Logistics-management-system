#include <bits/stdc++.h>
#include "History.h"
#include "User.h"
using namespace std;

//Manager
string Manager::getMpasswd() const {
    return mpasswd;
}

istream &operator>>(istream &in, Manager &m) {
    in >> m.uid >> m.uname >> m.mpasswd >> m.wallet;
    cout << m.mpasswd << endl;
    return in;
}

ostream &operator << (ostream &out, const Manager &m) {
    out << m.uid << " " << m.uname << " " << m.mpasswd << " " << m.wallet;
    return out;
}