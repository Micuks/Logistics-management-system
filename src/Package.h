#ifndef PACKAGE_H
#define PACKAGE_H

#include <bits/stdc++.h>
#include "History.h"
using namespace std;

class BasePackage {
protected:
    string pid, pname, state, stime, rtime, sname, rname, description;
    int fee = 15;
public:
    BasePackage(){}
    BasePackage(string _pid, string _pname, string _state = "无", string _stime = "无", string _rtime = "无", string _sname = "无", string _rname = "无", string _desc = "无")
        :pid(_pid), pname(_pname), state(_state), stime(_stime), rtime(_rtime), sname(_sname), rname(_rname), description(_desc){}
    string getPid(){ return pid; }
    string getPname() { return pname; }
    string getState() { return state; }
    string getStime() { return stime; }
    string getRtime() { return rtime; }
    string getSname() { return sname; }
    string getRname() { return rname; }
    string getDescription() { return description; }
    int getFee() { return fee; }
    bool canSend(int wallet) { return wallet >= fee; }
    bool canDel() { return state == "signed"; }
    bool match(const string &s) const;
    void print() const;
    friend istream &operator >> (istream &in, BasePackage &bp);
    friend ostream &operator << (ostream &out, const BasePackage &bp);
};

class Packet: public BasePackage {
    HistoryList sendReq;
    HistoryList sendHis;
    HistoryList recvReq;
    HistoryList recvHis;
public:
    // using BasePackage::BasePackage;
    BasePackage getBase() const { return BasePackage(pid, pname, state, stime, rtime, sname, rname, description); }
    void reqSend(const BaseHistory &bh);
    void agrSend(const BaseHistory &bh);
    void canSend(const BaseHistory &bh);
    void refSend(const BaseHistory &bh);
    void reqRecv(const BaseHistory &bh);
    void agrRecv(const BaseHistory &bh);
    void canRecv(const BaseHistory &bh);
    void refRecv(const BaseHistory &bh);
    int printSendHis() const;
    int printSendReq() const;
    int printRecvHis() const;
    int printRecvReq() const; // 输出全部历史记录并返回数量
    string showSendHis(const int &idx) const;
    string showSendReq(const int &idx) const;
    string showRecvHis(const int &idx) const;
    string showRecvReq(const int &idx) const; // 输出编号idx的历史记录并返回hid
    friend istream &operator >> (istream &in, Packet &p);
    friend ostream &operator << (ostream &out, const Packet &p);
};

class PackageList {
    vector <BasePackage> bp;
public:
    BasePackage &operator [] (const string &pid);
    BasePackage &operator [] (const int &num);
    int size() const { return bp.size(); }
    bool pidExist(const string &pid) const;
    void add(const BasePackage &bp);
    void del(const BasePackage &bp);
    void del(const string &pid);
    int print() const;
    string print(const int &num) const;
    void print(const string &pid) const;
    void schPacket(const string &s) const;
    friend istream &operator >> (istream &in, PackageList &pl);
    friend ostream &operator << (ostream &out, PackageList &pl);
};

#endif