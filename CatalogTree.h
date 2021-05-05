//
// Created by 28320 on 2021/5/5.
//

#ifndef DIRECTORY_CATALOGTREE_H
#define DIRECTORY_CATALOGTREE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct CatalogNode {
    string rPath;
    CatalogNode *sibling;
    CatalogNode *parent;
    CatalogNode *child;
};

class CatalogTree {
public:
    vector<string> getChildren();
    void eraseChild(const string &theRPath);
    void insertChild(const string &theRPath);
    void setPath(const string &thePath);
    void setPathWithParent();
    vector<string> getFPath();
private:
    void erase(); // 将当前的目录所在的子树释放掉
    CatalogNode *root;
};


#endif //DIRECTORY_CATALOGTREE_H
