#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

// Warehouse::CourierOperation
void Warehouse::CourierOperation::initColHis() { c.initColHis(); }
void Warehouse::CourierOperation::setCourier(const string _cid) {
    cid = _cid;
    string cp = con.couDir(cid) + cid;
    con.inFile(cp, c);
}
void Warehouse::CourierOperation::chargeWallet(const double &val) {
    c.chargeWallet(val);
    con.outFile(cp, c);
}
void Warehouse::CourierOperation::finColl(const string &hid) {
    BaseHistory bh = data->hl[hid];
    Courier c;
    con.inFile(cp, c);

    string pid = bh.getPid();
    string pp = con.pacDir(pid) + pid;
    Package p;
    con.inFile(pp, p);

    string hp = con.hisDir(hid) + hid;
    History h;
    con.inFile(hp, h);

    h.finColl();
    con.outFile(hp, h);
    bh = h.getBase();

    p.finColl(bh);
    con.outFile(pp, p);

    c.finColl(bh);
    con.outFile(cp, c);

    data->hl.del(hid);
    data->hl.add(bh);
    data->outHList();

    data->pl.del(p);
    data->pl.add(p.getBase());
    data->outPList();

    data->cl.del(c);
    data->cl.add(c.getBase());
    data->outCList();
}
int Warehouse::CourierOperation::printCollHis() const {
    return c.printCollHis();
}
string Warehouse::CourierOperation::printCollHis(const int &idx) const {
    return c.printCollHis(idx);
}
void Warehouse::CourierOperation::changeCpasswd(const string &s) {
    c.changeCpasswd(s);
}
