#ifndef USER_H
#define USER_H

#include <bits/stdc++.h>
#include "History.h"
using namespace std;

class BaseUser {
protected:
    string uid, uname;
    int wallet;
public:
    BaseUser(){}
    BaseUser(string _uid, string _uname, int _wallet = 0)
        :uid(_uid), uname(_uname), wallet(_wallet){}
    string getUid() const { return uid; }
    string getUname() const { return uname; }
    int getWallet() const { return wallet; }
    bool canDel() const { return wallet == 0; }
    bool match(const string &s) const;
    void print() const;
    friend istream &operator >> (istream &in, BaseUser &bu);
    friend ostream &operator << (ostream &out, const BaseUser &bu);
};

class User: public BaseUser {
    string upasswd;
    HistoryList sendHis;
    HistoryList recvHis;
public:
    User(){}
    User(string _uid, string _uname, string _upasswd, int _wallet)
        :BaseUser(_uid, _uname, _wallet) { upasswd = _upasswd; }
    BaseUser getBase () const { return BaseUser(uid, uname, wallet); }
    bool upasswdMatch(const string &s) const { return upasswd == s; }
    void changeUpasswd(const string &s) { upasswd = s; }
    void reqSend(const BaseHistory &bh);
    void finSend(const BaseHistory &bh);
    void reqRecv(const BaseHistory &bh);
    void finRecv(const BaseHistory &bh);
    string schSendHis(const string &pid);
    string schRecvHis(const string &pid);
    int printSendHis() const;
    int printRecvHis() const; // 打印全部的历史记录, 返回历史记录条数
    string printSendHis(const int &idx) const;
    string printRecvHis(const int &idx) const; // 打印序号idx的历史记录, 返回hid
    friend istream &operator >> (istream &in, User &u);
    friend ostream &operator << (ostream &out, const User &u);
};

class UserList {
    vector <BaseUser> ul;
public:
    BaseUser &operator [] (const string &uid) ;
    BaseUser &operator [] (const int &idx) ;
    int size() const { return ul.size(); }
    bool uidExist(const string &uid) const;
    void add(const BaseUser &bu);
    void del(const BaseUser &bu);
    void del(const string &uid);
    int print() const;
    string print(const int &idx) const;
    void print(const string &uid) const;
    void schUser(const string &s) const;
    friend istream &operator >> (istream &in, UserList &ul);
    friend ostream &operator << (ostream &out, const UserList &ul);
};

class Manager: public BaseUser {
    string mpasswd;
public:
    Manager(){}
    Manager(string _mid, string _mname, string _mpasswd, int _wallet)
        :BaseUser(_mid, _mname, _wallet) { mpasswd = _mpasswd; }
    string getMpasswd() const;
    bool mpasswdMatch(const string &s) { return mpasswd == s; }
    void changeMpasswd(const string &s) { mpasswd = s; }
    friend istream &operator >> (istream &in, Manager &m);
    friend ostream &operator << (ostream &out, const Manager &m);
};

#endif
