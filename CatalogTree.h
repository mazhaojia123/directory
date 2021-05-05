//
// Created by 28320 on 2021/5/5.
//

#ifndef DIRECTORY_CATALOGTREE_H
#define DIRECTORY_CATALOGTREE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

struct CatalogNode {
    CatalogNode() {
        rPath = "";
        parent = nullptr;
        sibling = nullptr; // 右孩子
        child = nullptr; // 左孩子？？？
    }

    string rPath;
    CatalogNode *sibling;
    CatalogNode *parent;
    CatalogNode *child;
};

class CatalogTree {
public:
    CatalogTree();

    ~CatalogTree();

    vector<CatalogNode*> getChildren(); // 看成链表

    void eraseChild(const string &theRPath); // 看成二叉树

    void insertChild(const string &theRPath); // 看成链表

    void setPath(const string &thePath); // 从语义

    void setPathWithParent(); // 从语义

    vector<string> getFPath(); // 从语义

    bool save(const string &filePath); // 看成二叉树

    bool load(const string &filePath); // 看成二叉树

private:
    void erase(CatalogNode *cur); // 将当前的目录所在的子树释放掉

    static vector<string> split(const string &s);

    static void ascendInsert(CatalogNode *theHead, CatalogNode *thePar, const string &rPath);

    void preSave(CatalogNode *cur);

    void preLoad(CatalogNode *&cur);

    void updatePar(CatalogNode *);

//    void dispose(CatalogNode *cur);

    CatalogNode root; // 根目录是不能删除掉的, 根目录默认是一个空的字符串
    CatalogNode *currentNode; // 指向当前所在的节点
    ofstream output;
    ifstream input;
};


#endif //DIRECTORY_CATALOGTREE_H
