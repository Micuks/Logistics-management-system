#include <bits/stdc++.h>
#include "History.h"
#include "User.h"
using namespace std;

//Manager
istream &operator>>(istream &in, Manager &m) {
    in >> m.uid >> m.uname >> m.mpasswd >> m.wallet;
    return in;
}

ostream &operator << (ostream &out, const Manager &m) {
    out << m.uid << " " << m.uname << " " << m.mpasswd << " " << m.wallet;
    return out;
}