#include "History.h"
#include "User.h"
#include <bits/stdc++.h>
using namespace std;

// Courier
void Courier::reqColl(const BaseHistory &bh) { collectHis.add(bh); }

void Courier::finColl(const BaseHistory &bh) {
    collectHis.del(bh.getHid());
    collectHis.add(bh);
}

void Courier::reqDist(const BaseHistory &bh) { distribHis.add(bh); }

void Courier::finDist(const BaseHistory &bh) {
    distribHis.del(bh.getHid());
    distribHis.add(bh);
}

string Courier::schCollHis(const string &pid) {
    return collectHis.schPkgHis(pid);
}

string Courier::schDistHis(const string &pid) {
    return distribHis.schPkgHis(pid);
}

int Courier::printCollHis() const { return collectHis.print(); }

int Courier::printDistHis() const { return distribHis.print(); }

string Courier::printCollHis(const int &idx) const {
    return collectHis.print(idx);
}

string Courier::printDistHis(const int &idx) const {
    return distribHis.print(idx);
}

istream &operator>>(istream &in, Courier &c) {
    in >> c.uid >> c.uname >> c.cpasswd >> c.wallet >> c.collectHis >>
        c.distribHis;
    return in;
}

ostream &operator<<(ostream &out, const Courier &c) {
    out << c.uid << " " << c.uname << " " << c.cpasswd << " " << c.wallet
        << endl
        << c.collectHis << c.distribHis << endl;
    return out;
}

// CourierList
BaseUser &CourierList::operator[](const string &cid) {
    for (int i = 0; i < cl.size(); i++) {
        if (cl[i].getUid() == cid)
            return cl[i];
    }
    return *new BaseUser();
}

BaseUser &CourierList::operator[](const int &idx) { return cl[idx]; }

bool CourierList::cidExist(const string &cid) const {
    for (int i = 0; i < cl.size(); i++) {
        if (cl[i].getUid() == cid)
            return true;
    }
    return false;
}

void CourierList::add(const BaseUser &bu) { cl.push_back(bu); }

void CourierList::del(const BaseUser &bu) { del(bu.getUid()); }

void CourierList::del(const string &cid) {
    for (int i = 0; i < cl.size(); i++) {
        if (cl[i].getUid() == cid) {
            cl.erase(cl.begin() + i);
            return;
        }
    }
}

string CourierList::print(const int &idx) const {
    cl[idx].print();
    return cl[idx].getUid();
}

void CourierList::print(const string &cid) const {
    for (int i = 0; i < cl.size(); i++) {
        if (cl[i].getUid() == cid) {
            cl[i].print();
            return;
        }
    }
}

void CourierList::schCourier(const string &s) const {
    cout << "编号\t快递员id\t快递员名\t" << endl;
    for (int i = 0; i < cl.size(); i++) {
        if (cl[i].match(s)) {
            cout << i + 1 << "\t";
            cl[i].print();
        }
    }
}
