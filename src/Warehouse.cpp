#include <bits/stdc++.h>
#include "History.h"
#include "User.h"
#include "Package.h"
#include "Console.h"
#include "Warehouse.h"
#include "Utils.h"
using namespace std;

//Warehouse::Operation
int Warehouse::Operation::printPackage() const {
    return data->pl.print();
}

int Warehouse::Operation::printUser() const {
    return data->ul.print();
}

int Warehouse::Operation::printHistory() const {
    return data->hl.print();
}

string Warehouse::Operation::printPackage(const int &idx) const {
    return data->pl.print(idx);
}

string Warehouse::Operation::printUser(const int &idx) const {
    return data->ul.print(idx);
}

string Warehouse::Operation::printHistory(const int &idx) const {
    return data->hl.print(idx);
}

void Warehouse::Operation::printPackage(const string &pid) const {
    data->pl.print(pid);
}

void Warehouse::Operation::printUser(const string &uid) const {
    data->ul.print(uid);
}

void Warehouse::Operation::printHistory(const string &hid) const {
    data->hl.print(hid);
}

void Warehouse::Operation::schPackage(const string &s) const {
    data->pl.schPackage(s);
}

bool Warehouse::Operation::pidExist(const string &pid) const {
    return data->pl.pidExist(pid);
}

bool Warehouse::Operation::uidExist(const string &uid) const {
    return data->ul.uidExist(uid);
}

//Warehouse::ManagerOperation
void Warehouse::ManagerOperation::addPackage(const string &pid, const int &num) const {
    
}
