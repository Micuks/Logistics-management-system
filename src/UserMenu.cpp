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
        uop->setUser(uid);
        while(true) {
            cout << "请输入密码" << endl
                 << "\t输入-1返回上级菜单" << endl;
            getline(cin, upasswd);
            if(upasswd == "-1")
                return;
            if(uop->upasswdMatch(upasswd))
                break;
            cout << "用户名或密码错误" << endl;
        }
        start();
    }
}

void Menu::UserMenu::start() const {
    while(true) {
        system("clear");
        cout << "1. 发快递" << endl
             << "2. 收快递" << endl
             << "3. 搜索快递" << endl
             << "4. 打印所有已发快递" << endl
             << "5. 打印所有签收和待签收快递" << endl
             << "6. 更改密码" << endl
             << "7. 返回上级菜单" << endl
             << "8. 退出系统" << endl;
            string s;
            while(true) {
                getline(cin, s);
                if(isPositive(s) && stoi(s) <= 8)
                    break;
                cout << "输入内容错误, 请重新输入" << endl;
            }
            if(s == "1")
                sendPackage();
            else if(s == "2")
                recvPackage();
            else if(s == "3")
                schPackage();
            else if(s == "4")
                printSendHis();
            else if(s == "5")
                printRecvHis();
            else if(s == "6")
                changeUpasswd();
            else if(s == "7")
                return;
            else if(s == "8")
                exit(0);
    }
}

void Menu::UserMenu::sendPackage() const {
    while(true) {
        system("clear");
        string pid, pname, rid, rname, description;

        cout << "输入包裹名称(输入-1返回上级菜单)" << endl;
        getline(cin, pname);
        if (pname == "-1")
            return;
        replace(pname, " ", "_");

        cout << "输入包裹描述(输入0为无描述, 输入-1返回上级菜单)" << endl;
        getline(cin, description);
        if(description == "0")
            description = "无";
        if(description == "-1")
            return;
            replace(description, " ", "_");
        pid = uop->addPackage(pname, description);
        
        while(true) {
            cout << "输入输入收件人uid(输入-1返回上级菜单)" << endl;
            getline(cin, rid);
            if(rid == "-1")
                return;
            if(op->uidExist(rid))
                break;
            cout << "输入错误, id为 " << rid << " 的收件人不存在" << endl; 
        }
        
        cout << "收件人信息如下" << endl;
        op->printUser(rid);
        string hid = uop->reqSend(pid, rid, 15);
        uop->reqRecv(hid);
        
        cout << "包裹发送完毕" << endl
             << "1. 发送下一个包裹" << endl
             << "2. 返回上级菜单" << endl
             << "3. 退出系统" << endl;
        string s;
        while(true) {
            getline(cin, s);
            if(isPositive(s) && stoi(s) <= 3)
                break;
            cout << "输入内容错误, 请重新输入" << endl;
        }
        if(s == "1")
            continue;
        else if(s == "2")
            return;
        else if(s == "3")
            exit(0);
    }
}

void Menu::UserMenu::recvPackage() const {
    while(true) {
        system("clear");
        string pid, hid;
        while(true) {
            cout << "输入待签收包裹的pid(输入-1返回上级菜单)" << endl;
            getline(cin, pid);
            if(pid == "-1")
                return;
            else if(pid[0] != 'P')
                cout << "包裹pid格式错误, 请重新输入" << endl;
            else if((hid = uop->schRecvHis(pid)) == "-1")
                cout << "pid为 " << pid << " 的包裹不存在, 请重试" << endl;
            else
                break;
        }
        cout << "签收的包裹信息如下" << endl;
        op->printPackage(pid);
        uop->finRecv(hid);
        uop->finSend(hid);
        
        cout << "包裹签收成功" << endl
             << "1. 签收下一个包裹" << endl
             << "2. 返回上级菜单" << endl
             << "3. 退出系统" << endl;
        string s;
        while(true) {
            getline(cin, s);
            if(isPositive(s) && stoi(s) <= 3)
                break;
            cout << "输入内容错误, 请重新输入" << endl;
        }
        if(s == "1")
            continue;
        else if(s == "2")
            return;
        else if(s == "3")
            exit(0);
    }
}

void Menu::UserMenu::changeUpasswd() const {
    system("clear");
    string upasswd, r_upasswd;
    while (true) {
        cout << "输入旧密码(输入-1返回上级菜单)" << endl;
        getline(cin, upasswd);
        if (upasswd == "-1")
            return;
        if (uop->upasswdMatch(upasswd))
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
    uop->changeUpasswd(upasswd);
    cout << "密码修改成功, 新密码为" << endl
         << upasswd << endl
         << "输入任意字符返回" << endl;   
        string s;
        getline(cin, s);
}