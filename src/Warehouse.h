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
        CourierList cl;
        HistoryList hl;
        HistoryList sendReq;
        HistoryList recvReq;
        HistoryList collectHis;
        HistoryList distribHis;
        Manager m0;
        Data() {
            con.inFile("data/manPasswd", m0);
            con.inFile("data/packageList", pl);
            con.inFile("data/userList", ul);
            con.inFile("data/courierList", cl);
            con.inFile("data/historyList", hl);
        }
        string getHis() const {
            return "H" + to_string(5760000000 + hl.size());
        }
        string getPkg() const {
            return "P" + to_string(0000000000 + pl.size());
        }
        void chargeMWallet(const int &val) {
            m0.chargeWallet(val);
            con.outFile("data/manPasswd", m0);
        };
        void outPList() const { con.outFile("data/packageList", pl); }
        void outUList() const { con.outFile("data/userList", ul); }
        void outCList() const { con.outFile("data/courierList", cl); }
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
        int printCourier() const;
        int printHistory() const;
        string printPackage(const int &idx) const;
        string printUser(const int &idx) const;
        string printCourier(const int &idx) const;
        string printHistory(const int &idx) const;
        void printPackage(const string &pid) const;
        void printUser(const string &uid) const;
        void printCourier(const string &uid) const;
        void printHistory(const string &hid) const;
        void schPackage(const string &s) const;
        bool pidExist(const string &pid) const;
        bool CidExist(const string &cid) const;
        bool uidExist(const string &uid) const;
    } op;
    class ManagerOperation {
        Data *data;
        string mp;
        Manager m;

      public:
        ManagerOperation(Data *_data) : data(_data) { setManager(); }
        void setManager();
        int getWallet() const;
        bool mpasswdMatch(const string &s) { return m.mpasswdMatch(s); }
        void changeMPasswd(const string &s);

        void addUser(const User &u) const;
        void addCourier(const Courier &c) const;
        void delPackage(const string &pid) const;
        void delUser(const string &uid) const;
        void delCourier(const string &cid) const;

        void schUser(const string &s) const;
        void schCourier(const string &s) const;
        void schHistory(const string &s) const;

        void reqColl(const string &hid, const string &cid) const;
    } mop;

    class UserOperation {
        Data *data;
        string uid, up;
        User u;
        string addHistory(const string &pid, const string &rid,
                          const int &fee) const; // 发送pid包裹并返回hid
      public:
        void initSRHis();
        UserOperation(Data *_data) : data(_data) {}
        void setUser(const string &_uid);
        string addPackage(const string &pname,
                          const string &description = "none") const;
        void addPackage(const Package &p) const;
        bool billPackage(const string &pid);
        int getWallet() const;
        void chargeWallet(const double &val);
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
    class CourierOperation {
        Data *data;
        string cid, cp;
        Courier c;

      public:
        void initColHis();
        CourierOperation(Data *_data) : data(_data){};
        void setCourier(const string _cid);
        void chargeWallet(const double &val);
        void finColl(const string &hid);
        int printCollHis() const;
        string printCollHis(const int &idx) const;
        string schCollHis(const string &pid) const;
        bool cpasswdMatch(const string &s) const { return c.cpasswdMatch(s); }
        void changeCpasswd(const string &s);
    } cop;
    Warehouse()
        : op(Operation(&data)), mop(ManagerOperation(&data)),
          cop(CourierOperation(&data)), uop(UserOperation(&data)) {}
};

#endif
