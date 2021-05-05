//
// Created by 28320 on 2021/5/6.
//

#ifndef DIRECTORY_SHELL_H
#define DIRECTORY_SHELL_H

#include "split.h"
#include "CatalogTree.h"
#include "fstream"

class Shell {
public:
    Shell() {
        t.load("file");
    }
    ~Shell() {
        t.save("file");
    }
    void loop();
private:
    void run();

    ifstream input;
    ofstream output;
    CatalogTree t;
    string line;
    vector<string> args;
};


#endif //DIRECTORY_SHELL_H
