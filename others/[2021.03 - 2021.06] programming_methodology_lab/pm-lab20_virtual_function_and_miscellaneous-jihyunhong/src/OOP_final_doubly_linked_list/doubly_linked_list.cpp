#include <iostream> 
#include "doubly_linked_list.hpp"
doubly_linked_list::doubly_linked_list(){
    this->head=new Node;
    this->head->next=this->head;
    this->head->prev=this->head;

    this->head->number=1;
}
void doubly_linked_list::insert_forward(int n){
    Node* new_first_node=new Node;
    Node* current_first_node=this->head->next;
    
    new_first_node->number=n;
    
    new_first_node->prev=this->head;
    this->head->next=new_first_node;

    new_first_node->next=current_first_node;
    current_first_node->prev=new_first_node;
}
void doubly_linked_list::remove(Node* node_ptr){ //remove the node pointed by node_ptr
    Node* prev_node=node_ptr->prev;
    Node* next_node=node_ptr->next;
    prev_node->next=next_node;
    next_node->prev=prev_node;
    delete node_ptr;
}
Node* doubly_linked_list::search_first(int n){
    Node* temp_node=this->head->next;
    while(temp_node!=this->head){
        if(temp_node->number==n){
            return temp_node;
        }
        temp_node=temp_node->next;
    }
    return NULL;
}
void doubly_linked_list::print_list_forward(){
    std::cout<<"doubly linked list: ";
    bool first=true;
    Node* temp_node=this->head->next;
    while(temp_node!=this->head){
        if(first){
            std::cout<<(temp_node->number);
            first=false;
        }
        else{
            std::cout<<"->"<<(temp_node->number);
        }
        temp_node=temp_node->next;
    }
    std::cout<<std::endl;
}

//shallow copy the linked list..
doubly_linked_list::~doubly_linked_list(){
    if(this->head->number==1){
        Node* temp_node=this->head->next;
        while(temp_node!=this->head){
            temp_node=temp_node->next;
            delete temp_node->prev;
        }
        delete this->head;
    }
    else{
        (this->head->number)--;
    }
}
doubly_linked_list::doubly_linked_list(doubly_linked_list& d_list){
    this->head=d_list.head;
    (this->head->number)++;
}
doubly_linked_list& doubly_linked_list::operator=(doubly_linked_list const& d_list){
    if(this!=&d_list){
        if(this->head->number==1){
            Node* temp_node=this->head->next;
            while(temp_node!=this->head){
                temp_node=temp_node->next;
                delete temp_node->prev;
            }
            delete this->head;
        }
        else{
            (this->head->number)--;
        }
        this->head=d_list.head;
        (this->head->number)++;
    }
    return *this;
}