#include <iostream>
class Node{
public:
    int number;
    Node* next;
    Node* prev;
};

class doubly_linked_list{
public:
    //head node
    Node* head;
    
    doubly_linked_list();
    
    //insert, remove, search and print
    void insert_forward(int n);
    void remove(Node* node_ptr);
    Node* search_first(int n);
    void print_list_forward();

    //rule of three
    ~doubly_linked_list();
    doubly_linked_list(doubly_linked_list& d_list);
    doubly_linked_list& operator=(doubly_linked_list const& d_list);
};
