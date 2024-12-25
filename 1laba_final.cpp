#include <iostream>
using namespace std;

struct node{
    int data;
    node* next = nullptr;
};
void print_list (node *&head){
    if(head == nullptr){
        cout<< "There are no elements in list \n";
    } else {
        node* p = head;
        do{
            cout<< p->data<<" ";
            p = p->next;
        }while(p != head);
        cout<<"\n";
    }
}
void init(int value, node *&head){ 
    head = new node;
    head ->data = value;
    head ->next = head;
}
void add(int value, node *&head){ // допилить
    if (head == nullptr){
        init(value, head);
    } else if(value >=  head->data){
        node* current = head;
        while(current->next != head){
            current = current->next;
        }
        node* p = new node;
        p->data = value;
        p->next = head;
        current->next = p;
        head = p;
    } else {
        node* current = head;
        while(value < current->next->data and current->next != head ){
            current = current->next;
        }
            node* h = new node;
            h->data = value;
            h->next = current->next;
            current->next = h;
        }
}
void srch_value(int value, node *&head){
    if (head == nullptr){
        cout<<"There are no elements in list \n";
        return;
    }
    node* current = head;
    bool fl = false; // флаг для проверки наличия значения
    int i = 1;
    do {
        if(current->data == value){
            cout<<i << " ";
            fl = true;
        }
        current = current->next;
        i++;
    }while(current != head);
    if(fl == false){
        cout<<"There is no such value" << "\n";
    }
}

void del(int value, node *&head){
    if (head==nullptr){
        cout << "There is are elements in list \n";
        return;
    }
    bool fl = false;
     if (head ->next == head){
        delete head;
        head = nullptr;
     } else {
        node* current = head;
        node* p = head->next; // указатель на следующий элемент
        while(p->next->data != value){
            current = p;
            p = p->next;
            if (current == head and fl == false){
                cout << "There is no such value \n";
                return;
            }
        }
        p = p->next;
        node* h = current->next;
        if (h == head){
            delete h;
            head = p;
            current->next = head;
            fl = true;
        } else if(p->next->data == value){
            while(p->data == value){
                delete h;
                current->next = p;
                h = p;
                p = p->next;
                h->next = p;
                if (head == head ->next){
                    delete head;
                    head = nullptr;
                    return;
                }
            }
            fl = true;
        } else {
            delete h;
            current->next = p;
            fl = true;
        }
    }
}
void del_vals(int value, node*& head){
    bool fl = false;
    if (head == nullptr ){
        cout << "Error, there are no elements list \n";
        fl = true;
    } else if(head->next == head and head->data == value){
        delete head;
        head = nullptr;
        fl = true;
    } else {
        node* current = head;
        node* p = current->next;
        do{
            if (p->data == value){
                node* h = p;
                p= p->next;
                if (h == head){
                    delete h;
                    head = p;
                    current->next = p;
                } else {
                delete h;
                current->next = p;
                }
                fl = true;
                continue;
            }
            current = p;
            p = p->next;
        } while (p!= head);
        if (head->next == head and head->data == value){
            delete head;
            head = nullptr;
            fl = true;
        }
        if (fl == false){
            cout << "There is no such element \n";
        }
    }
}
void intersection(node*& head1, node*& head2, node*&head3){
    bool fl = false;
    if (head1 == nullptr or head2 == nullptr){
        cout << "Error, there is no elements in list \n";
        return;
    }
    node* current1 = head1;
    node* current2 = head2;
    node* p1 = current1->next;
    node* p2 = current2->next;
    
    do {
      //  cout << current1->data << " " << current2->data << " " <<p1->data << " "<< p2->data<<  "\n";
       if (current1->data > current2->data ){
            if (p1 == head2){
                current2= head2;
            }
            current1 = current1->next;
            p1 = current1->next;
           // cout<<"1 ";
       } else if (current2->data > current1->data){
            if (p2 == head2){
                current1 = head1;
            }
            current2 = current2->next;
            p2 = current2->next;
       } else if (current1->data == current2->data){ 
            add(current1->data, head3);
            fl = true;
            current1 = current1->next;
            p1 = current1->next;
            current2 = current2->next;
            p2 = current2->next;
       }
    } while((current1 != head1) or (current2 != head2));
    if (fl == false) {
        cout << "There is no intersection \n";
    }
}
void clear(node *&head){
    if (head==nullptr){
        cout << "There are no elements in list \n";
        return;
    }
    node* current = head;
    node* p = current->next;
    while (current->next != head){
        current = current->next;
    }
    node* end = current;
    current = head;
    while (p != end){
        delete current;
        current = p;
        p= p->next;
    }
    delete end;
    head = nullptr;
    current = nullptr;
    p = nullptr;
    end = nullptr;
}
int get_length(node *&head){
    int list_legth = 0;
    if(head == nullptr){
        cout<< "There is no elements in list \n";
    } else {
        node* p = head;
        do{
            list_legth++;
            p = p->next;
        }while(p != head);
    }
    return list_legth;
}
int summ(int start_index, int end_index, node *&head){
    node *p = head;
    int result = 0;
    for (int i = 1; i != start_index; ++i){
        p = p->next;
    }
    //cout << p->data << " "<< p->next->data <<  "\n";
    // if (start_index == end_index){
    //     p = p->next;
    // }
    for (int i = start_index; i <= end_index; ++i) {
       // cout << p->data << " ";
        result += p->data;
        p = p->next;
    }   
    cout << endl;
    return result;
}
void optimise(node *&head){
    int length = get_length(head);
    int a, b;
    if (length % 2 == 0){
        a = 1;
        b = length /2;
        a = summ(a,b, head);
        b = summ(b +1, length, head);
        
        clear(head);
        add(a,head);
        add(b,head);
        
    } else {
        b = length/2;
        a = 1;
        a = summ(a, b, head);
        b= summ(b+1,length-1,head);
        int c = summ(length,length, head);
        clear(head);
        add(a,head);
        add(b,head);
        add(c, head);
    }
}
int main(){
    node* head1 = nullptr; 
    node* head2 = nullptr;
    node* head3 = nullptr;
    init(9, head1);
    add(8,head1);
    // add(7,head1);
    // add(5,head1);
    //add(10, head1);
   // add(6, head1);
    // add(9, head1);
    // add(3, head1); 
    // add(5, head1);
    // add(5,head1);
    // add(5,head1);
    // del(9, head1);
    cout << "List1: ";
    print_list(head1);
    del(1, head1);
    print_list(head1);
    // cout << endl;
    // optimise(head1);
    // print_list(head1);
//     srch_value(9, head1);
//     del(8, head1);
//     add(2, head1);
//     add(4, head1);
//     cout << "List1 after deleting elements: ";
//     print_list(head1);
//     add(4, head2);
//     add(10, head2);
//     add(7, head2);
//     add(2, head2);
//     cout << "List2: ";
//     print_list(head2);
//     intersection(head1, head2, head3);
//     cout << "Intersection List: "; 
//     print_list(head3);
//     clear(head1);
//     clear(head2);
//     clear(head3);
 }