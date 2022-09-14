#include <iostream> 
#include <iomanip>
#include <fstream>


using namespace std;


struct Node {
    int val;
    Node* next;
    Node* previous;

    Node(unsigned int _val) :val(_val), next(nullptr), previous(nullptr) {}

    Node* get_next() {
        return this->next;
    }

    Node* get_previous() {
        return this->previous;
    }
};


struct list {
    Node* first;
    Node* last;

    list() : first(nullptr), last(nullptr) {}


    bool is_empty() {
        return first == nullptr;
    }



    void push_back(int _val) {
        Node* p = new Node(_val);
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        p->previous = last;
        last = p;
    }

    void push_first(int _val) {
        Node* p = new Node(_val);
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        first->previous = p;
        p->next = first;
        first = p;
    }


    void push_index(int index, int _val) {
    
        if (is_empty()) return;
        Node* p = first;
        Node* _new=new Node(_val);

        for (int i = 0; i < index-1; i++) {
            p = p->get_next();
        }

        _new->next = p; _new->previous = p->previous;

        if (_new->previous != nullptr)p->previous->next = _new;
        p->previous = _new;

    }


    void remove_first() {
        if (is_empty()) return;
        Node* p = first;
        first = p->next;
        delete p;
        if (first) first->previous = nullptr;
    }

    void remove_last() {
        if (is_empty()) return;
        Node* p = last;
        last = p->get_previous();
        delete p;
        if (last) last->next = nullptr;
    }


    void remove_index(int index) {
        if (is_empty()) return;
        Node* p = first;
        Node* p2;

        for (int i = 0; i < index-2; i++) {
            p = p->get_next();
        }

        p2 = p->get_next();
        p->next = p->next->next;
        p = p->get_next();
        p2->previous = p->previous;

        delete p2;
    }

    void remove_all() {
        if (is_empty()) return;

        Node* p = first;

        while (p) {
            auto t = p;
            p = p->get_next();
            delete t;
        }
        first = nullptr;
        last = nullptr;
    }


    void print() {
        if (is_empty()) return;
        Node* p = first;

        while (p) {
            cout << p->val;
            p = p->get_next();
        }
        cout << endl;
    }

    int get(int index) {

        if (is_empty()) exit(1);
        Node* p = first;

        for (int i = 0; i < index - 1; i++) {
            p = p->get_next();

            if (!p) { cout << "length is too big!"<<endl; exit(1); }
        }

        return p->val;
    }

    void replace(int index, int _val) {

        if (is_empty()) return;
        Node* p = first;

        for (int i = 0; i < index - 1; i++) {
            p = p->get_next();

            if (!p) { cout << "length is too big!" << endl; return; }
        }
        p->val = _val;

    }

    int size() {
        int i = 0;
        Node* p = first;

        if (is_empty()) return 0;

        while (p) { p = p->get_next(); i++; }

        return i;
    }


    bool areListIn(list SmallList) {                 //insert smaller list

        bool Val_in;

        Node* p1;
        Node* p2 = SmallList.first;
        int searchin_val;

        if (is_empty()) return 0;
        if (SmallList.is_empty()) return 0;


        while (p2) {

            searchin_val = p2->val;
            Val_in = false;
            p1 = first;
            while (p1) {

                if (searchin_val == p1->val) { Val_in = true; break; }

                p1 = p1->get_next();
            }

            if (Val_in == false) return false;

            p2 = p2->get_next();


        }
        return true;
    }

};


int main() {


    list main_list, second_list;

    cout << "Given 2 lists(created by push_back, withdrown by print): " << endl;
    for (int i = 0; i < 10; i+=2) {
       main_list.push_back(i);
    }

    second_list.push_back(2);
    second_list.push_back(3);
    second_list.push_back(4);


    main_list.print();
    second_list.print();

    cout << "Check for availability second list in first list " << endl;
    cout << "result " << main_list.areListIn(second_list)<<endl;
    cout << "let's get the second value from " << main_list.get(2) << endl;
    cout << "check for emptiness  " << main_list.is_empty()<<endl;
    cout << " adding 7 to first place ";
    main_list.push_first(7);
    main_list.print();
    cout << " adding a 5 to 5th place ";
    main_list.push_index(5, 5);
    main_list.print();
    cout << "removing first value ";
    main_list.remove_first();
    main_list.print();
    cout << "removing last value ";
    main_list.remove_last();
    main_list.print();
    cout << "changing 3rd value to 9 ";
    main_list.replace(3, 9);
    main_list.print();
    cout << "checking a size of list ";
    main_list.size();
    cout << "deleting all values";
    main_list.remove_all();
    main_list.print();



}