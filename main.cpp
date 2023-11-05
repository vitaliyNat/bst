#include <iostream>

using namespace std;

class Node {
public:
    Node* parent;
    Node* leftChild;
    Node* rightChild;
    int data;
    int id;

    Node() {
        parent = nullptr;
        leftChild = nullptr;
        rightChild = nullptr;
        data = 0;
        id = 0;
    }
    Node(int value) {
        Node();
        data = value;
    }

    void addLeftChild(int value) {
        leftChild = new Node(value);
        leftChild->parent = this;
    }

    void addRightChild(int value) {
        rightChild = new Node(value);
        rightChild->parent = this;
    }


};

class BST {
private:
    Node* head;
    int size;
    int idQty;
    int high;



    void DFS(Node* node) {
        if(node !=head){
        cout << "Value: " << node->data << ". Id: " << node->id <<". Parent: "<<node->parent->data;
        }else{
            cout << "Value: " << node->data << ". Id: " << node->id <<". Head of BST";
        }
        if (node->leftChild) {
            cout<<". Left Child: " << node->leftChild->data<<". ";}
        if (node->rightChild) {
            cout<<". Right Child: " << node->rightChild->data<<". ";}
        cout<<endl;
        if (node->leftChild) {
            DFS(node->leftChild);}
        if (node->rightChild) {
            DFS(node->rightChild);}

    }
public:


    BST() {
        head = nullptr;
        size = 0;
        idQty = 0;
    }
    BST(int value) {
        head = new Node(value);
        head->id = idQty;
        size = 1;
        idQty++;
    }
    void add(int value) {
        if (size == 0) {
            head = new Node(value);
            head->id = idQty;
            idQty++;
            size++;
            return;
        }
        Node* tmp = this->head;
        int flag = 0;
        while (flag == 0) {
            if (value < tmp->data) {
                if (tmp->leftChild != nullptr) {
                    tmp = tmp->leftChild;
                }
                else {
                    flag = -1;
                }
            }
            else {
                if (tmp->rightChild != nullptr) {
                    tmp = tmp->rightChild;
                }
                else {
                    flag = 1;
                }
            }
        }
        if (flag == -1) {
            tmp->addLeftChild(value);
            size++;
            tmp->leftChild->id = idQty;
            idQty++;
        }
        else {
            tmp->addRightChild(value);
            size++;
            tmp->rightChild->id = idQty;
            idQty++;
        }

    }

    Node* searchNode(int value) {
        auto* tmp = this->head;
        while (tmp != nullptr) {
            if (tmp->data == value) {
                return tmp;
            }
            if (tmp->data < value) {
                tmp = tmp->rightChild;
                continue;
            }
            if (tmp->data > value) {
                tmp = tmp->leftChild;
                continue;
            }
        }

        cout << "Error" << endl;
        return nullptr;


    }



    void deleteNode(Node* value) {

        auto* tmp = value;
        if ((tmp->leftChild == nullptr || tmp->rightChild == nullptr) && tmp == tmp->parent->leftChild) {
            tmp->parent->leftChild = nullptr;
            delete tmp;
            return;
        }
        if ((tmp->leftChild == nullptr || tmp->rightChild == nullptr) && tmp == tmp->parent->rightChild) {
            tmp->parent->rightChild = nullptr;
            delete tmp;
            return;
        }


        auto* tmp2 = tmp->leftChild;
        while (tmp2->rightChild != nullptr) {
            tmp2 = tmp2->rightChild;
        }

        tmp->data = tmp2->data;
        tmp->id = tmp2->id;


        if ((tmp2->leftChild == nullptr || tmp2->rightChild == nullptr) && tmp2 == tmp2->parent->leftChild) {
            tmp2->parent->leftChild = nullptr;
            delete tmp2;
            return;
        }
        if ((tmp2->leftChild == nullptr || tmp2->rightChild == nullptr) && tmp2 == tmp2->parent->rightChild) {
            tmp2->parent->rightChild = nullptr;
            delete tmp2;
            return;
        }
        if (tmp2->leftChild != nullptr) {
            tmp2->parent->rightChild = tmp2->leftChild;
            tmp2->leftChild->parent = tmp2->parent;
        }
        else {
            tmp2->parent->rightChild = nullptr;
        }
        delete tmp2;
        size--;

    }

    void showDFS() {
        DFS(head);
    }



    void BFS() {

        Node* queue = new Node[size];
        int queueQty = 0;
        queue[queueQty] = *head;
        queueQty++;
        int visited = 0;
        auto  tmp = queue[visited];
        while (visited < queueQty) {

            tmp = queue[visited];
            if (tmp.leftChild != nullptr) {
                queue[queueQty] = *tmp.leftChild;
                queueQty++;
            }
            if (tmp.rightChild != nullptr) {
                queue[queueQty] = *tmp.rightChild;
                queueQty++;
            }
            cout << "Value: " << tmp.data << ". Id: " << tmp.id << endl;
            visited++;
        }

    }

    void clear() {
        Node* queue = new Node[size];
        int queueQty = 0;
        queue[queueQty] = *head;
        queueQty++;
        int visited = 0;
        auto  tmp = queue[visited];
        while (visited < queueQty) {

            tmp = queue[visited];
            if (tmp.leftChild != nullptr) {
                queue[queueQty] = *tmp.leftChild;
                queueQty++;
            }
            if (tmp.rightChild != nullptr) {
                queue[queueQty] = *tmp.rightChild;
                queueQty++;
            }
            cout << "Value: " << tmp.data << ". Id: " << tmp.id << endl;
            visited++;
            delete& tmp;
        }
        size = 0;
        head = nullptr;
        idQty = 0;
    }

    void calcHeight(Node* node, int floor) {
        if (node->rightChild == nullptr && node->leftChild == nullptr) {
            if (high < floor) high = floor;
        }
        if (node->leftChild)  calcHeight(node->leftChild, floor + 1);
        if (node->rightChild)  calcHeight(node->rightChild, floor + 1);
    }
    int height() {
        calcHeight(head, 1);
        return high;
    }

    void toString(){
        cout<<"Size:" << size<<endl;
        cout<<"Height: "<<height()<<endl;
        DFS(head);
    }





};


int main() {

    auto* first = new BST();
    first->add(10);
    first->add(15);
    first->add(12);
    first->add(5);
    first->add(30);
    first->add(25);
    first->add(35);
    first->add(7);
    first->add(-2);
    first->add(33);
    first->add(32);

    first->toString();




    return 0;
}
