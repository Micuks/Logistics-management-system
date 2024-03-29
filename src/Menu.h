#ifndef MENU_H
#define MENU_H

#include <bits/stdc++.h>
#include "Warehouse.h"
using namespace std;

//Menu
class Menu {
    // 仓库类, 封装全部数据和操作
    Warehouse *wh;
    /**
     * @brief 子菜单, 菜单基类
     * 
     */
    class SubMenu {
        // 仓库类, 封装全部数据和操作
        Warehouse *wh;
    protected:
        // 公操作
        Warehouse::Operation *op;
        /**
         * @brief 搜索包裹
         * 
         */
        void schPackage() const;
    public:
        /**
         * @brief Construct a new Sub Menu object
         * 
         * @param _wh 
         */
        SubMenu(Warehouse *_wh):wh(_wh), op(&(_wh->op)) {}
    };
    /**
     * @brief 用户菜单类
     * 
     */
    class UserMenu:public SubMenu {
        // 用户操作类
        Warehouse::UserOperation *uop;
    public:
        /**
         * @brief Construct a new User Menu object
         * 
         * @param _wh 
         */
        UserMenu(Warehouse *_wh): SubMenu(_wh) { uop = &(_wh->uop); }
        /**
         * @brief 用户登录
         * 
         */
        void login() const;
    private:
        /**
         * @brief 用户开始界面
         * 
         */
        void start() const;
        /**
         * @brief 打印发送历史记录
         * 
         */
        void printSendHis() const;
        /**
         * @brief 打印签收记录
         * 
         */
        void printRecvHis() const;
        /**
         * @brief 发送包裹
         * 
         */
        void sendPackage() const;
        /**
         * @brief 签收包裹
         * 
         */
        void recvPackage() const;
        /**
         * @brief 充值钱包
         * 
         */
        void chargeWallet() const;
        /**
         * @brief 修改密码
         * 
         */
        void changeUpasswd() const;
    };
    /**
     * @brief 管理员菜单类
     * 
     */
    class ManagerMenu:public SubMenu {
        // 管理员操作类
        Warehouse::ManagerOperation *mop;
    public:
        /**
         * @brief Construct a new Manager Menu object
         * 
         * @param _wh 
         */
        ManagerMenu(Warehouse *_wh):SubMenu(_wh) { mop = &(_wh->mop); }
        /**
         * @brief 管理员登录
         * 
         */
        void login() const;
    private:
        /**
         * @brief 管理员初始界面
         * 
         */
        void start() const;
        /**
         * @brief 打印所有包裹
         * 
         */
        void printPackage() const;
        /**
         * @brief 打印所有用户
         * 
         */
        void printUser() const;
        /**
         * @brief 打印所有历史记录
         * 
         */
        void printHistory() const;
        /**
         * @brief 新建用户
         * 
         */
        void addUser() const;
        /**
         * @brief 删除用户
         * 
         */
        void delUser() const;
        /**
         * @brief 更改密码
         * 
         */
        void changeMPasswd() const;
        /**
         * @brief 搜索用户
         * 
         */
        void schUser() const;
        /**
         * @brief 搜索历史记录
         * 
         */
        void schHistory() const;
    };
public:
    // 用户菜单
    UserMenu um;
    // 管理员菜单
    ManagerMenu mm;
    /**
     * @brief Construct a new Menu object
     * 
     * @param _wh 
     */
    Menu(Warehouse *_wh):wh(_wh), um(_wh), mm(_wh) {}
    /**
     * @brief 初始界面
     * 
     */
    void start() const;
};

#endif
