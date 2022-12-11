#include <iostream> 
#include <fstream>
#include <string>
#include <map>


using namespace std;

struct leaf {
    int freq;
    string symb;
    int code = 0;
};

map <char, int> mp;



class Node {
private:
    leaf _value;
    Node* left;
    Node* right;
    Node* parent;

public:
    Node(leaf value) {
        _value = value;
        left = NULL;
        right = NULL;
        parent = NULL;
    } Node() :_value(), left(NULL), right(NULL), parent(NULL) {
    }

    void SetLeft(Node* ptr) {
        left = ptr;
    }

    void SetRight(Node* ptr) {
        right = ptr;
    }

    void SetParent(Node* ptr) {
        parent = ptr;
    }


    void SetValue(leaf iValue) {
        _value = iValue;
    }

    leaf GetValue() {
        return _value;
    }

    Node* GetLeft() {
        return left;
    }

    Node* GetRight() {
        return right;
    }

    Node* GetParent() {
        return parent;
    }



};

class tree {
private:
    Node* head;

   

public:

    



    tree() :head(NULL) {
    } tree(leaf value) {
        Node* node = new Node(value);
        head = node;
    }

    tree(Node* node) {
        head = node;
    }

    Node* GetHead() {
        return head;
    }

    void AddRoot(leaf value) {
        if (head == NULL) {
            Node* node = new Node(value);
            head = node;
            return;
        }
    }

   

    void Add(leaf value, leaf parent) {      //adding new node

        if (head == NULL) {
            Node* node = new Node(value);
            head = node;
            return;
        }

        Node* node = findInorder(head, parent);   
        Node* n = new Node(value);
        if (node->GetLeft() == NULL) {
            node->SetLeft(n);
            n->SetParent(node);
        }
        else { node->SetRight(n); n->SetParent(node); }
        return;
    }

    

    Node* findInorder(Node* n, leaf node) {    //find node  by inorder detour

        if (n != nullptr) {

            if (node.symb == n->GetValue().symb) {

                return n;
            }

            auto tmp = findInorder(n->GetLeft(), node);
            if (tmp && tmp->GetValue().symb == node.symb)
                return tmp;

            tmp = findInorder(n->GetRight(), node);
            if (tmp && tmp->GetValue().symb == node.symb)
                return tmp;
        }
    }


    Node* findInorderLetter(Node* n, string symb) { //find node with symb by inorder detour

        if (n != nullptr) {


            if (symb == n->GetValue().symb) {

                return n;
            }
            Node* tmp;

            if (n->GetLeft()) {
                tmp = findInorderLetter(n->GetLeft(), symb);
                if (tmp && tmp->GetValue().symb == symb)
                    return tmp;
            }

            if (n->GetRight()) {
                tmp = findInorderLetter(n->GetRight(), symb);
                if (tmp && tmp->GetValue().symb == symb)
                    return tmp;
            }
        }
        return NULL;
    }


    void inorder(Node* n) {
        if (n != nullptr) {
            inorder(n->GetLeft());

            cout << n->GetValue().symb<<":"<< n->GetValue().freq<<" code="<< n->GetValue().code << endl;

            inorder(n->GetRight());
        }
    }

    void inorderPrint() {
        inorder(head);
        std::cout << "\n";
    }

    void getLevelCount(Node* n, int count, int& max_count) const {
        if (n == nullptr)
            max_count = (max_count > count) ? max_count : count;
        else {
            count++;
            getLevelCount(n->GetLeft(), count, max_count);
            getLevelCount(n->GetRight(), count, max_count);
        }
    }



};


void insertSort(leaf numbers[], int size) {

    for (int i = 1; i < size; i++)
        for (int j = i; j > 0 && numbers[j - 1].freq < numbers[j].freq; j--)
            swap(numbers[j - 1], numbers[j]);

    return;
}

