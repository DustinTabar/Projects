// Name: Dustin Tabar
// Student ID: 200447720
// Email: tabar010@cougars.csusm.com

#include <iostream>
using namespace std;

struct Node {
  int data;
  Node * LC;
  Node * RC;
};

class BinarySearchTree {
  private:
    Node * root_;
  
    void printPreOrder(Node* subRoot) {
      if (subRoot == nullptr) {
        return;
      }
      cout << subRoot->data << ' ';
      printPreOrder(subRoot->LC);
      printPreOrder(subRoot->RC);
    }

    void printInOrder(Node* subRoot) {
      if (subRoot == nullptr) {
        return;
      }
      printInOrder(subRoot->LC);
      cout << subRoot->data << ' ';
      printInOrder(subRoot->RC);
    }

    void printPostOrder(Node* subRoot) {
      if (subRoot == nullptr) {
        return;
      }
      printPostOrder(subRoot->LC);
      printPostOrder(subRoot->RC);
      cout << subRoot->data << ' ';
    }

    Node* search(int key, Node* subRoot) {
      if (subRoot == nullptr || subRoot->data == key) {
        return subRoot;
      }
      else if (key < subRoot->data) {
        return search(key, subRoot->LC);
      }
      else {
        return search(key, subRoot->RC);
      }
    }

    Node* insert(int key, Node* subRoot) {
      if (subRoot == nullptr) {
        subRoot = new Node;
        subRoot->data = key;
        subRoot->LC = subRoot->RC = nullptr;
      }
      else if (key < subRoot->data) {
        subRoot->LC = insert(key, subRoot->LC);
      }
      else if (key > subRoot->data) {
        subRoot->RC = insert(key, subRoot->RC);
      }
      return subRoot;
    }

    Node* remove(int key, Node* subRoot) {
      // key does not exist in tree case
      if (subRoot == nullptr) {
        return subRoot;
      }
      // traverse to find if key value exists in tree
      else if (key < subRoot->data) {
        subRoot->LC = remove(key, subRoot->LC);
      }
      else if (key > subRoot->data) {
        subRoot->RC = remove(key, subRoot->RC);
      }
      // if key is found
      else if (key == subRoot->data) {
        // key is on a leaf node case
        if (subRoot->LC == nullptr && subRoot->RC == nullptr) {
          delete subRoot;
          subRoot = nullptr;
        }
        else {
          Node* temp;
          // key node has one child case
          if (subRoot->RC == nullptr) {
            temp = subRoot->LC;
            delete subRoot;
            subRoot = temp;
          }
          else if (subRoot->LC == nullptr) {
            temp = subRoot->RC;
            delete subRoot;
            subRoot = temp;
          }
          // key node has 2 children case
          else {
            temp = rightMostNode(subRoot->LC);
            subRoot->data = temp->data;
            subRoot->LC = remove(temp->data, subRoot->LC);
          }
        }
      }
      return subRoot;
    }

    Node* rightMostNode(Node* subRoot) {
      Node* temp = subRoot;
      while (temp->RC != nullptr) {
        temp = temp->RC;
      }
      return temp;
    }

  public:
    BinarySearchTree() {
      root_ = nullptr;
    }

    void printPreOrder() {
      printPreOrder(root_);
    }

    void printInOrder() {
      printInOrder(root_);
    }

    void printPostOrder() {
      printPostOrder(root_);
    }

    Node* search(int key) {
      return search(key, root_);
    }

    void insert(int key) {
      root_ = insert(key, root_);
    }

    void remove(int key) {
      root_ = remove(key, root_);
    }
};

int main() {
  const int SIZE = 10;
  int dataList[SIZE];
  BinarySearchTree BST;
  int numToSearch, tempNum;

  cout << "\nEnter " << SIZE << " integers to store in a BST (seperate with a space): ";
  for (int i = 0; i < SIZE; i++) {
    cin >> tempNum;
    dataList[i] = tempNum;
  }
  cout << endl;

  // create the BST, also tests insertion method
  for (int i = 0; i < SIZE; i++) {
    cout << "inserting " << dataList[i] << endl;
    BST.insert(dataList[i]);
    cout << "current tree (in-order): ";
    BST.printInOrder();
    cout << endl << endl;
  }

  // test the 3 traversal methods
  cout << "\nPreorder traversal:   ";
  BST.printPreOrder();
  cout << endl;
  cout << "Inorder traversal:    ";
  BST.printInOrder();
  cout << endl;
  cout << "Postorder traversal:  ";
  BST.printPostOrder();
  cout << endl << endl;

  // test searching method
  cout << "\nenter a number to search for: ";
  cin >> numToSearch;

  if (BST.search(numToSearch) == nullptr) {
    cout << "-> " << numToSearch << " is not in the tree" << endl;
  }
  else {
    cout << "-> " << numToSearch << " is in the tree" << endl;
  }
  cout << endl << endl;

  // test deletion method
  cout << "Choose a number to remove: ";
  cin >> tempNum;
  BST.remove(tempNum);
  cout << "-> New tree (in-order): ";
  BST.printInOrder();
  cout << endl;

  return 0;
}
