#ifndef PACKAGE_H
#define PACKAGE_H

#include <bits/stdc++.h>
#include "History.h"
using namespace std;

/**
 * @brief 包裹基类
 * 
 */
class BasePackage {
protected:
    // 包裹pid, 名称, 描述, 状态
    string pid, pname, description, state;
    // 包裹发送价格
    int fee = 15;
public:
    /**
     * @brief Construct a new Base Package object
     * 
     */
    BasePackage(){}
    /**
     * @brief Construct a new Base Package object
     * 
     * @param _pid 
     * @param _pname 
     * @param _state 
     * @param _description 
     * @param _fee 
     */
    BasePackage(string _pid, string _pname, string _state = "待签收", string _description = "无", int _fee = 15)
        :pid(_pid), pname(_pname), state(_state), description(_description), fee(_fee) {};
    /**
     * @brief Get the Pid object
     * 
     * @return string 
     */
    string getPid() const { return pid; }
    /**
     * @brief Get the Pname object
     * 
     * @return string 
     */
    string getPname() const { return pname; }
    /**
     * @brief Get the State object
     * 
     * @return string 
     */
    string getState() const { return state; }
    /**
     * @brief Get the Description object
     * 
     * @return string 
     */
    string getDescription() const { return description; }
    /**
     * @brief Get the Fee object
     * 
     * @return int 
     */
    int getFee() const { return fee; }
    /**
     * @brief 判断余额是否足够支付发送费用
     * 
     * @param wallet 
     * @return true 
     * @return false 
     */
    bool canSend(int wallet) const { return wallet >= fee; }
    /**
     * @brief 是否可以删除包裹
     * 
     * @return true 
     * @return false 
     */
    bool canDel() const { return state == "signed"; }
    /**
     * @brief 是否匹配包裹
     * 
     * @param s 
     * @return true 
     * @return false 
     */
    bool match(const string &s) const;
    /**
     * @brief 打印包裹
     * 
     */
    void print() const;
    /**
     * @brief 流输出包裹
     * 
     * @param in 
     * @param bp 
     * @return istream& 
     */
    friend istream &operator >> (istream &in, BasePackage &bp);
    /**
     * @brief 流输入包裹
     * 
     * @param out 
     * @param bp 
     * @return ostream& 
     */
    friend ostream &operator << (ostream &out, const BasePackage &bp);
};

/**
 * @brief 包裹类
 * 
 */
class Package: public BasePackage {
    /**
     * @brief 包裹历史记录
     * 
     */
    HistoryList pacHis;
public:
    /**
     * @brief Get the Base object
     * 
     * @return BasePackage 
     */
    BasePackage getBase() const { return BasePackage(pid, pname, state, description, fee); }
    /**
     * @brief 发送包裹
     * 
     * @param bh 
     */
    void reqSend(const BaseHistory &bh);
    /**
     * @brief 发送包裹完毕
     * 
     * @param bh 
     */
    void finSend(const BaseHistory &bh);
    /**
     * @brief 接受包裹
     * 
     * @param bh 
     */
    void reqRecv(const BaseHistory &bh);
    /**
     * @brief 接受包裹完毕
     * 
     * @param bh 
     */
    void finRecv(const BaseHistory &bh);
    /**
     * @brief 打印包裹历史
     * 
     * @return int 
     */
    int printPacHis() const;
    string printPacHis(const int &idx) const;
    friend istream &operator >> (istream &in, Package &p);
    friend ostream &operator << (ostream &out, const Package &p);
};

/**
 * @brief 包裹列表类
 * 
 */
class PackageList {
    // 包裹列表
    vector <BasePackage> pl;
public:
    /**
     * @brief 重载[]操作符
     * 
     * @param pid 
     * @return BasePackage& 
     */
    BasePackage &operator [] (const string &pid);
    BasePackage &operator [] (const int &num);
    /**
     * @brief 返回列表大小
     * 
     * @return int 
     */
    int size() const { return pl.size(); }
    /**
     * @brief 判断pid包裹是否存在
     * 
     * @param pid 
     * @return true 
     * @return false 
     */
    bool pidExist(const string &pid) const;
    /**
     * @brief 添加包裹
     * 
     * @param bp 
     */
    void add(const BasePackage &bp);
    /**
     * @brief 删除包裹
     * 
     * @param bp 
     */
    void del(const BasePackage &bp);
    void del(const string &pid);
    /**
     * @brief 打印包裹
     * 
     * @return int 
     */
    int print() const;
    string print(const int &idx) const;
    void print(const string &pid) const;
    /**
     * @brief 搜索包裹
     * 
     * @param s 
     */
    void schPackage(const string &s) const;
    friend istream &operator >> (istream &in, PackageList &pl);
    friend ostream &operator << (ostream &out, const PackageList &pl);
};

#endif
