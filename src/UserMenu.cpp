#include <bits/stdc++.h>
#include "Menu.h"
#include "Warehouse.h"
#include "Utils.h"
using namespace std;

void Menu::UserMenu::login() const {
    while(true) {
        system("clear");
        string uid, upasswd;
        while(true) {
            cout << "请输入用户id" << endl
                << "\t输入-1返回上级菜单" << endl;
            getline(cin, uid);
            if(uid == "-1")
                return;
            if(op->uidExist(uid))
                break;
            cout << uid << " 用户不存在" << endl;
        }
    }
}
