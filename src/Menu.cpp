#include <bits/stdc++.h>
#include "Menu.h"
#include "Warehouse.h"
#include "Utils.h"
using namespace std;

//SubMenu
void Menu::SubMenu::printPackage() const {
    system("clear");
    op->printPackage();
    cout << "输入任意字符返回上级菜单" << endl;
    string s;
    getline(cin, s);
    return;
}

void Menu::SubMenu::printUser() const {
    system("clear");
    op->printUser();
    cout << "输入任意字符返回上级菜单" << endl;
    string s;
    getline(cin, s);
    return;
}

void Menu::SubMenu::schPackage() const {
    while(true) {
        system("clear");
        cout << "请输入待搜索包裹的关键字" << endl;
        string s;
        getline(cin, s);
        op->schPackage(s);
        cout << "1. 继续搜索" << endl
            << "2. 返回上级菜单" << endl
            << "3. 退出系统" << endl;
        string k;
        while(true) {
            getline(cin, k);
            if(isPositive(k) && stoi(k) <= 3)
                break;
            cout << "输入内容错误, 请重新输入" << endl;
        }
        if(k == "1")
            continue;
        if(k == "2")
            return;
        if(k == "3")
            exit(0);
        cout << "?\n";
    }
}

//Menu
void Menu::start() const {
    while(true) {
        system("clear");
        cout << "物流管理平台" << endl
            << "1. 用户入口" << endl
            << "2. 管理员入口" << endl
            << "3. 退出" << endl;
        string s;
        while(true) {
            getline(cin, s);
            if(isPositive(s) && stoi(s) <= 3)
                break;
            cout << "输入内容错误, 请重新输入" << endl;
        }
        if(s == "1")
            um.login();
        if(s == "2")
            mm.login();
        if(s == "3")
            exit(0);
        cout << "?\n";
    }
}
