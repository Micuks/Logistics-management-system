#ifndef PACKAGE_H
#define PACKAGE_H

#include "History.h"
#include <bits/stdc++.h>
using namespace std;

class BasePackage {
  protected:
    string pid, pname, description, state;
    double fee;

  public:
    BasePackage() {}
    BasePackage(string _pid, string _pname, string _state = "待揽收",
                string _description = "无", double _fee = 0.0)
        : pid(_pid), pname(_pname), state(_state), description(_description),
          fee(_fee) {}
    string getPid() const { return pid; }
    string getPname() const { return pname; }
    string getState() const { return state; }
    string getDescription() const { return description; }
    virtual void calcFee();
    virtual double getPrice() const { return fee; }
    bool canSend(double wallet) const { return wallet >= fee; }
    bool canDel() const { return state == "已签收"; }
    bool match(const string &s) const;
    void print() const;
    friend istream &operator>>(istream &in, BasePackage &bp);
    friend ostream &operator<<(ostream &out, const BasePackage &bp);
};

class Package : public BasePackage {
    double quantity, unit_price;

  protected:
    HistoryList pacHis;

  public:
    // using BasePackage::BasePackage;
    Package() : BasePackage() {
        unit_price = 5.0;
        quantity = 0.0;
        pacHis = HistoryList();
    }
    Package(string _pid, string _pname, double _quantity = 0.0,
            string _description = "无", string _state = "待揽收",
            double _unit_price = 5.0, double _fee = 0.0)
        : BasePackage(_pid, _pname, _state, _description, _fee) {
        unit_price = _unit_price;
        quantity = _quantity;
    }
    BasePackage getBase() const {
        return BasePackage(pid, pname, state, description, fee);
    }
    void calcFee() { fee = quantity * unit_price; }
    double getPrice() {
        calcFee();
        return fee;
    }
    double getQuantity() const { return quantity; }
    double getUnitPrice() const { return unit_price; }
    void reqSend(const BaseHistory &bh);
    void finSend(const BaseHistory &bh);
    void reqRecv(const BaseHistory &bh);
    void finRecv(const BaseHistory &bh);
    int printPacHis() const;
    string printPacHis(const int &idx) const;
    friend istream &operator>>(istream &in, Package &p);
    friend ostream &operator<<(ostream &out, const Package &p);
};

class Book : public Package {
    int quantity;
    double unit_price;

  public:
    Book() : Package() {
        quantity = 0;
        unit_price = 2.0;
    }
    Book(string _pid, string _pname, int _quantity = 0,
         string _description = "无", string _state = "待揽收",
         double _unit_price = 5.0, double _fee = 0.0)
        : Package(_pid, _pname, (double)_quantity, _description, _state,
                  _unit_price, _fee) {
        unit_price = _unit_price;
        quantity = _quantity;
    }
    double getPrice() {
        calcFee();
        return fee;
    }
    int getQuantity() const { return quantity; }
};

class Fragile : public Package {
    double quantity, unit_price;

  public:
    Fragile() : Package() {
        quantity = 0.0;
        unit_price = 8.0;
    }
    Fragile(string _pid, string _pname, int _quantity = 0.0,
            string _description = "无", string _state = "待揽收",
            double _unit_price = 5.0, double _fee = 0.0)
        : Package(_pid, _pname, _quantity, _description, _state, _unit_price,
                  _fee) {
        unit_price = _unit_price;
        quantity = _quantity;
    }
};

class PackageList {
    vector<BasePackage> pl;

  public:
    BasePackage &operator[](const string &pid);
    BasePackage &operator[](const int &num);
    int size() const { return pl.size(); }
    bool pidExist(const string &pid) const;
    void add(const BasePackage &bp);
    void del(const BasePackage &bp);
    void del(const string &pid);
    int print() const;
    string print(const int &idx) const;
    void print(const string &pid) const;
    void schPackage(const string &s) const;
    friend istream &operator>>(istream &in, PackageList &pl);
    friend ostream &operator<<(ostream &out, const PackageList &pl);
};

#endif
