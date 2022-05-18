#include <bits/stdc++.h>
#include "Console.h"
using namespace std;

//Console

void Console::mkDir(const string &s) {
    string cmd = "mkdir "+s;
    system(cmd.c_str());
}

void Console::rmDir(const string &s) {
    string cmd = "rm -r "+s;
    system(cmd.c_str());
}

string Console::pacDir(const string &s) {
    string path = "data/package/"+s+"/";
    return path;
}

string Console::usrDir(const string &s) {
    string path = "data/user/"+s+"/";
    return path;
}

string Console::hisDir(const string &s) {
    string path = "data/history/"+s+"/";
    return path;
}
