#include <bits/stdc++.h>
#include "Package.h"
#include "History.h"
using namespace std;

//BasePackage
bool BasePackage::match(const string &s) const {
    return pid == s || pname == s || description == s || state == s;
}

void BasePackage::print() const {
    cout << pid << "\t" << pname << "\t" << state << "\t" << fee << "\t" << description << endl;
}

istream &operator >> (istream &in, BasePackage &bp) {
    in >> bp.pid >> bp.pname >> bp.state >> bp.fee >> bp.description;
    return in;
}

ostream &operator << (ostream &out, const BasePackage &bp) {
    out << bp.pid << " " << bp.pname << " " << bp.state << " " << bp.fee << " "
        << bp.description << endl;
    return out;
}

//Packet
void Packet::reqSend(const BaseHistory &bh) {
    pacHis.add(bh);
}

void Packet::reqRecv(const BaseHistory &bh) {
    pacHis.add(bh);
}

int Packet::printPacHis() const {
    return pacHis.print();
}

string Packet::printPacHis(const int &idx) const {
    return pacHis.print(idx);
}

istream &operator >> (istream &in, Packet &p) {
    in >> p.pid >> p.pname >> p.state >> p.fee >> p.description;
    in >> p.pacHis;
    return in;
}

ostream &operator << (ostream &out, const Packet &p) {
    out << p.pid << " " << p.pname << " " << p.state << " " << p.fee << " "
        << p.description << endl;
    out << p.pacHis;
    return out;
}

// PackageList
BasePackage &PackageList::operator[](const string &pid) {
    for(int i = 0; i < pl.size(); i++) {
        if(pl[i].getPid() == pid)
            return pl[i];
    }
    return *new BasePackage();
}

BasePackage &PackageList::operator[](const int &num) {
    return pl[num];
}

bool PackageList::pidExist(const string &pid) const {
    for(int i = 0; i < pl.size(); i++) {
        if(pl[i].getPid() == pid)
            return true;
    }
    return false;
}

void PackageList::add(const BasePackage &bp) {
    pl.push_back(bp);
}

void PackageList::del(const BasePackage &bp) {
    for(int i = 0; i < pl.size(); i++) {
        if(pl[i].getPid() == bp.getPid()) {
            pl.erase(pl.begin()+i);
        }
    }
}

void PackageList::del(const string &pid) {
    for(int i = 0; i < pl.size(); i++) {
        if(pl[i].getPid() == pid) {
            pl.erase(pl.begin()+i);
        }
    }
}

int PackageList::print() const {
    cout << "编号\t包裹id\t包裹名\t包裹状态\t寄件费用\t描述" << endl;
    for(int i = 0; i < pl.size(); i++) {
        cout << i+1 << "\t";
        pl[i].print();
    }
    return pl.size();
}

string PackageList::print(const int &idx) const {
    pl[idx].print();
    return pl[idx].getPid();
}

void PackageList::print(const string &pid) const {
    for(int i = 0; i < pl.size(); i++) {
        if(pl[i].getPid() == pid) {
            pl[i].print();
            return;
        }
    }
}

void PackageList::schPacket(const string &s) const {
    cout << "编号\t包裹id\t包裹名\t包裹状态\t寄件费用\t描述" << endl;
    for(int i = 0; i < pl.size(); i++) {
        if(pl[i].match(s)) {
            cout << i+1 << "\t";
            pl[i].print();
        }
    }
}

istream &operator >> (istream &in, PackageList &pl) {
    int num;
    in >> num;
    while(num--) {
        BasePackage bp;
        in >> bp;
        pl.add(bp);
    }
    return in;
}

ostream &operator << (ostream &out, PackageList &pl) {
    out << pl.size() << endl;
    for(int i = 0; i < pl.size(); i++) {
        out << pl[i];
    }
    return out;
}