#include <bits/stdc++.h>
#include "History.h"
#include "User.h"
using namespace std;

//BaseUser
bool BaseUser::match(const string &s) const {
    return uid == s || uname == s;
}

void BaseUser::print() const {
    cout << uid << "\t" << uname << "\t" << wallet << endl;
}

istream &operator >> (istream &in, BaseUser &bu) {
    in >> bu.uid >> bu.uname >> bu.wallet;
    return in;
}

ostream &operator << (ostream &out, const BaseUser &bu) {
    out << bu.uid << " " << bu.uname << " " << bu.wallet << endl;
    return out;
}

//User
void User::reqSend(const BaseHistory &bh) {
    sendHis.add(bh);
}

void User::finSend(const BaseHistory &bh) {
    sendHis.del(bh.getHid());
    sendHis.add(bh);
}

void User::reqRecv(const BaseHistory &bh) {
    recvHis.add(bh);
}

void User::finRecv(const BaseHistory &bh) {
    recvHis.del(bh.getHid());
    recvHis.add(bh);
}

int User::printSendHis() const {
    return sendHis.print();
}

int User::printRecvHis() const {
    return recvHis.print();
}

istream &operator >> (istream &in, User &u) {
    in >> u.uid >> u.uname >> u.upasswd >> u.wallet;
    return in;
}

ostream &operator << (ostream &out, const User &u) {
    out << u.uid << " " << u.uname << " " << u.upasswd << " " << u.wallet;
    return out;
}

//UserList
BaseUser &UserList::operator [] (const string &uid) {
    for(int i = 0; i < ul.size(); i++) {
        if(ul[i].getUid() == uid)
            return ul[i];
    }
    return *new BaseUser();
}

BaseUser &UserList::operator [] (const int &idx) {
    return ul[idx];
}

bool UserList::uidExist(const string &uid) const {
    for(int i = 0; i < ul.size(); i++) {
        if(ul[i].getUid() == uid)
            return true;
    }
    return false;
}

void UserList::add(const BaseUser &bu) {
    ul.push_back(bu);
}

void UserList::del(const BaseUser &bu) {
    del(bu.getUid()); //***
}

void UserList::del(const string &uid) {
    for(int i = 0; i < ul.size(); i++) {
        if(ul[i].getUid() == uid) {
            ul.erase(ul.begin()+i);
            return;
        }
    }
}

int UserList::print() const {
    cout << "编号\t用户id\t用户名\t余额" << endl;
    for(int i = 0; i < ul.size(); i++) {
        cout << i+1 << "\t";
        ul[i].print();
    }
    return ul.size();
}

string UserList::print(const int &idx) const {
    ul[idx].print();
    return ul[idx].getUid();
}

void UserList::print(const string &uid) const {
    for(int i = 0; i < ul.size(); i++) {
        ul[i].print();
        return;
    }
}

void UserList::schUser(const string &s) const {
    cout << "编号\t用户id\t用户名\t余额" << endl;
    for(int i = 0; i < ul.size(); i++) {
        if(ul[i].match(s)) {
            cout << i+1 << "\t";
            ul[i].print();
        }
    }
}

istream &operator >> (istream &in, UserList &ul) {
    int num;
    in >> num;
    while(num--) {
        BaseUser bu;
        in >> bu;
        ul.add(bu);
    }
    return in;
}

ostream &operator << (ostream &out, const UserList &ul) {
    out << ul.size();
    for(int i = 0; i < ul.size(); i++) {
        out << ul.ul[i];
    }
    return out;
}
