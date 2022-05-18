#ifndef MENU_H
#define MENU_H

#include <bits/stdc++.h>
#include "Warehouse.h"
using namespace std;

//Menu
class Menu {
    Warehouse *wh;
    class SubMenu {
        Warehouse *wh;
    protected:
        Warehouse::Operation *op;
        void printPackage() const;
        void printUser() const;
        void schPackage() const;
    public:
        SubMenu(Warehouse *_wh):wh(_wh), op(&(_wh->op)) {}
    };
    class UserMenu:public SubMenu {
        Warehouse::UserOperation *uop;
    public:
        UserMenu(Warehouse *_wh): SubMenu(_wh) { uop = &(_wh->uop); }
        void login() const;
    private:
        void start() const;
        void sendPackage() const;
        void recvPackage() const;
        void changeUpasswd() const;
    };
    class ManagerMenu:public SubMenu {
        Warehouse::ManagerOperation *mop;
    public:
        ManagerMenu(Warehouse *_wh):SubMenu(_wh) { mop = &(_wh->mop); }
        void login() const;
    private:
        void start() const;
        void addPackage() const;
        void addUser() const;
        void delPackage() const;
        void delUser() const;
        void changeMPasswd() const;
        void schUser() const;
        void schHistory() const;
    };
public:
    UserMenu um;
    ManagerMenu mm;
    Menu(Warehouse *_wh):wh(_wh), um(_wh), mm(_wh) {}
    void start() const;
};

#endif
