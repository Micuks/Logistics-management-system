#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <bits/stdc++.h>
#include "Package.h"
#include "User.h"
#include "History.h"
#include "Console.h"
using namespace std;

extern Console con;
/**
 * @brief 仓库类, 封装快递发送, 管理和接受的所有数据和所有用户类的操作
 * 
 */
class Warehouse {
    /**
     * @brief 从文件读入和读出用户数据
     * 
     */
    class Data {
    public:
        // 包裹列表
        PackageList pl;
        // 用户列表
        UserList ul;
        // 历史记录列表
        HistoryList hl;
        // 发送记录列表
        HistoryList sendReq;
        // 签收记录列表
        HistoryList recvReq;
        // 管理员
        Manager m0;
        Data() {
            con.inFile("data/manPasswd", m0);
            con.inFile("data/packageList", pl);
            con.inFile("data/userList", ul);
            con.inFile("data/historyList", hl);
        }
        // 获取新的历史记录标号
        string getHis() const { return "H"+to_string(5760000000+hl.size()); }
        // 获取新的包裹编号
        string getPkg() const { return "P"+to_string(0000000000+pl.size()); }
        // 充值管理员账户
        void chargeMWallet(const int &val) {
            m0.chargeWallet(val); con.outFile("data/manPasswd", m0);
        };
        // 保存包裹列表
        void outPList() const { con.outFile("data/packageList", pl); }
        // 保存用户列表
        void outUList() const { con.outFile("data/userList", ul); }
        // 保存历史列表
        void outHList() const { con.outFile("data/historyList", hl); }
    } data;
public:
    /**
     * @brief 用户, 管理员的公操作
     * 
     */
    class Operation {
        Data *data;
    public:
        Operation(Data *_data):data(_data){}
        /**
         * @brief 充值管理员包裹
         * 
         * @param val 
         */
        void chargeMWallet(const int &val);
        /**
         * @brief 打印所有包裹
         * 
         * @return int 包裹数量
         */
        int printPackage() const;
        /**
         * @brief 打印所有用户
         * 
         * @return int 用户数量
         */
        int printUser() const;
        /**
         * @brief 打印所有历史记录
         * 
         * @return int 历史记录数量
         */
        int printHistory() const;
        /**
         * @brief 打印下标idx的包裹
         * 
         * @param idx 包裹下标
         * @return string 包裹pid
         */
        string printPackage(const int &idx) const;
        /**
         * @brief 打印下标idx的用户
         * 
         * @param idx 用户下标
         * @return string 用户uid
         */
        string printUser(const int &idx) const;
        /**
         * @brief 打印下标idx的历史记录
         * 
         * @param idx 历史记录下标
         * @return string 历史记录hid
         */
        string printHistory(const int &idx) const;
        /**
         * @brief 打印包裹
         * 
         * @param pid 包裹的pid
         */
        void printPackage(const string &pid) const;
        /**
         * @brief 打印用户
         * 
         * @param uid 用户uid
         */
        void printUser(const string &uid) const;
        /**
         * @brief 打印历史记录hid
         * 
         * @param hid 历史记录hid
         */
        void printHistory(const string &hid) const;
        /**
         * @brief 搜索包裹
         * 
         * @param s 包裹pid
         */
        void schPackage(const string &s) const;
        /**
         * @brief 包裹是否存在
         * 
         * @param pid 包裹pid
         * @return true 
         * @return false 
         */
        bool pidExist(const string &pid) const;
        /**
         * @brief 用户是否存在
         * 
         * @param uid 用户uid
         * @return true 
         * @return false 
         */
        bool uidExist(const string &uid) const;
    } op;
    /**
     * @brief 管理员操作类
     * 
     */
    class ManagerOperation {
        // 数据类
        Data *data;
        // 管理员配置文件路径
        string mp;
        // 管理员对象
        Manager m;
    public:
        /**
         * @brief Construct a new Manager Operation object
         * 
         * @param _data 
         */
        ManagerOperation(Data *_data):data(_data) { setManager(); }
        /**
         * @brief Set the Manager object
         * 
         */
        void setManager();
        /**
         * @brief 添加用户u
         * 
         * @param u 用户对象
         */
        void addUser(const User &u) const;
        /**
         * @brief 删除包裹
         * 
         * @param pid 包裹pid
         */
        void delPackage(const string &pid) const;
        /**
         * @brief 删除用户
         * 
         * @param uid 用户uid
         */
        void delUser(const string &uid) const;
        /**
         * @brief 获取钱包余额
         * 
         * @return int 余额
         */
        int getWallet() const;
        /**
         * @brief 密码检验
         * 
         * @param s 输入的密码
         * @return true 
         * @return false 
         */
        bool mpasswdMatch(const string &s) { return m.mpasswdMatch(s); }
        /**
         * @brief 修改密码
         * 
         * @param s 新密码
         */
        void changeMPasswd(const string &s);
        /**
         * @brief 搜索用户
         * 
         * @param s 用户uid, uname等
         */
        void schUser(const string &s) const;
        /**
         * @brief 搜索历史记录
         * 
         * @param s 历史记录关键字, 如历史记录hid
         */
        void schHistory(const string &s) const;
    } mop;

