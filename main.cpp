#include <iostream>
#include <chrono>

using namespace std;

template <class T>
class Node {
public:
    Node* parent;
    Node* leftChild;
    Node* rightChild;
    T data;
    int id;

    Node() {
        parent = nullptr;
        leftChild = nullptr;
        rightChild = nullptr;
        data = 0;
        id = 0;
    }
    Node(T value) {
        Node();
        data = value;
    }

    void addLeftChild(T value) {
        leftChild = new Node(value);
        leftChild->parent = this;
    }

    void addRightChild(T value) {
        rightChild = new Node(value);
        rightChild->parent = this;
    }


};

template <class T>
class BST {
private:
    Node<T>* head;
    int size;
    int idQty;
    int high;



    void DFS(Node<T>* node) {
        if (node != head) {
            cout << "Value: " << node->data << ". Id: " << node->id << ". Parent: " << node->parent->data;
        }
        else {
            cout << "Value: " << node->data << ". Id: " << node->id << ". Head of BST";
        }
        if (node->leftChild) {
            cout << ". Left Child: " << node->leftChild->data << ". ";
        }
        if (node->rightChild) {
            cout << ". Right Child: " << node->rightChild->data << ". ";
        }
        cout << endl;
        if (node->leftChild) {
            DFS(node->leftChild);
        }
        if (node->rightChild) {
            DFS(node->rightChild);
        }

    }
public:


    BST() {
        head = nullptr;
        size = 0;
        idQty = 0;
    }
    BST(T value) {
        head = new Node(value);
        head->id = idQty;
        size = 1;
        idQty++;
    }
    void add(int value) {
        if (size == 0) {
            head = new Node<T>(value);
            head->id = idQty;
            idQty++;
            size++;
            return;
        }
        Node<T>* tmp = this->head;
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

    Node<T> * searchNode(int value) {
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



    void deleteNode(Node<T>* value) {

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

        Node<T>* queue = new Node<T>[size];
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
        Node<T>* queue = new Node<T>[size];
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

    void calcHeight(Node<T>* node, int floor) {
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

    void toString() {
        cout << "Size:" << size << endl;
        cout << "Height: " << height() << endl;
        cout << "Head: " << head->data;
        //DFS(head);
    }





};

int getRandom() {
    return rand() % 100000;
}



int main() {

    auto* first = new BST<int>();
    const int Qty = 100;


    //Add begin
    auto t1 = chrono::high_resolution_clock::now();


    for (int i = 0; i < Qty; i++) {
        first->add(getRandom());
    }

    auto t2 = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    printf("Add  %d elements: Time measured: %.3d nanoseconds.\n", Qty, duration.count());


    //Search element

    int hits = 0;
    t1 = chrono::high_resolution_clock::now();


    auto t1_temp = chrono::high_resolution_clock::now();
    auto t2_temp = chrono::high_resolution_clock::now();
    auto  duration_temp = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);

    long duration_temp_data[Qty];
    auto worst_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);

    for (int i = 0; i < Qty; i++) {
        t1_temp = chrono::high_resolution_clock::now();


        Node<int>* so = first->searchNode(getRandom());
        if (so != nullptr) {
            hits++;
        }
        delete so;




        t2_temp = chrono::high_resolution_clock::now();
        duration_temp = std::chrono::duration_cast<std::chrono::nanoseconds>(t2_temp - t1_temp);
        if (duration_temp > worst_duration) {
            worst_duration = duration_temp;
        }
        duration_temp_data[i] = duration_temp.count();


    }

    t2 = chrono::high_resolution_clock::now();
    long sum = 0;

    for (int i = 0; i < Qty; i++) {
        sum += duration_temp_data[i];
    }
    long average = sum / Qty;
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    printf("Searched  %d elements from %d : Time measured: %.3d nanoseconds.\n. Average time %.3d. Worst time %.d3", hits, Qty, duration.count(), average, worst_duration.count());






    return 0;
}
