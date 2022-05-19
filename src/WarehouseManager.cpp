#include <bits/stdc++.h>
#include "Warehouse.h"
using namespace std;

//WarehouseManager
extern Console con;

void Warehouse::ManagerOperation::setManager() {
    mp = "data/manPasswd";
    con.inFile(mp, m);
}

void Warehouse::ManagerOperation::addUser(const User &u) const {
    string p = con.usrDir(u.getUid());
    con.mkDir(p);
    p+=u.getUid();
    con.outFile(p, u);

    data->ul.add(u.getBase());
    data->outUList();
}

void Warehouse::ManagerOperation::delPackage(const string &pid) const {
    string p = con.pacDir(pid);
    con.rmDir(p);
    data->pl.del(pid);
    data->outPList();
}

void Warehouse::ManagerOperation::delUser(const string &uid) const {
    string p = con.usrDir(uid);
    con.rmDir(p);
    data->ul.del(uid);
    data->outUList();
}

void Warehouse::ManagerOperation::changeMPasswd(const string &s) {
    m.changeMpasswd(s);
    con.outFile(mp, m);
}

void Warehouse::ManagerOperation::schUser(const string &s) const {
    data->ul.schUser(s);
}

void Warehouse::ManagerOperation::schHistory(const string &s) const {
    data->hl.schHistory(s);
}