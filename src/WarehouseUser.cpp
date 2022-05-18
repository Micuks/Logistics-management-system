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

void Warehouse::UserOperation::setUser(const string &_uid) {
    uid = _uid;
    up = con.usrDir(uid)+uid;
    con.inFile(up, u);
}

void Warehouse::UserOperation::reqSend(const string &pid, const string &rid,
                                       const int &fee) {
    string hid = addHistory(pid, rid, fee);
    BaseHistory bh = data->hl[hid];
    string pp = con.pacDir(pid)+pid;
    Package p;
    con.inFile(pp, p);
    string hp = con.hisDir(hid)+hid;
    History h;
    con.inFile(hp, h);
    h.reqSend();
    con.outFile(hp, h);
    bh = h.getBase();
    p.reqSend(bh);
    con.outFile(pp, p);
    u.reqSend(bh);
    con.outFile(up, u);
    string rp = con.usrDir(rid)+rid;
    User r;
    con.inFile(rp, r);
    r.reqSend(bh);
    con.outFile(rp, r);
    data->hl.del(hid);
    data->hl.add(bh);
    data->outHList();
    
    data->pl.add(p.getBase());
    data->outPList();
}