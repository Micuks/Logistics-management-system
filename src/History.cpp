#include <bits/stdc++.h>
#include "History.h"
#include "Utils.h"
using namespace std;

//History
bool BaseHistory::match(const string &s) const {
    return hid == s || pid == s || sid == s || rid == s || pname == s ||
        sname == s || rname == s || state == s;
}

void BaseHistory::print() const {
    cout << hid << "\t" << pid << "\t" << pname << "\t" << sid << "\t" <<
        sname << "\t" << stime << "\t" << rid << "\t" << rname << "\t" <<
        rtime << "\t" << state << endl;
}

istream &operator >> (istream &in, BaseHistory &bh) {
    in >> bh.hid >> bh.pid >> bh.sid >> bh.rid >> bh.pname >> bh.sname >>
        bh.rname >> bh.state >> bh.stime >> bh.rtime;
    return in;
}

ostream &operator << (ostream &out, const BaseHistory &bh) {
    out << bh.hid << " " << bh.pid << " " << bh.sid << " " << bh.rid << " "
        << bh.pname << " " << bh.sname << " " << bh.rname << " " << bh.state
        << " " << bh.stime << " " << bh.rtime << " " << endl;
    return out;
}

//History
void History::reqSend() {
    string t = getTime();
    state = "待签收";
    stime = t;
}

void History::reqRecv() {
    string t = getTime();
    state = "已签收";
    rtime = t;
}

istream &operator >> (istream &in, History &bh) {
    in >> bh.hid >> bh.pid >> bh.sid >> bh.rid >> bh.pname >> bh.sname >>
        bh.rname >> bh.state >> bh.stime >> bh.rtime;
    return in;
}

ostream &operator << (ostream &out, const History &bh) {
    out << bh.hid << " " << bh.pid << " " << bh.sid << " " << bh.rid << " "
        << bh.pname << " " << bh.sname << " " << bh.rname << " " << bh.state
        << " " << bh.stime << " " << bh.rtime << " " << endl;
    return out;
}

//HistoryList
BaseHistory &HistoryList::operator [] (const string &hid) {
    for(int i = 0; i < hl.size(); i++) {
        if(hl[i].getHid() == hid)
            return hl[i];
    }
    return *new BaseHistory();
}

BaseHistory &HistoryList::operator[](const int &num) {
    if(num < hl.size())
        return hl[num];
    return *new BaseHistory();
}

void HistoryList::add(const BaseHistory &bh) {
    hl.push_back(bh);
}

void HistoryList::del(const BaseHistory &bh) {
    //del(bh.getHid()); // ***
    for(int i = 0; i < hl.size(); i++) {
        if(hl[i].getHid() == bh.getHid()) {
            hl.erase(hl.begin()+i);
            return;
        }
    }
}

void HistoryList::del(const string &hid) {
    for(int i = 0; i < hl.size(); i++) {
        if(hl[i].getHid() == hid) {
            hl.erase(hl.begin()+i);
            return;
        }
    }
}

int HistoryList::print() const {
    cout << "编号\t历史记录id\t包裹id\t包裹名\t包裹状态\t寄件用户id\t寄件用户姓名\t收件用户id\t收件用户姓名" << endl;
    for(int i = 0; i < hl.size(); i++) {
        cout << i+1 << "\t";
        hl[i].print();
    }
    return hl.size();
}

string HistoryList::print(const int &idx) const {
    hl[idx].print();
    return hl[idx].getHid();
}

void HistoryList::print(const string &hid) const {
    for(int i = 0; i < hl.size(); i++) {
        if(hl[i].getHid() == hid) {
            hl[i].print();
            return;
        }
    }
}

void HistoryList::schHistory(const string &s) const {
    cout << "序号\t历史记录id\t包裹id\t包裹名\t包裹状态\t寄件用户id\t寄件用户姓名\t收件用户id\t收件用户姓名" << endl;
    int cnt = 0;
    for(int i = 0; i < hl.size(); i++) {
        if(hl[i].match(s)) {
            cout << ++cnt << "\t";
            hl[i].print();
        }
    }
}

istream &operator >> (istream &in, HistoryList &hl) {
    int num;
    in >> num;
    while(num--) {
        BaseHistory bh;
        in >> bh;
        hl.add(bh);
    }
    return in;
}

ostream &operator << (ostream &out, HistoryList &hl) {
    out << hl.size() << endl;
    for(int i = 0; i < hl.size(); i++) {
        out << hl[i];
    }
    return out;
}