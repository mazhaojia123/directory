//
// Created by 28320 on 2021/5/6.
//

#include "Shell.h"

void Shell::loop() {
    do {
        vector<string> curFPath = t.getFPath();
        cout << curFPath[0];
        for (int i = 1; i < curFPath.size(); i++)
            cout << '/' << curFPath[i];
        if (curFPath.size() == 1) cout << '/';
        cout << " >" << flush;

        getline(cin, line);
        args = split(line);

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
                // do nothing
            } else if (args[1] == "..")
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
            t.eraseChild(args[1] + "*"); // 删掉文件
//        } else if (args[0] == "save") {
//            t.save(args[1]);
//        } else if (args[0] == "load") {
//            t.load(args[1]);
        } else if (args[0] == "run") {
            if (args.size() == 1) {
                for (int i = 0; i <= 9; i++) {
                    string halfPathIn = "../input/in";
                    string halfPathOut = "../myOutput/out";
                    string suffixPath = ".txt";

                    input.open(halfPathIn + to_string(i) + suffixPath);
                    output.open(halfPathOut + to_string(i) + suffixPath);
                    if (!input.is_open() || !output.is_open()) {
                        cerr << "failed to open file" << endl;
                        continue;
                    }

                    run();
                    input.close();
                    output.close();
                }
            }
            else {
                string inPath = args[1];
                string outPath = args[2];

                input.open(inPath);
                output.open(outPath);
                if (!input.is_open() || !output.is_open()) {
                    cerr << "failed to open file" << endl;
                    continue;
                }

                run();
                input.close();
                output.close();
            }
        }
    } while (args[0] != "quit");
}

void Shell::run() {
    CatalogTree tmpT;
    vector<string> tmpArgs;
    string tmpLine;
    getline(input, tmpLine);
    tmpArgs = split(tmpLine);
    while (tmpArgs[0] != "quit") {
        if (tmpArgs[0] == "dir") {
            vector<CatalogNode *> v = tmpT.getChildren();
            vector<string> ans;
            for (auto &x : v) {
                if (x->rPath[x->rPath.size() - 1] != '*')
                    ans.push_back(x->rPath);
                else
                    output << x->rPath << endl;
            }
            for (auto &x : ans)
                output << x << endl;

        } else if (tmpArgs[0] == "cd") {
            if (tmpArgs.size() == 1) {
                vector<string> ans = tmpT.getFPath();
                output << ans[0];
                for (int i = 1; i < ans.size(); i++)
                    output << '/' << ans[i];
                if (ans.size() == 1) output << '/';
                output << endl;
            } else if (tmpArgs[1] == "..")
                tmpT.setPathWithParent();
            else
                tmpT.setPath(tmpArgs[1]);
        } else if (tmpArgs[0] == "mkdir") {
            tmpT.insertChild(tmpArgs[1]);
        } else if (tmpArgs[0] == "mkfile") {
            tmpArgs[1] += "*";
            tmpT.insertChild(tmpArgs[1]);
        } else if (tmpArgs[0] == "delete") {
            tmpT.eraseChild(tmpArgs[1]);// 删掉目录
            tmpT.eraseChild(tmpArgs[1] + "*"); // 删掉文件
        } else if (tmpArgs[0] == "save") {
            tmpT.save(tmpArgs[1]);
        } else if (tmpArgs[0] == "load") {
            tmpT.load(tmpArgs[1]);
        }
        getline(input, tmpLine);
        tmpArgs = split(tmpLine);
    }

}
