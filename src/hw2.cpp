#include <algorithm>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct Node {
  int key;
  int value;
  Node *left;
  Node *right;
};

int heightFrom(Node *node) {
  if (!node) {
    return 0;
  }
  if (!node->left && !node->right) {
    return 0;
  }
  return 1 + std::max(heightFrom(node->left), heightFrom(node->right));
}

int maxKey(Node *node) {
  if (!node) {
    return -9999;
  }
  if (!node->left && !node->right) {
    return node->key;
  }
  return std::max(maxKey(node->left), maxKey(node->right));
}

std::vector<Node *> childrenOf(const std::vector<Node *> &parents) {
  std::vector<Node *> children;
  for (auto &p : parents) {
    if (p) {
      children.push_back(p->left);
      children.push_back(p->right);
    } else {
      children.push_back(NULL);
      children.push_back(NULL);
    }
  }
  return children;
}

void printTree(Node *root) {
  int h = heightFrom(root);
  int w = 2 * (int)pow(2, h);
  int nspaces = 1 + (int)log10(maxKey(root));
  // std::cout << "h = " << h << ", w = " << w << std::endl;
  std::vector<Node *> currents = {root};
  for (int i = 0; i <= h; i++) {
    int many = (int)pow(2, i);
    int block = w / many;
    // std::cout << "many = " << many << ", block = " << block << std::endl;
    for (int j = 0; j < many; j++) {
      for (int k = 0; k < block; k++) {
        std::cout << std::setfill(' ') << std::setw(nspaces);
        if (k == block / 2 && currents[j]) {
          std::cout << currents[j]->value;
        } else {
          std::cout << ' ';
        }
      }
    }
    // int h_ = (int)pow(2, h-i-1);
    // int many_ = 2*many;
    // int block_ = w / many_;
    // for (int j = 0; j < h_; j++) {
    //   for (int k = 0; k < many_; k++) {
    //     for (int l = 0; l < block_; l++) {
    //       if (k % 2 == 0) {
    //
    //       } else {
    //
    //       }
    //     }
    //   }
    // }
    std::cout << "\n";
    currents = childrenOf(currents);
  }
}

Node *insert(Node *root, Node *node) {
  if (!root) {
    root = node;
  } else if (node->key < root->key) {
    root->left = insert(root->left, node);
  } else {
    root->right = insert(root->right, node);
  }
  return root;
}

// Any node other than leaves and their parents must have 2 children
bool bstCheck1(Node *root) {
  int h = heightFrom(root);
  if (h < 2) {
    return true;
  }
  if (h == 2) {
    return root->left && root->right;
  }
  return bstCheck1(root->left) && bstCheck1(root->right);
}
// void bstFix1(Node *root) {
//   int h = heightFrom(root);
//   if (h < 2) {
//     return;
//   }
//   if (h == 2) {
//     if (root->left && !root->right) {
//
//     } else if (!root->left && root->right) {
//
//     }
//     return;
//   }
//   bstFix1(root->left);
//   bstFix1(root->right);
// }

// 2 subtrees of a node must differ in height no greater than 1
bool bstCheck2(Node *root) {
  return abs(heightFrom(root->left) - heightFrom(root->right)) <= 1;
}

// Node *bstInsert(Node *root, Node *node) {
//   root = insert(node);
//   //
// }

void mid(int i, int j, std::function<void(int)> f) {
  if (i == j) {
    return;
  }
  int k = (i + j) / 2;
  f(k);
  if (j - i > 1) {
    mid(i, k, f);
    mid(k + 1, j, f);
  }
}

Node *makeBst(std::vector<int> &list) {
  std::sort(list.begin(), list.end());
  Node *root = NULL;
  mid(0, list.size(), [&root, &list](int i) {
    int k = list[i];
    Node *node = new Node{k, k, NULL, NULL};
    root = insert(root, node);
  });
  return root;
}

int main() {
  //         1
  //        /\
  //       /  \
  //      /    \
  //     /      \
  //    4       1
  //   / \     / \
  //  /   \   /   \
  //  2   6   1   1
  // / \ / \ / \ / \
  // 1 3 5 7 1 1 1 1
  std::vector<int> list;
  int x;
  std::cout << "add ";
  while (std::cin >> x) {
    list.push_back(x);
    Node *root = makeBst(list);
    std::cout << "----------------\n";
    printTree(root);
    std::cout << "----------------\n";
    std::cout << "add ";
  }
}
