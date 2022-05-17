#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <bits/stdc++.h>
#include "Package.h"
#include "User.h"
#include "History.h"
#include "Console.h"
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
        Data() {
            con.inFile("data/packerList", pl);
            con.inFile("data/userList", ul);
            con.inFile("data/historyList", hl);
            con.inFile("data/sendReq", sendReq);
            con.inFile("data/recvReq", recvReq);
        }
        string getHis() const { return "H"+to_string(5760000000+hl.size()); }
        void outPList() const { con.outFile("data/packetList", pl); }
        void outUList() const { con.outFile("data/userList", ul); }
        void outSReq() const { con.outFile("data/sendReq", sendReq); }
        void outRReq() const { con.outFile("data/recvReq", recvReq); }
    } data;
public:
    class Operation {
        Data *data;
    public:
        Operation(Data *_data):data(_data){}
        int printPacket() const;
        int printUser() const;
        int printHistory() const;
        string printPacket(const int &num) const;
        string printUser(const int &num) const;
        string printHistory(const int &num) const;
        void printPacket(const string &pid) const;
        void printUser(const string &uid) const;
        void printHistory(const string &hid) const;
        void schPacket(const string &s) const;
        bool pidExist(const string &pid) const;
        bool uidExist(const string &uid) const;
    } op;
    class ManagerOperation {
        Data *data;
        Manager m;
    public:
        ManagerOperation(Data *_data):data(_data) {
            // con.inFile("data/managerPasswd", mpasswd);
        }
        // void outMPasswd() const { con.outFile("data/managerPasswd", mpasswd); }
        void addPacket(const string &pid, const int &num) const;
        void addPacket(const Packet &p) const;
        void addUser(const User &u) const;
        bool canDelPkt(const string &pid) const;
        bool canDelUsr(const string &uid) const;
        bool canDelPkt(const int &num) const;
        bool canDelUsr(const int &num) const;
        void delPacket(const string &pid) const;
        void delUser(const string &uid) const;
        void agrSend(const string &pid) const;
        void refSend(const string &pid) const;
        void agrRecv(const string &pid) const;
        void refRecv(const string &pid) const;
        int printSendReq() const;
        int printRecvReq() const;
        string printSendReq(const int &num) const;
        string printRecvReq(const int &num) const;
        bool canSend(const string &pid) const; // pid? hid?
        bool mpasswdMatch(const string &s) { return m.mpasswdMatch(s); }
        void changeMPasswd(const string &s);
        void schUser(const string &s) const;
        void schHistory(const string &s) const;
    } mop;

    class UserOperation {
        Data *data;
        string uid, up;
        User u;
        string addHistory(const string &pid) const; // 发送pid包裹并返回hid
    public:
        UserOperation(Data *_data):data(_data){}
        void setUser(const string &_uid);
        void reqSend(const string &pid);
        void canSend(const string &pid);
        void reqRecv(const string &pid);
        void canRecv(const string &pid);
        int printSendHis() const;
        int printSendReq() const;
        int printRecvHis() const;
        int printRecvReq() const;
        string printSendHis(const int &num) const;
        string printSendReq(const int &num) const;
        string printRecvHis(const int &num) const;
        string printRecvReq(const int &num) const;
        bool upasswdMatch(const string &s) const { return u.upasswdMatch(s); };
        void changeUpasswd(const string &s);
    } uop;
    Warehouse():op(Operation(&data)), mop(ManagerOperation(&data)), uop(UserOperation(&data)){}
};

#endif