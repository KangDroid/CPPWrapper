#include <iostream>

using namespace std;

class Node {
    private:
        int data;
        Node * tail;
        Node * head;
    public:
        Node() {
            this->tail = nullptr;
            this->head = nullptr;
            this->data = 0;
        }
        int getData() {
            return this->data;
        }
        void setData(int a) {
            this->data = a;
        }
        Node * getTail() {
            return this->tail;
        }
        Node * getHead() {
            return this->head;
        }
        void setTail(Node *n) {
            this->tail = n;
        }
        void setHead(Node *n) {
            this->head = n;
        }
};

class NodeController {
    public:
        Node * start;
        Node * backup_tmp;

        void insertData(int a) {
            if (start == nullptr) {
                // First run
                start = new Node();
                start->setData(a);
                backup_tmp = start;
            } else {
                Node *tmp_new = new Node();
                tmp_new->setData(a);

                tmp_new->setTail(start);
                tmp_new->setHead(start->getHead());
                start->setHead(tmp_new);
                start = start->getHead();
            }
        }

        void insertDataSort(int a) {
            if (start == nullptr) {
                insertData(a);
            } else {
                Node *nxt = backup_tmp;
                Node *n_tmp = new Node();
                n_tmp->setData(a);

                while (true) {
                    if (nxt->getData() >= n_tmp->getData()) {
                        Node *bef = nxt->getTail();
                        if (bef == nullptr) {
                            // First Node;
                            start = n_tmp;
                            start->setTail(nullptr);
                            start->setHead(nxt);
                            nxt->setTail(start);
                            backup_tmp = start;
                        } else {
                            bef->setHead(n_tmp);
                            n_tmp->setTail(bef);
                            n_tmp->setHead(nxt);
                            nxt->setTail(n_tmp);
                        }
                        break;
                    } else {
                        // For the case nxt->getData() < n_tmp->getData()
                        // nxt->getHead() Might be null because this is CIRCULAR LINKED LIST
                        // So if nxt->getHead() is null and n_tmp is not linked, than automaticall link n_tmp after nxt.
                        if (nxt->getHead() == nullptr) {
                            n_tmp->setHead(nxt->getHead());
                            nxt->setHead(n_tmp);
                            n_tmp->setTail(nxt);
                            break;
                        } else {
                            nxt = nxt->getHead();
                        }
                    }
                }
            }
        }

        void deleteDataByKey(int key) {
            Node *tmp = backup_tmp;
            while (tmp != nullptr) {
                if (tmp->getData() == key) {
                    //Delete
                    // Case - By Case - If Node is on First one, If Node is on Middle one, If Node is End one
                    if (tmp->getTail() == nullptr) {
                        // If Node is the First one
                        Node * nxt = tmp->getHead();
                        if (nxt != nullptr) {
                            nxt->setTail(nullptr);
                        }
                        backup_tmp = nxt;
                    } else if (tmp->getHead() == nullptr) {
                        // If Node is the last one
                        Node * prev = tmp->getTail();
                        prev->setHead(tmp->getHead());
                    } else {
                        // If Node is on Middle one
                        Node * prev = tmp->getTail();
                        Node * next = tmp->getHead();
                        prev->setHead(next);
                        next->setTail(prev);
                    }
                    delete tmp;
                    return;
                }
                tmp = tmp->getHead();
            }
            cout << "Key is NOT Found on the list." << endl;
        }
        
        void show() {
            Node *tmp = backup_tmp;
            while (tmp != nullptr) {
                cout << tmp->getData() << endl;
                tmp = tmp->getHead();
            }
        }
};

int main(void) {
    NodeController ndc;
    for (int i = 0; i < 50; i++) {
        ndc.insertDataSort(rand() % 100);
    }
    ndc.show();
    return 0;
}