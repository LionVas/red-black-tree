#include <iostream>
#include <fstream>
#include <string>
using namespace std;
enum Color { red, black };
class dyn_list {
public:
    struct node {
        int data;
        node* next = nullptr;
    };
    node* head = nullptr;
    void init(int value) {
        head = new node;
        head->data = value;
        head->next = head;
    }
    void add(int value) { // допилить
        if (head == nullptr) {
            init(value);
        }
        else if (value >= head->data) {
            node* current = head;
            while (current->next != head) {
                current = current->next;
            }
            node* p = new node;
            p->data = value;
            p->next = head;
            current->next = p;
            head = p;
        }
        else {
            node* current = head;
            while (value < current->next->data and current->next != head) {
                current = current->next;
            }
            node* h = new node;
            h->data = value;
            h->next = current->next;
            current->next = h;
        }
    }
    void print_list(node*& head) {
        if (head == nullptr) {
            cout << "There are no elements in list \n";
        }
        else {
            node* p = head;
            do {
                cout << p->data << " ";
                p = p->next;
            } while (p != head);
            cout << "\n";
        }
    }
};
struct Data {
    string surname; // Фамилия
    string name; // имя
    string patronymic; // отчество
    dyn_list line_num;
    bool operator == (const Data& sec_op) {
        return ((this->surname == sec_op.surname) and (this->name == sec_op.name) and (this->patronymic == sec_op.patronymic));
    }
    bool operator > (const Data& sec_op) {
        if (this->surname == sec_op.surname) {
            if (this->name == sec_op.name) {
                if (this->patronymic == sec_op.patronymic)
                    return this->patronymic < sec_op.patronymic;
            }
            else {
                return this->name < sec_op.name;
            }
        }
        else {
            return this->surname < sec_op.surname;
        }
    }
    bool operator < (const Data& sec_op) {
        if (this->surname == sec_op.surname) {
            if (this->name == sec_op.name) {
                return this->patronymic < sec_op.patronymic;
            }
            else {
                return this->name < sec_op.name;
            }
        }
        else {
            return this->surname < sec_op.surname;
        }
    }
};
ostream& operator <<(ostream& os, const Data& data) {
    string full = data.surname + " " + data.name + " " + data.patronymic;
    return os << full;
}
ostream& operator <<(ostream& os, const Color color) {
    if (color == red) {
        return os << "red";
    }
    else {
        return os << "black";
    }
}
struct Node {
    Color color;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    Data data;
};
class RBtree {
public:

    Node* root;
    bool fl1 = false; // флаг для проверки висячего указателя
    void init() {
        root = nullptr;
        fl1 = true;
    }
    void leftRotation(Node*& node) {
        if (!fl1) {
            cout << "There is no tree";
            return;
        }
        Node* child = node->right;
        node->right = child->left;
        if (node->right != nullptr) {
            node->right->parent = node;
        }
        child->parent = node->parent;
        if (node->parent == nullptr) {
            root = child;
        }
        else if (node == node->parent->left) {
            node->parent->left = child;
        }
        else {
            node->parent->right = child;
        }
        child->left = node;
        node->parent = child;
    }
    void rightRotation(Node*& node) {
        if (!fl1) {
            cout << "There is no tree";
            return;
        }
        Node* child = node->left;
        node->left = child->right;
        if (node->left != nullptr) {
            node->left->parent = node;
        }
        child->parent = node->parent;
        if (node->parent == nullptr) {
            root = child;
        }
        else if (node == node->parent->left) {
            node->parent->left = child;
        }
        else {
            node->parent->right = child;
        }
        child->right = node;
        node->parent = child;
    }
    void addBalance(Node*& node) {
        if (!fl1) {
            cout << "There is no tree";
            return;
        }
        Node* parent = nullptr;
        Node* grand = nullptr;
        Node* uncle = nullptr;
        while ((node != root) and (node->color == red) and (node->parent->color == red)) {
            // cout<<node->color << " "<< node->parent->color;
            parent = node->parent;
            grand = parent->parent;
            if (parent == grand->left) {
                uncle = grand->right;
                if (uncle != nullptr and uncle->color == red) {
                    uncle->color = black;
                    parent->color = black;
                    grand->color = red;
                    node = grand;
                }
                else {
                    if (node == parent->right) {
                        leftRotation(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rightRotation(grand);
                    Color grandColor = grand->color;
                    grand->color = parent->color;
                    parent->color = grandColor;
                    node = parent;
                }
            }
            else {
                //cout << "right";
                uncle = grand->left;
                if (uncle != nullptr and uncle->color == red) {
                    uncle->color = black;
                    parent->color = black;
                    grand->color = red;
                    node = grand;
                }
                else {
                    if (node == parent->left) {
                        rightRotation(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    leftRotation(grand);
                    Color grandColor = grand->color;
                    grand->color = parent->color;
                    parent->color = grandColor;
                    node = parent;
                }
            }
        }
        root->color = black;
        //cout<<"Balance complete \n";
    }
    void add(Data data) {
        if (!fl1) {
            cout << "There is no tree";
            return;
        }
        if (root == nullptr) {
            root = new Node;
            root->color = black;
            root->data = data;
            //cout<<"Inserttt complete \n";
            return;
        }
        Node* newElem = new Node;
        newElem->data = data;
        newElem->color = red;
        Node* cur = root;
        Node* parent = nullptr;
        while (cur != nullptr) {
            parent = cur;
            if ((data > cur->data) or (data == cur->data)) {
                cur = cur->right;
            }
            else {
                cur = cur->left;
            }
        }
        newElem->parent = parent;
        if (parent == nullptr) {
            root = newElem;
        }
        else if ((data > parent->data) or (data == parent->data)) {
            parent->right = newElem;
        }
        else {
            parent->left = newElem;
        }
        //cout<<"Insert complete \n";
        addBalance(newElem);
    }
    void post_order(Node*& root) {
        if (root == nullptr) return;
        post_order(root->left);
        post_order(root->right);
        cout << ((root->color == red) ? "\x1b[31m" : "") << root->data << ((root->color == red) ? "\x1b[0m" : "") << "\n";
    }
    Node* search(Data data) {
        if (!fl1) {
            cout << "There is no tree";
            return nullptr;
        }
        Node* cur = root;
        bool fl = false; // флаг для проверки наличия элемента
        while (cur != nullptr) {
            if (data == cur->data) {
                break;
            }
            else if (data > cur->data) {
                cur = cur->right;
                continue;
            }
            else {
                cur = cur->left;
                continue;
            }
        }
        if (cur == nullptr) {
            // cout << "There is no such element in Tree";
            return nullptr;
        }
        else {
            // cout << cur->data << " \n";
            return cur;
        }
    }
    void remove(Data data) {
        if (!fl1) {
            cout << "There is no tree";
            return;
        }
        Node* cur = search(data);
        if (cur == nullptr) {
            return;
        }
        Node* del_node = cur; // удаляемая нода 
        Node* replace_node; // заменяющая нода
        Color delColor = del_node->color;
        if (cur->left == nullptr and cur->right == nullptr) {
            if (cur->parent == nullptr) {
                delete cur;
                root = nullptr;
                return;
            }
            if (cur->color == black) {
                removeBalance(cur);
            }
            Node* p = cur->parent;
            if (cur == p->right) {
                p->right = nullptr;
            }
            else {
                p->left = nullptr;
            }
            delete cur;
            return;
        }
        if (cur->left == nullptr) {
            replace_node = cur->right;
            if (replace_node != nullptr) {
                replace_node->parent = cur->parent;
            }
            if (cur->parent == nullptr) {
                root = replace_node; // Корень
            }
            else if (cur == cur->parent->left) {
                cur->parent->left = replace_node;
            }
            else {
                cur->parent->right = replace_node;
            }

            delete cur;
        }
        else if (cur->right == nullptr) {
            replace_node = cur->left;
            if (replace_node != nullptr) {
                replace_node->parent = cur->parent;
            }
            if (cur->parent == nullptr) {
                root = replace_node; // Корень
            }
            else if (cur == cur->parent->left) {
                cur->parent->left = replace_node;
            }
            else {
                cur->parent->right = replace_node;
            }
            delete cur;
        }
        else {
            // если два потомка адекватные
            del_node = cur->right;
            while (del_node->left != nullptr) {
                del_node = del_node->left;
            }
            delColor = del_node->color;
            replace_node = del_node->right; // Узел, который замещает del_node
            if (del_node->parent == cur) {
                if (replace_node != nullptr) {
                    replace_node->parent = del_node;
                }
            }
            else {
                if (replace_node != nullptr) {
                    replace_node->parent = del_node->parent;
                    del_node->parent->left = replace_node;
                }
                else {
                    del_node->parent->left = nullptr;
                }
                del_node->right = cur->right;
                if (cur->right != nullptr) {
                    cur->right->parent = del_node;
                }
            }

            if (cur->parent == nullptr) {
                root = del_node;
            }
            else if (cur == cur->parent->left) {
                cur->parent->left = del_node;
            }
            else {
                cur->parent->right = del_node;
            }
            del_node->parent = cur->parent;
            del_node->color = cur->color;
            del_node->left = cur->left;
            if (cur->left != nullptr) {
                cur->left->parent = del_node;
            }
            delete cur;
        }
       // cout << "UDALIL USPESHNO";
        if (delColor == black) {
            removeBalance(replace_node);
        }
        // cout<<"Remove complete \n";
    }
    void removeBalance(Node* replace_node) {
        return;
        while (replace_node != root and ((replace_node == nullptr) or replace_node->color == black)) { //(зафикшено) крашится когда сюда нулл птр попадает надо сначала сбалансировать потом удалить ноду
            if (replace_node == replace_node->parent->left) {
                Node* bro = replace_node->parent->right; // брат замещающей ноды
                if (bro->color == red) {
                    bro->color = black;
                    replace_node->parent->color = red;
                    leftRotation(replace_node->parent);
                    bro = replace_node->parent->right;
                }
                if (((bro->left == nullptr) or (bro->left->color == black)) and
                    ((bro->right == nullptr) or (bro->right->color == black))) {
                    bro->color = red;
                    replace_node = replace_node->parent;
                }
                else {
                    if ((bro->right == nullptr) or (bro->right->color == black)) {
                        if (bro->left != nullptr) {
                            bro->left->color = black;
                        }
                        bro->color = red;
                        rightRotation(bro);
                        bro = replace_node->parent->right;
                    }
                    bro->color = replace_node->parent->color;
                    replace_node->parent->color = black;
                    if (bro->right != nullptr) {
                        bro->right->color = black;
                    }
                    leftRotation(replace_node->parent);
                    replace_node = root;
                }
            }
            else {
                Node* bro = replace_node->parent->left;
                if (bro->color == red) {
                    bro->color = black;
                    replace_node->parent->color = red;
                    rightRotation(replace_node->parent);
                    bro = replace_node->parent->left;
                }
                if (((bro->right == nullptr) or (bro->right->color == black)) and
                    ((bro->left == nullptr) or (bro->left->color == black))) {
                    bro->color = red;
                    replace_node = replace_node->parent;
                }
                else {
                    if ((bro->left == nullptr) or (bro->left->color == black)) {
                        if (bro->right != nullptr) {
                            bro->right->color = black;
                        }
                        bro->color = red;
                        leftRotation(bro);
                        bro = replace_node->parent->left;
                    }
                    bro->color = replace_node->parent->color;
                    replace_node->parent->color = black;
                    if (bro->left != nullptr) {
                        bro->left->color = black;
                    }
                    rightRotation(replace_node->parent);
                    replace_node = root;
                }
            }
        }
        if (replace_node != nullptr) {
            replace_node->color = black;
        }
        cout << "Balance complete";
    }
    void printTree(Node* root, int h) {
        if (root != nullptr) {
            printTree(root->left, h + 4);
            for (int i = 1; i <= h; ++i) {
                cout << " ";
            }
            cout << ((root->color == red) ? "\x1b[31m" : "") << root->data << ((root->color == red) ? "\x1b[0m" : "") << "\n";
            printTree(root->right, h + 4);
        }
    }
    void clear(Node* root) {
        if (root != nullptr) {
            clear(root->left);
            clear(root->right);
            delete root;
        }
    }
    void result_record(Node* root, ofstream& fout){
        if (root==nullptr) return;
        result_record(root->left, fout);
        result_record(root->right,fout);
        fout<< root->data << "\n";
    }
};

int main() {
    RBtree tree;
    tree.init();
    ifstream in("names.txt");
    if (in.is_open()) {
        string x, y, z;
        int i = 1; // номер строки
        while (in >> x >> y >> z) {
            Data node;
            node.surname = x;
            node.name = y;
            node.patronymic = z;
            //cout << node << "\n";
            Node* elem = tree.search(node);
            if (elem == nullptr) {
                node.line_num.add(i);
                tree.add(node);
            }
            else {
                elem->data.line_num.add(i);
            }
            ++i;
        }
    }
    in.close();
    tree.printTree(tree.root, 5);
    cout << "------------------------------------" << "\n";
    Data node1 = { "m","h","i" };
    tree.remove(node1);
    tree.printTree(tree.root, 5);
    //cout << "------------------------------------" <<"\n"; 
    //tree.post_order(tree.root);
    ofstream fout("result.txt");
    tree.result_record(tree.root, fout);
    cout << "\n" << "Compiled";

}