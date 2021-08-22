#ifndef REVIEW_H
#define REVIEW_H

#include <iostream>

class Review
{ 
    private:
        int* array;
        int len;
    public: 
        Review();
        Review(int* array, int len);
        
        // copy constructor
        Review(const Review &r);
        
        // assignment operator
        Review& operator= (const Review &r);
        void view();
        ~Review();
}; 

#endif