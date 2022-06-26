#include <bits/stdc++.h>
#include "History.h"
#include "Package.h"
#include "User.h"
#include "Warehouse.h"
#include "Utils.h"
#include "Console.h"
using namespace std;

// Warehouse::UserOperation
extern Console con;
string Warehouse::UserOperation::addHistory(const string &pid,
                                            const string &rid, const int &fee) const {
    string hid = data->getHis();
    History h(hid, pid, uid, rid, data->pl[pid].getPname(), data->ul[uid].getUname(),
              data->ul[rid].getUname());
    string p = con.hisDir(hid);
    con.mkDir(p);
    p += hid;
    con.outFile(p, h);
    data->hl.add(h.getBase());
    data->outHList();
    return hid;
}

string Warehouse::UserOperation::addPackage(const string &pname, const string &description) const {
    string pid = data->getPkg();
    BasePackage bp(pid, pname, "待签收", description);
    string p = con.pacDir(pid);
    con.mkDir(p);
    p+=pid;
    con.outFile(p, bp);
    data->pl.add(bp);
    data->outPList();
    return pid;
}

void Warehouse::UserOperation::setUser(const string &_uid) {
    uid = _uid;
    u.initSRHis();
    up = con.usrDir(uid)+uid;
    con.inFile(up, u);
}

bool Warehouse::UserOperation::billPackage(const string &pid) {
    BasePackage bp = data->pl[pid];
    return u.billPackage(bp.getFee());
}

void Warehouse::UserOperation::addPackage(const Package &pkg) const {
    string p = con.pacDir(pkg.getPid());
    con.mkDir(p);
    p+=pkg.getPid();
    con.outFile(p, pkg);
    data->pl.add(pkg.getBase());
    data->outPList();
}

int Warehouse::UserOperation::getWallet() const {
    return u.getWallet();
}

void Warehouse::UserOperation::chargeWallet(const int &val) {
    u.chargeWallet(val);
    con.outFile(up, u);
}

string Warehouse::UserOperation::reqSend(const string &pid, const string &rid,
                                       const int &fee) {
    // 新建包裹历史记录
    string hid = addHistory(pid, rid, fee);
    BaseHistory bh = data->hl[hid];
    
    // 读取包裹
    string pp = con.pacDir(pid)+pid;
    Package p;
    con.inFile(pp, p);

    // 读取历史记录
    string hp = con.hisDir(hid)+hid;
    History h;
    con.inFile(hp, h);

    // 写入发送历史记录
    h.reqSend();
    con.outFile(hp, h);
    bh = h.getBase();

    // 写入包裹发送记录
    p.reqSend(bh);
    con.outFile(pp, p);

    // 写入发送方历史记录
    u.reqSend(bh);
    con.outFile(up, u);
    
    // 更新历史记录列表
    data->hl.del(hid);
    data->hl.add(bh);
    data->outHList();

    // 更新包裹列表
    data->pl.del(pid);
    data->pl.add(p.getBase());
    data->outPList();
    
    // 更新用户列表
    data->ul.del(uid);
    data->ul.add(u.getBase());
    data->outUList();

    return hid;
}

void Warehouse::UserOperation::reqRecv(const string &hid) {
    // 获取BaseHistory
    BaseHistory bh = data->hl[hid];

    string pid = bh.getPid();
    string rid = bh.getRid();

    string pp = con.pacDir(pid)+pid;
    Package p;
    con.inFile(pp, p);

    string hp = con.hisDir(hid)+hid;
    History h;
    con.inFile(hp, h);

    string rp = con.usrDir(rid)+rid;
    User r;
    con.inFile(rp, r);

    h.reqRecv();
    con.outFile(hp, h);
    bh = h.getBase();

    p.reqRecv(bh);
    con.outFile(pp, p);

    r.reqRecv(bh);
    con.outFile(rp, r);
    
    data->hl.del(hid);
    data->hl.add(bh);
    data->outHList();

    data->ul.del(rid);
    data->ul.add(r.getBase());
    data->outUList();
}

void Warehouse::UserOperation::finSend(const string &hid) {
    BaseHistory bh = data->hl[hid];
    string pid = bh.getPid();
    string sid = bh.getSid();
    
    string pp = con.pacDir(pid)+pid;
    Package p;
    con.inFile(pp, p);

    string hp = con.hisDir(hid)+hid;
    History h;
    con.inFile(hp, h);
    
    string sp = con.usrDir(sid)+sid;
    User s;
    con.inFile(sp, s);

    h.finSend();
    con.outFile(hp, h);
    bh = h.getBase();

    p.finSend(bh);
    con.outFile(pp, p);

    s.finSend(bh);
    con.outFile(sp, s);

    data->hl.del(hid);
    data->hl.add(h.getBase());
    data->outHList();
    
    data->pl.del(pid);
    data->pl.add(p.getBase());
    data->outPList();

    data->ul.del(sid);
    data->ul.add(s.getBase());
    data->outUList();
}

void Warehouse::UserOperation::finRecv(const string &hid) {
    BaseHistory bh = data->hl[hid];
    string pid = bh.getPid();
    
    string pp = con.pacDir(pid)+pid;
    Package p;
    con.inFile(pp, p);
    
    string hp = con.hisDir(hid)+hid;
    History h;
    con.inFile(hp, h);

    h.finRecv();
    con.outFile(hp, h);
    bh = h.getBase();
    
    p.finRecv(bh);
    con.outFile(pp, p);
    
    u.finRecv(bh);
    con.outFile(up, u);

    data->hl.del(hid);
    data->hl.add(h.getBase());
    data->outHList();

    data->pl.del(pid);
    data->pl.add(p.getBase());
    data->outPList();

    data->ul.del(uid);
    data->ul.add(u.getBase());
    data->outUList();
}

string Warehouse::UserOperation::schSendHis(const string &pid) {
    return u.schSendHis(pid);
}

string Warehouse::UserOperation::schRecvHis(const string &pid) {
    return u.schRecvHis(pid);
}

int Warehouse::UserOperation::printSendHis() const {
    return u.printSendHis();
}

int Warehouse::UserOperation::printRecvHis() const {
    return u.printRecvHis();
}

string Warehouse::UserOperation::printSendHis(const int &idx) const {
    return u.printSendHis(idx);
}

string Warehouse::UserOperation::printRecvHis(const int &idx) const {
    return u.printRecvHis(idx);

}

void Warehouse::UserOperation::changeUpasswd(const string &s) {
    u.changeUpasswd(s);
    con.outFile(up, u);
}