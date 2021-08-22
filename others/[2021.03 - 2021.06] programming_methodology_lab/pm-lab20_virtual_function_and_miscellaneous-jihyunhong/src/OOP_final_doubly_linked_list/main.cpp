#include <iostream>
#include "doubly_linked_list.hpp"
int main(){
    doubly_linked_list d_list;
    d_list.insert_forward(5);
    d_list.insert_forward(3);
    d_list.insert_forward(8);
    d_list.insert_forward(2);
    d_list.print_list_forward();
    //2->8->3->5

    std::cout<<d_list.search_first(10)<<std::endl;
    Node* temp_node=d_list.search_first(5);
    std::cout<<temp_node<<std::endl;
    temp_node=d_list.search_first(2);
    std::cout<<temp_node<<std::endl;
    temp_node=d_list.search_first(3);
    std::cout<<temp_node<<std::endl;

    d_list.insert_forward(7);
    d_list.insert_forward(3);
    temp_node=d_list.search_first(3);
    d_list.print_list_forward();
    //7->2->8->3->5
    d_list.remove(temp_node);
    temp_node=d_list.search_first(3);
    d_list.remove(temp_node);
    temp_node=d_list.search_first(5);
    d_list.remove(temp_node);
    d_list.print_list_forward();
    //7->2->8

    doubly_linked_list d_list1;
    std::cout<<d_list1.head->number<<std::endl;
    //1
    d_list1=d_list;
    std::cout<<d_list.head->number<<std::endl;
    //2
    std::cout<<d_list1.head->number<<std::endl;
    //2
    doubly_linked_list d_list2=d_list1;
    std::cout<<d_list.head->number<<std::endl;
    //3
    d_list2.print_list_forward();
    //7->2->8
    d_list.insert_forward(16);
    d_list2.print_list_forward();
    //16->7->2->8
    temp_node=d_list1.search_first(7);
    d_list.remove(temp_node);
    d_list2.print_list_forward();
    //16->2->8
    return 0;
}
