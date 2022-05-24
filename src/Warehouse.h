#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "Console.h"
#include "History.h"
#include "Package.h"
#include "User.h"
#include <bits/stdc++.h>
using namespace std;

extern Console con;
class Warehouse {
  class Data {
  public:
    PackageList pl;
    UserList ul;
    HistoryList hl;
    HistoryList sendReq;
    HistoryList recvReq;
    Manager m0;
    Data() {
      con.inFile("data/manPasswd", m0);
      con.inFile("data/packageList", pl);
      con.inFile("data/userList", ul);
      con.inFile("data/historyList", hl);
    }
    string getHis() const { return "H" + to_string(5760000000 + hl.size()); }
    string getPkg() const { return "P" + to_string(0000000000 + pl.size()); }
    void chargeMWallet(const int &val) {
      m0.chargeWallet(val);
      con.outFile("data/manPasswd", m0);
    };
    void outPList() const { con.outFile("data/packageList", pl); }
    void outUList() const { con.outFile("data/userList", ul); }
    void outHList() const { con.outFile("data/historyList", hl); }
  } data;

public:
  class Operation {
    Data *data;

  public:
    Operation(Data *_data) : data(_data) {}
    void chargeMWallet(const int &val);
    int printPackage() const;
    int printUser() const;
    int printHistory() const;
    string printPackage(const int &idx) const;
    string printUser(const int &idx) const;
    string printHistory(const int &idx) const;
    void printPackage(const string &pid) const;
    void printUser(const string &uid) const;
    void printHistory(const string &hid) const;
    void schPackage(const string &s) const;
    bool pidExist(const string &pid) const;
    bool uidExist(const string &uid) const;
  } op;
  class ManagerOperation {
    Data *data;
    string mp;
    Manager m;

  public:
    ManagerOperation(Data *_data) : data(_data) { setManager(); }
    void setManager();
    void addUser(const User &u) const;
    void delPackage(const string &pid) const;
    void delUser(const string &uid) const;
    // void agrSend(const string &pid) const;
    int getWallet() const;
    bool mpasswdMatch(const string &s) { return m.mpasswdMatch(s); }
    void changeMPasswd(const string &s);
    void schUser(const string &s) const;
    void schHistory(const string &s) const;
  } mop;

  class UserOperation {
    Data *data;
    string uid, up;
    User u;
    string addHistory(const string &pid, const string &rid,
                      const int &fee) const; // 发送pid包裹并返回hid
  public:
    void initSRHis() const;
    UserOperation(Data *_data) : data(_data) {}
    void setUser(const string &_uid);
    string addPackage(const string &pname,
                      const string &description = "none") const;
    void addPackage(const Package &p) const;
    bool billPackage(const string &pid);
    int getWallet() const;
    void chargeWallet(const int &val);
    string reqSend(const string &pid, const string &rid, const int &fee);
    void finSend(const string &hid);
    void reqRecv(const string &hid);
    void finRecv(const string &hid);
    int printSendHis() const;
    int printRecvHis() const;
    string printSendHis(const int &num) const;
    string printRecvHis(const int &num) const;
    string schSendHis(const string &pid);
    string schRecvHis(const string &pid);
    bool upasswdMatch(const string &s) const { return u.upasswdMatch(s); };
    void changeUpasswd(const string &s);
  } uop;
  Warehouse()
      : op(Operation(&data)), mop(ManagerOperation(&data)),
        uop(UserOperation(&data)) {}
};

#endif
