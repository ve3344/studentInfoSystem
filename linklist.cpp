#pragma once
#include<functional>
using namespace std;

template< typename T>
class Linklist {
    class Node {
    public:
        Node *next;
        T *data;
        Node(T *dat):data(dat) {
        }
    };
    Node *head=NULL,*tail=NULL;
    int size=0;
public:
    Linklist() {

    }
    ~Linklist() {
        clear();
    }
    bool empty() {
        return head==NULL;
    }
    T* remove(int index  ) {
        if (index>=size) {
            return NULL;
        }
        if (index==0) {
            return popFront();
        }
        Node *position=head,*last;
        while (position&&index--) {
            last=position;
            position=position->next;

        }
        last->next=position->next;
        T *value=position->data;
        delete position;
        size--;
        return value;
    }
    T* removeIf(function< bool (int,T*) > condition) {
        Node *position=head,*last;
        int index=0;
        if (condition(index,position->data)) {
            return popFront();
        }

        while (position) {
            last=position;
            position=position->next;
            index++;
            if (condition(index,position->data)) {
                break;
            }

        }
        last->next=position->next;
        T *value=position->data;
        delete position;
        size--;
        return value;

    }
    void insert(int index, T* value) {
        if (index>size||value==NULL) {
            return;
        }

        Node *node=new Node(value);
        if (index==0) {
            pushFront(value);
        }
        Node *position=head,*last;
        while (position&&index--) {
            last=position;
            position=position->next;
        }
        last->next=node;
        node->next= position;
        size++;

    }
    void clear() {
        if (head) {
            destroy([](int p,T* value) {
                if (value) {
                    delete value;
                }
            });
        }
    }

    void pushFront(T* value) {
        if (value==NULL) {
            return;
        }
        Node *node=new Node(value);
        node->next=head;
        head=node;
        size++;
    }
    T *popFront() {
        Node *node=head;
        if (head) {
            head=node->next;
            node->next=NULL;
            size--;
        }
        return node->data;
    }
    T *popBack() {
        T *value=NULL;
        Node *position=head,*last=NULL;
        if (head==NULL) {
            return NULL;
        }
        if (head->next==NULL) {
            value=position->data;
            delete head;
            head=NULL;
            return value;
        }

        while (position->next) {
            last=position;
            position=position->next;
        }
        value=position->data;
        delete position;
        last->next=NULL;
        return value;
    }
    void sort(function< int (T*,T*) > comparetor) {
        if (head==NULL) {
            return;
        }
        T *temp;
        for (Node*i=head; i!=NULL; i=i->next) {
            for (Node*j=i->next; j!=NULL; j=j->next) {
                if (comparetor(i->data,j->data)>=0) {
                    temp=i->data;
                    i->data=j->data;
                    j->data=temp;

                }

            }

        }

    }
    void pushBack(T* value) {
        if (value==NULL) {
            return;
        }
        Node *node=new Node(value);
        if (node) {
            node->next=NULL;
        } else {
            return;
        }
        if (head) {
            Node* position=head;
            while (position->next) {
                position=position->next;
            }
            position->next=node;
        } else {
            head=node;

        }

        size++;
    }
    T* get(int pos) {

        if (pos>size) {
            return NULL;
        }
        Node *position=head;
        int index=0;
        while ( position) {
            if (index==pos) {
                return position->data;
            }
            position=position->next;
            index++;
        }
        return NULL;
    }
    void seekList(function< bool (int,T*) > action) {
        Node *position=head;
        int index=0;
        while ( position) {
            if (action(index,position->data)) {
                break;
            }
            position=position->next;
            index++;
        }
    }

    void destroy(function< void(int,T*) > onItemDelete) {
        Node *position=head, *freeNode=NULL;
        int index=0;
        while (position) {
            freeNode=position;
            position=position->next;
            onItemDelete(index,freeNode->data);

            delete(freeNode);
            index++;
        }
        head=NULL;
    }
    void append(Linklist& other) {
        pushBack(other.head->data);
        size+= (other.size-1);
        other.head=NULL;
        other.size=0;
    }
    T* findMax(function< int (T*,T*) > comparetor) {
        Node *position=head;
        T* max=position?position->data:NULL;

        while ( position) {
            if (comparetor(max,position->data)<0) {
                max=position->data;
            }
            position=position->next;
        }

        return max;
    }
    int length() {
        return size;
    }
};
