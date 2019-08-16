//
//  main.cpp
//  tree
//
//  Created by junl on 2019/7/20.
//  Copyright © 2019 junl. All rights reserved.
//

#include <iostream>
#include "btree.h"
#include "bSearchTree.h"
#include "heap.h"
#include "inorderTraversal.h"
#include "isValidBST.h"
#include "invertTree.h"
#include "maxDepth.h"
#include "buildTree.h"
#include "minDepth.h"
#include "hasPathSum.h"
#include "preorderTraversal.h"
#include "kthSmallestInTree.h"
#include "HasSubtree.h"
#include "Mirror.h"
#include "FindPath.h"
#include "IsBalanced_Solution.h"
#include "GetNext.h"
#include "isSymmetrical.h"
#include "VerifySquenceOfBST.h"
#include "isSameTree.h"
#include <string>
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    using namespace std;
    typedef bnode<string> node;
    node *root = new node("A");
    node *b = new node("B");
    node *c = new node("C");
    node *d = new node("D");
    node *e = new node("E");
    node *f = new node("F");
    node *g = new node("G");
    root->lchild = b;
    root->rchild = c;
    b->lchild = d;
    b->rchild = e;
    c->lchild = f;
    c->rchild = g;
    cout << "preOrder starting............." << endl;
    btree::preOrder(root);
    cout << "inOrder starting............." << endl;
    btree::inOrder(root);
    cout << "postOrder starting............." << endl;
    btree::postOrder(root);
    cout << "levelOrder starting............." << endl;
    btree::levelOrder(root);
    cout << "printfleaf starting............." << endl;
    btree::printfleaf(root);
    
    cout << "getleafnum starting............." << endl;
    cout << btree::getleafnum(root) << endl;
    
    cout << "getheight starting............." << endl;
    cout << btree::getheight(root) << endl;
    
    
    cout << "bSearchTree starting........." << endl;
    using namespace bSearchTree;
    inode *tree = new inode(13);
    insert_node(8, tree);
    insert_node(6, tree);
    insert_node(10, tree);
    insert_node(18, tree);
    insert_node(16, tree);
    insert_node(20, tree);
    btree::inOrder(tree);
    
    if (find_node(18, tree)) {
        cout << "find_node  18" << endl;
    }
    cout << "delete_node starting........." << endl;
    delete_node(13, tree);
    btree::inOrder(tree);
    cout << "max_node :" << get_max(tree)  << endl;
    cout << "min_node :" << get_min(tree)  << endl;
    cout << "get_prenode: " << get_prenode(8, tree) << endl;
    cout << "get_postnode: " << get_postnode(8, tree) << endl;
    
    cout << "heap starting........." << endl;
    heap hp;
    for (int i=1; i<7; i++) {
        hp.insert(i);
    }
    hp.print();
    hp.removemax();
    hp.removemax();
    hp.print();
    
    cout << "leetcode stating..........\n\n" << endl;
    leetcode::test_inorderTraversal();
    leetcode::test_isValidBST();
    leetcode::test_invertTree();
    leetcode::test_buildTree();
    leetcode::test_minDepth();
    leetcode::test_hasPathSum();
    leetcode::test_preorderTraversal();
    leetcode::test_kthSmallest();
    
    
    codinginterviews::test_HasSubtree();
    codinginterviews::test_Mirror();
    codinginterviews::test_FindPath();
    codinginterviews::test_IsBalanced_Solution2();
    codinginterviews::test_isSymmetrical2();
    return 0;
}
