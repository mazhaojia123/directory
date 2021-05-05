#include <iostream>
#include "CatalogTree.h"

#define DEBUG

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

int main() {
#ifdef DEBUG
    freopen("../input/in9.txt", "r", stdin);
    freopen("../myOutput/out9.txt", "w", stdout);
#endif
    CatalogTree t;
    string op;
    vector<string> args;

    getline(cin, op);
    args = split(op);
    while (args[0] != "quit") {
        if (args[0] == "dir") {
            vector<CatalogNode *> v = t.getChildren();
            vector<string> ans;
            for (auto &x : v) {
                if (x->rPath[x->rPath.size() - 1] != '*')
                    ans.push_back(x->rPath);
                else
                    cout << x->rPath << endl;
            }
            for (auto &x : ans)
                cout << x << endl;

        } else if (args[0] == "cd") {
            if (args.size() == 1) {
                vector<string> ans = t.getFPath();
                cout << ans[0];
                for (int i = 1; i < ans.size(); i++)
                    cout << '/' << ans[i];
                if (ans.size() == 1) cout << '/';
                cout << endl;
            }
            else if (args[1] == "..")
                t.setPathWithParent();
            else
                t.setPath(args[1]);
        } else if (args[0] == "mkdir") {
            t.insertChild(args[1]);
        } else if (args[0] == "mkfile") {
            args[1] += "*";
            t.insertChild(args[1]);
        } else if (args[0] == "delete") {
            t.eraseChild(args[1]);// 删掉目录
            t.eraseChild(args[1]+"*"); // 删掉文件
        } else if (args[0] == "save") {
            t.save(args[1]);
        } else if (args[0] == "load") {
            t.load(args[1]);
        }
        getline(cin, op);
        args = split(op);
    }


    return 0;
}