    /**
     * @brief 用户操作类
     * 
     */
    class UserOperation {
        // 数据类
        Data *data;
        // 用户uid, 用户配置文件路径
        string uid, up;
        // 用户对象
        User u;
        /**
         * @brief 添加历史记录
         * 
         * @param pid 历史记录pid
         * @param rid 接收方uid
         * @param fee 包裹快递费用
         * @return string 包裹hid
         */
        string addHistory(const string &pid, const string &rid, const int &fee) const; // 发送pid包裹并返回hid
    public:
        /**
         * @brief 初始化发送和接受列表
         * 
         */
        void initSRHis() const;
        /**
         * @brief Construct a new User Operation object
         * 
         * @param _data 数据类
         */
        UserOperation(Data *_data):data(_data){}
        /**
         * @brief Set the User object
         * 
         * @param _uid 用户uid
         */
        void setUser(const string &_uid);
        /**
         * @brief 添加新包裹
         * 
         * @param pname 包裹名
         * @param description 包裹描述
         * @return string 包裹pid
         */
        string addPackage(const string &pname, const string &description = "none") const;
        /**
         * @brief 添加包裹
         * 
         * @param p 包裹对象
         */
        void addPackage(const Package &p) const;
        /**
         * @brief 支付包裹, 返回支付是否成功
         * 
         * @param pid 包裹pid
         * @return true 
         * @return false 
         */
        bool billPackage(const string &pid);
        /**
         * @brief Get the Wallet object
         * 
         * @return int 钱包余额
         */
        int getWallet() const;
        /**
         * @brief 给钱包充值
         * 
         * @param val 
         */
        void chargeWallet(const int &val);
        /**
         * @brief 添加发送包裹
         * 
         * @param pid 包裹pid
         * @param rid 接收方uid
         * @param fee 包裹发送费用
         * @return string 包裹历史记录hid
         */
        string reqSend(const string &pid, const string &rid, const int &fee);
        /**
         * @brief 完成包裹发送, 即包裹被签收
         * 
         * @param hid 包裹历史记录hid
         */
        void finSend(const string &hid);
        /**
         * @brief 添加待签收包裹
         * 
         * @param hid 包裹历史记录hid
         */
        void reqRecv(const string &hid);
        /**
         * @brief 完成包裹签收
         * 
         * @param hid 包裹历史记录hid
         */
        void finRecv(const string &hid);
        /**
         * @brief 打印发送包裹
         * 
         * @return int 发送包裹数量
         */
        int printSendHis() const;
        /**
         * @brief 打印签收包裹
         * 
         * @return int 签收包裹数量
         */
        int printRecvHis() const;
        /**
         * @brief 打印发送包裹历史
         * 
         * @param num 发送包裹下标
         * @return string 发送包裹pid
         */
        string printSendHis(const int &num) const;
        /**
         * @brief 打印签收包裹历史
         * 
         * @param num 签收包裹下标
         * @return string 签收包裹pid
         */
        string printRecvHis(const int &num) const;
        /**
         * @brief 搜索发送历史
         * 
         * @param pid 包裹pid
         * @return string 包裹hid
         */
        string schSendHis(const string &pid);
        /**
         * @brief 搜索签收历史
         * 
         * @param pid 包裹pid
         * @return string 包裹历史记录hid
         */
        string schRecvHis(const string &pid);
        /**
         * @brief 判断密码是否正确
         * 
         * @param s 输入的密码
         * @return true 
         * @return false 
         */
        bool upasswdMatch(const string &s) const { return u.upasswdMatch(s); };
        /**
         * @brief 更改密码
         * 
         * @param s 
         */
        void changeUpasswd(const string &s);
    } uop;
    /**
     * @brief Construct a new Warehouse object
     * 
     */
    Warehouse():op(Operation(&data)), mop(ManagerOperation(&data)), uop(UserOperation(&data)){}
};

#endif
