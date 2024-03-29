#include <bits/stdc++.h>
#include "Warehouse.h"
#include "Menu.h"
#include "Utils.h"
using namespace std;

void Menu::ManagerMenu::login() const {
    while(true) {
        system("clear");
        string mpasswd;
        while(true) {
            cout << "请输入密码" << endl
                 << "\t输入-1返回上级菜单" << endl;
            getline(cin, mpasswd);
            if(mpasswd == "-1")
                return;
            if(mop->mpasswdMatch(mpasswd))
                break;
            cout << "用户名或密码错误" << endl;
        }
        start();
    }
}

void Menu::ManagerMenu::start() const {
    while(true) {
        system("clear");
        mop->setManager();
        cout << "当前余额为" << mop->getWallet() << endl;
        cout << "1. 查看所有用户" << endl
             << "2. 查看所有包裹" << endl
             << "3. 查看所有历史记录" << endl
             << "4. 查找用户" << endl
             << "5. 查找包裹" << endl
             << "6. 查找历史记录" << endl
             << "7. 添加用户" << endl
             << "8. 删除用户" << endl
             << "9. 修改密码" << endl
             << "10. 返回上级菜单" << endl
             << "11. 退出系统" << endl;
        string s;
        while(true) {
            getline(cin, s);
            if(isPositive(s) && stoi(s) <= 11)
                break;
            cout << "输入内容错误, 请重新输入" << endl;
        }
        if(s == "1") printUser();
        else if(s == "2") printPackage();
        else if(s == "3") printHistory();
        else if(s == "4") schUser();
        else if(s == "5") schPackage();
        else if(s == "6") schHistory();
        else if(s == "7") addUser();
        else if(s == "8") delUser();
        else if(s == "9") changeMPasswd();
        else if(s == "10") return;
        else exit(0);
    }
}

void Menu::ManagerMenu::printUser() const {
    system("clear");
    op->printUser();
    cout << "输入任意字符返回上级菜单" << endl;
    string s;
    getline(cin, s);
    return;
}

void Menu::ManagerMenu::printPackage() const {
    system("clear");
    op->printPackage();
    cout << "输入任意字符返回上级菜单" << endl;
    string s;
    getline(cin, s);
    return;
}

void Menu::ManagerMenu::printHistory() const {
    system("clear");
    op->printHistory();
    cout << "输入任意字符返回上级菜单" << endl;
    string s;
    getline(cin, s);
    return;
}

void Menu::ManagerMenu::addUser() const {
    while(true) {
        system("clear");
        string uid, uname, upasswd = "123456";
        while(true) {
            cout << "输入读者id(输入-1返回上级菜单)" << endl;
            getline(cin, uid);
            if(uid == "-1") return;
            replace(uid, " ", "_");
            if(!op->uidExist(uid)) break;
            cout << "此uid已被占用" << endl;
        }
        cout << "输入你的名字(输入-1返回上级菜单)" << endl;
        getline(cin, uname);
        if(uname == "-1") return;
        replace(uname, " ", "_");
        mop->addUser(User(uid, uname, upasswd, 0));

        system("clear");
        cout << "用户添加成功, 初始密码为123456" << endl
             << "用户uid为 " << uid << endl
             << "用户名字为 " << uname << endl
             << "1. 继续添加" << endl
             << "2. 返回上级菜单" << endl
             << "3. 退出系统" << endl;
        string s;
        while(true) {
            getline(cin, s);
            if(isPositive(s) && stoi(s) <= 3)
                break;
            cout << "输入内容错误, 清重新输入" << endl;
        }
        if(s == "1") continue;
        else if(s == "2") return;
        else exit(0);
    }
}

void Menu::ManagerMenu::delUser() const {
    while(true) {
        system("clear");
        string uid, hid;
        while(true) {
            cout << "输入待删除用户的uid(输入-1返回上级菜单)" << endl;
            getline(cin, uid);
            if(uid == "-1")
                return;
            else if(!op->uidExist(uid))
                cout << "uid为 " << uid << " 的用户不存在, 请重试" << endl;
            else
                break;
        }
        cout << "待删除的用户信息如下" << endl;
        op->printUser(uid);
        mop->delUser(uid);
        
        system("clear");
        cout << "删除用户 " << uid << " 成功" << endl
             << "1. 删除下一个用户" << endl
             << "2. 返回上级菜单" << endl
             << "3. 退出系统" << endl;
        string s;
        while(true) {
            getline(cin, s);
            if(isPositive(s) && stoi(s) <= 3)
                break;
            cout << "输入内容错误, 请重新输入" << endl;
        }
        if(s == "1") continue;
        if(s == "2") return;
        else exit(0);
    }
}

void Menu::ManagerMenu::schUser() const{
    while(true) {
        system("clear");
        cout << "请输入待搜索用户的关键字" << endl;
        string s;
        getline(cin, s);
        mop->schUser(s);
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

void Menu::ManagerMenu::schHistory() const{
    while(true) {
        system("clear");
        cout << "请输入待搜索历史记录的关键字" << endl;
        string s;
        getline(cin, s);
        mop->schHistory(s);
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

void Menu::ManagerMenu::changeMPasswd() const{
    system("clear");
    string upasswd, r_upasswd;
    while (true) {
        cout << "输入旧密码(输入-1返回上级菜单)" << endl;
        getline(cin, upasswd);
        if (upasswd == "-1")
            return;
        if (mop->mpasswdMatch(upasswd))
            break;
        cout << "密码错误, 请重新输入" << endl;
    }
    cout << "密码正确" << endl;

    while(true) {
        while(true) {
            cout << "输入新密码, 不能包含空格(输入-1返回上级菜单)" << endl;
            getline(cin, upasswd);
            if(upasswd == "-1")
                return;
            if(upasswd.find(" ") == string::npos)
                break;
            cout << "密码中不能包含空格" << endl;
        }
        
        cout << "请再次输入新密码(输入-1返回上级菜单)" << endl;
        getline(cin, r_upasswd);
        if(r_upasswd == "-1")
            return;
        if(r_upasswd == upasswd)
            break;
        cout << "两次输入密码不同" << endl;
    }
    mop->changeMPasswd(upasswd);
    cout << "密码修改成功, 新密码为" << endl
         << upasswd << endl
         << "输入任意字符返回" << endl;   
        string s;
        getline(cin, s);
}