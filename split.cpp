//
// Created by 28320 on 2021/5/6.
//

#include "split.h"

vector<string> split(const string &s) {
    vector<string> res;
    string tmp;
    for (auto &x : s) {
        if (x == ' ') {
            res.push_back(tmp);
            tmp = "";
        } else {
            tmp += x;
        }
    }
    res.push_back(tmp);
    return res;
}
