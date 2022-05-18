#ifndef PACKAGE_H
#define PACKAGE_H

#include <bits/stdc++.h>
#include "History.h"
using namespace std;

class BasePackage {
protected:
    string pid, pname, description, state;
    int fee = 15;
public:
    BasePackage(){}
    BasePackage(string _pid, string _pname, string _state, string _description, int _fee)
        :pid(_pid), pname(_pname), state(_state), description(_description), fee(_fee) {};
    string getPid() const { return pid; }
    string getPname() const { return pname; }
    string getState() const { return state; }
    string getDescription() const { return description; }
    int getFee() const { return fee; }
    bool canSend(int wallet) const { return wallet >= fee; }
    bool canDel() const { return state == "signed"; }
    bool match(const string &s) const;
    void print() const;
    friend istream &operator >> (istream &in, BasePackage &bp);
    friend ostream &operator << (ostream &out, const BasePackage &bp);
};

class Packet: public BasePackage {
    HistoryList pacHis;
public:
    // using BasePackage::BasePackage;
    BasePackage getBase() const { return BasePackage(pid, pname, state, description, fee); }
    void reqSend(const BaseHistory &bp);
    void reqRecv(const BaseHistory &bp);
    int printPacHis() const;
    string printPacHis(const int &idx) const;
    friend istream &operator >> (istream &in, Packet &p);
    friend ostream &operator << (ostream &out, const Packet &p);
};

class PackageList {
    vector <BasePackage> pl;
public:
    BasePackage &operator [] (const string &pid);
    BasePackage &operator [] (const int &num);
    int size() const { return pl.size(); }
    bool pidExist(const string &pid) const;
    void add(const BasePackage &bp);
    void del(const BasePackage &bp);
    void del(const string &pid);
    int print() const;
    string print(const int &idx) const;
    void print(const string &pid) const;
    void schPacket(const string &s) const;
    friend istream &operator >> (istream &in, PackageList &pl);
    friend ostream &operator << (ostream &out, PackageList &pl);
};

#endif
