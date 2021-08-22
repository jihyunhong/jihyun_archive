#include "double_vector.h"

DoubleVector::DoubleVector(int len) : length(len) {
  vectorElements = new double [len];
  Fill(1.0); // initialize with all values 1.0
}

int DoubleVector::GetLength() const {
  return length;
}

void DoubleVector::Fill(double value) {
  for(int i = 0; i < length; i++) {
    vectorElements[i] = value;
  }
}


// 0. Implement the subscript operator
// DoubleVector vec(3);
// vec[2] should return vec.vectorElements[2]
double& DoubleVector::operator[] (int index){
  return vectorElements[index];
}


// 1. Implement Rule of Three!
// Copy Constructor, Destructor, Assignment Operator
DoubleVector::DoubleVector(const DoubleVector &copy): length(copy.length){
  vectorElements = new double [length];
  for (int i=0; i<length; i++){
    vectorElements[i] = copy.vectorElements[i];
  }
}

DoubleVector::~DoubleVector(){
  delete[] vectorElements;
}

DoubleVector& DoubleVector::operator= (const DoubleVector& rhs){
  // self assignment check
  if (this == &rhs){
    return *this;
  }

  if (rhs.vectorElements != nullptr){
      delete[] vectorElements;
  }
  
  length = rhs.length;
  vectorElements = new double [length];
  for (int i=0; i<length; i++){
    vectorElements[i] = rhs.vectorElements[i];
  }
  return *this;
}


// 2. Implement vector add and vector subtraction operator
// vec + vec // vec - vec
// Assume that the two vectors' length are the same!
DoubleVector operator+(const DoubleVector& lhs, const DoubleVector& rhs){
  DoubleVector ans(lhs.GetLength());

  for (int i=0; i<lhs.GetLength(); i++){
    ans.vectorElements[i] = lhs.vectorElements[i] + rhs.vectorElements[i];
  }
  return ans;
}

DoubleVector operator-(const DoubleVector& lhs, const DoubleVector& rhs){
  DoubleVector ans(lhs.GetLength());
  for (int i=0; i<lhs.GetLength(); i++){
    ans.vectorElements[i] = lhs.vectorElements[i] - rhs.vectorElements[i];
  }
  return ans;
}


// 3. Implement scalar multiplication operator
// Shoulbe work in both ways
// double * vec // vec * double
// ex) 2.0 * (3.0, 4.5, 5.7) 
//     = (3.0, 4.5, 5.7) * 2.0
//     = (6.0, 9.0, 11.4)
DoubleVector operator*(const DoubleVector &rhs, double x){
  DoubleVector ans(rhs.GetLength());
  for (int i=0; i<rhs.GetLength(); i++){
    ans.vectorElements[i] =  x * rhs.vectorElements[i];
  }
  return ans;
}

DoubleVector operator*(double x, const DoubleVector &rhs){
  DoubleVector ans(rhs.GetLength());
  for (int i=0; i<rhs.GetLength(); i++){
    ans.vectorElements[i] =  x * rhs.vectorElements[i];
  }
  return ans;
}


// 4. Implement Output Operator <<
// ex) should be able to perform something like:
// DoubleVector a(5);
// std::cout << a;
// Output format: (%f, %f, %f, %f, %f)
// ex) (12.34, 2, 1.223, 0.0022221)
std::ostream& operator<< (std::ostream &out, const DoubleVector &rhs){
  out << "(";
  for (int i=0; i<rhs.GetLength(); i++){
    out << rhs.vectorElements[i];
    if (i != rhs.length - 1){
      out << ", ";
    }
  }
  out << ")";
  return out;
}
