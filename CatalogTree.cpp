//
// Created by 28320 on 2021/5/5.
//

#include "CatalogTree.h"

CatalogTree::CatalogTree() {
    currentNode = &root;
}

CatalogTree::~CatalogTree() {
    // 将除了根节点之外的节点，都删除掉
    CatalogNode *cur = root.child;
    erase(cur); // 删掉整个的二叉结构
}

vector<CatalogNode *> CatalogTree::getChildren() {
    vector<CatalogNode *> res;
    CatalogNode *cur = currentNode->child;

    if (cur == nullptr) return res;
    else cur = cur->sibling;

    while (cur != nullptr) {
        res.push_back(cur);
        cur = cur->sibling;
    }
    return res;
}

void CatalogTree::eraseChild(const string &theRPath) {
    // 先将这个节点的孩子节点所在的二叉树全都删掉
    CatalogNode *pre = currentNode->child;

    // 如果没有孩子，他却要删？？？那咱就直接返回，反正没得删
    if (pre == nullptr) return;

    CatalogNode *cur = pre->sibling;
    while (cur != nullptr && cur->rPath != theRPath) {
        cur = cur->sibling;
        pre = pre->sibling;
    }
    if (cur == nullptr)
        return; // 没有找到这个节点

    erase(cur->child);

    // 把前后链表前后连起来
    pre->sibling = cur->sibling;

    // 把这个节点的空间释放
    delete cur;
}

void CatalogTree::insertChild(const string &theRPath) {
    if (currentNode->child == nullptr) {
        // 则给孩子链表设置一个头节点
        // 没有必要让他指向父亲
        // 字符串 @
        // 没有孩子
        currentNode->child = new CatalogNode;
        currentNode->child->rPath = "@"; // 专门表示头节点
    }
    ascendInsert(currentNode->child, currentNode, theRPath);

}

void CatalogTree::setPath(const string &thePath) {
    CatalogNode *cur = nullptr;

    if (thePath[0] == '/') { // 这是一个绝对路径
        CatalogNode *newCurrentNode = &root;
        vector<string> tmpPath = split(thePath);

        for (auto &x: tmpPath) {
            cur = newCurrentNode->child;
            while (cur != nullptr && cur->rPath != x)
                cur = cur->sibling;
            if (cur == nullptr) return;
            else newCurrentNode = cur;
        }

        currentNode = newCurrentNode;
    } else { // 相对路径
        cur = currentNode->child;
        while (cur != nullptr && cur->rPath != thePath)
            cur = cur->sibling;
        if (cur != nullptr)
            currentNode = cur; // 设置当前的路径为thePath
    }
}

void CatalogTree::setPathWithParent() {
    if (currentNode->parent == nullptr) return; // 根节点，直接返回

    currentNode = currentNode->parent; // 更新当前节点
}

vector<string> CatalogTree::getFPath() {
    CatalogNode *cur = currentNode;
    vector<string> res;

    while (cur != nullptr) {
        res.push_back(cur->rPath);
        cur = cur->parent;
    }
    reverse(res.begin(), res.end());

    return res;
}

void CatalogTree::preSave(CatalogNode *cur) {
    if (cur != nullptr) {
        output << cur->rPath << '\n'; // 输出这个名字
        preSave(cur->child);
        preSave(cur->sibling);
    } else {
        output << "-1\n";
    }
}

bool CatalogTree::save(const string &filePath) {
    output.open(filePath);
    if (!output.is_open()) return false;

    vector<string> fullPath = getFPath(); // 先记下所在的路径

    preSave(root.child); // root的child为根的二叉树，打印到

//    for (int i = 1; i < fullPath.size(); i++)
//        output << fullPath[i] << ' ';

    output.close();
    return true;
}

void CatalogTree::preLoad(CatalogNode *&cur) {
    string tmp;
    input >> tmp;
    cout << "read : " << tmp << endl;

    if (tmp == "-1") return; // 意味着读取失败

    cur = new CatalogNode;
    cur->rPath = tmp;

    preLoad(cur->child);
    preLoad(cur->sibling);
}

void CatalogTree::updatePar(CatalogNode *cur) {
    if (cur != nullptr) {
        currentNode = cur;
        vector<CatalogNode *> tmp = getChildren();
        for (auto &item: tmp)
            item->parent = cur;
        updatePar(cur->child);
        updatePar(cur->sibling);
    }
}

bool CatalogTree::load(const string &filePath) {
    // 删掉之前的
    erase(root.child);

    input.open(filePath);
    if (!input.is_open()) return false;


    // 不断new出其他的节点
    preLoad(root.child);


    // 更新全体的父亲节点
    updatePar(&root);

//    // 恢复currentNode
//    currentNode = &root;
//    string tmp;
//    while (input >> tmp) {
//        setPath(tmp);
//    }

    input.close();
    return true;
}

void CatalogTree::erase(CatalogNode *cur) {
    // 后序思想
//    if (cur != nullptr) {
//        CatalogNode *theCur = cur->child;
//        while (theCur != nullptr) {
//            erase(theCur);
//            theCur = theCur->sibling;
//        }
//        delete cur;
//    }
    if (cur != nullptr) {
        erase(cur->child);
        erase(cur->sibling);
        delete cur;
    }
}

void CatalogTree::ascendInsert(CatalogNode *theHead, CatalogNode *thePar, const string &theRPath) {
    // 插入这个节点到链表，并且设置这个节点的父亲
    // 如果这个节点已经存在，不做任何操作
    CatalogNode *pre = theHead;
    CatalogNode *cur = theHead->sibling;

    while (cur != nullptr && cur->rPath < theRPath) {
        cur = cur->sibling;
        pre = pre->sibling;
    }
    if (cur != nullptr && cur->rPath == theRPath)
        return; // 这个节点已经存在，直接返回
    // 插入一个新的节点
    CatalogNode *tmp = new CatalogNode;
    tmp->rPath = theRPath;
    tmp->parent = thePar;
    tmp->sibling = cur;
    pre->sibling = tmp;
}

vector<string> CatalogTree::split(const string &s) {
    // 分成多个相对路径
    vector<string> res;
    string tmp;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] != '/')
            tmp += s[i];
        else {
            res.push_back(tmp);
            tmp = "";
        }
    }
    res.push_back(tmp);
    return res;
}

void CatalogTree::draw() {
    printBT("", &root, false);
}

void CatalogTree::printBT(const string &prefix, const CatalogNode *node, bool isLeft) {
    if (node != nullptr) {
        std::cout << prefix;

        std::cout << (isLeft ? "├── " : "");

        // print the value of the node
        if (node == &root)
            std::cout << "/" << std::endl;
        else
            std::cout << node->rPath << std::endl;

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "│   " : "│   "), node->child, true);
        printBT(prefix + (isLeft ? "│   " : ""), node->sibling, false);
    }
}