string encryptCode(string text, tree root) {

    string encryptedCode;

    for (int i = text.length() - 1; i != -1; i--) {

        Node* n = root.findInorderLetter(root.GetHead(), string(1,text[i]));   
        while (n->GetValue().code != 7) {
            encryptedCode += to_string(n->GetValue().code);
            n = n->GetParent();
        }

    }

    reverse(encryptedCode.begin(), encryptedCode.end());

    return encryptedCode;
};


string decryptCode(string text, tree root) {

    string decryptedCode="";


    for (int i = 0; i < text.length(); i) {

        Node* n = root.GetHead();
        while (n->GetValue().symb.length() != 1) {

            if (to_string(n->GetLeft()->GetValue().code) == string(1,text[i])) {
                n = n->GetLeft();
            }
            else  n = n->GetRight();

            
            i++;

        }

        decryptedCode += n->GetValue().symb;
    }






    return decryptedCode;
}


int main() {
    string text;
    string allLetters="";

    cout << "write a text: ";
    getline(std::cin, text);
    cout << endl;

    leaf list[100];
    int lenList=0;
    int allFreq=0;

   



    for (int i = 0; i < text.length(); i++) {                       //doing a map of letters and their freq
        mp[text[i]] = count(text.begin(), text.end(), text[i]);
    }

    map <char, int> ::iterator it = mp.begin();

    for (it; it != mp.end(); it++) {
        list[lenList].freq = it->second;
        allFreq += list[lenList].freq;
        list[lenList++].symb = it->first;                   //input in array map values
    }

    if (lenList < 3) {                          //ñondition condition for more than 2 unique letters in the text
        cout << "Why are u ...?" << endl;
        return 0;
    }

    cout << "___________________________________________" << endl;
    insertSort(list, lenList);              //sort array by frequency


    for (int i = 0; i < lenList; i++)allLetters += list[i].symb; //making a var with all letters



    tree root;
    leaf noda;
    noda.symb = allLetters;
    noda.freq = allFreq;
    noda.code = 7;
    root.AddRoot(noda);

    Node* current = root.GetHead(); //set root
    current->GetValue().symb;

    noda.symb = list[0].symb + list[1].symb;
    noda.freq= list[0].freq + list[1].freq;
    noda.code = 1;
    Node* n = new Node(noda);
    current->SetLeft(n);            // set most usefull letter
    n->SetParent(current);

    noda.symb = list[0].symb;
    noda.freq = list[0].freq;
    noda.code = 1;
    n = new Node(noda);
    current->GetLeft()->SetLeft(n);
    n->SetParent(current->GetLeft());

    noda.symb = list[1].symb;
    noda.freq = list[1].freq;
    noda.code = 0;
    n = new Node(noda);
    current->GetLeft()->SetRight(n);
    n->SetParent(current->GetLeft());

    allLetters.erase(0,2);
    allFreq -= (list[1].freq + list[0].freq);

    noda.symb = allLetters;
    noda.freq = allFreq;
    noda.code = 0;
    n = new Node(noda);
    current->SetRight(n);           //set another letters
    n->SetParent(current);

    current=current->GetRight();
    

    int i = 2;

    while (allLetters.length()!=1) {



        noda.symb = list[i].symb;
        noda.freq = list[i].freq;
        
        if (allFreq - list[i].freq >= list[i].freq)noda.code = 0;
        else noda.code = 1;

        n = new Node(noda);
        current->SetLeft(n);
        n->SetParent(current);

        allFreq -= list[i].freq;

        noda.symb = allLetters.erase(0, 1);
        noda.freq = allFreq;

        if (noda.code==1)noda.code = 0;
        else noda.code = 1;

        n = new Node(noda);
        current->SetRight(n);
        n->SetParent(current);

        current=current->GetRight();
        i++;
    }

   





    string encryptedCode = encryptCode(text, root);

    cout << encryptedCode << endl;
    cout << decryptCode(encryptedCode, root)<<"\n\n";
    return 0;
}


