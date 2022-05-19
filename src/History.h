#ifndef HISTORY_H
#define HISTORY_H

#include <bits/stdc++.h>
using namespace std;

class BaseHistory {
protected:
    string hid, pid, sid, rid, pname, sname, rname, state, stime, rtime;
public:
    BaseHistory() {}
    BaseHistory(string _hid, string _pid, string _sid, string _rid, string _pname,
            string _sname, string _rname, string _state = "none", string _stime = "none",
            string _rtime = "none")
        : hid(_hid), pid(_pid), sid(_sid), rid(_rid), pname(_pname), sname(_sname),
        rname(_rname), state(_state), stime(_stime), rtime(_rtime) {}
    string getHid() const { return hid; }
    string getPid() const { return pid; }
    string getSid() const { return sid; }
    string getRid() const { return rid; }
    string getPname() const { return pname; }
    string getSname() const { return sname; }
    string getRname() const { return rname; }
    string getState() const { return state; }
    string getStime() const { return stime; }
    string getRtime() const { return rtime; }
    bool match(const string &s) const;
    void print() const;
    friend istream &operator>> (istream &in, BaseHistory &bh);
    friend ostream &operator<< (ostream &out, const BaseHistory &bh);
};

class History: public BaseHistory {
public:
    using BaseHistory::BaseHistory;
    BaseHistory getBase() const { return BaseHistory(hid, pid, sid, rid, pname, sname, rname, state, stime, rtime); }
    void reqSend();
    void finSend();
    void reqRecv();
    void finRecv();
    friend istream &operator >> (istream &in, History &h);
    friend ostream &operator << (ostream &out, const History &h);
};

class HistoryList {
    vector <BaseHistory> hl;
public:
    BaseHistory &operator [] (const string &hid);
    BaseHistory &operator [] (const int &num);
    int size() const { return hl.size(); }
    void add(const BaseHistory &bh);
    void del(const BaseHistory &bh);
    void del(const string &hid);
    int print() const; // 将HistoryList的信息打印, 返回其大小
    string print(const int &idx) const; // 将HistoryList[hid]打印, 返回其History
    void print(const string &hid) const;
    void schHistory(const string &s) const;
    string schPkgHis(const string &pid) const;
    friend istream &operator >> (istream &in, HistoryList &hl);
    friend ostream &operator << (ostream &out, const HistoryList &hl);
};

#endif
