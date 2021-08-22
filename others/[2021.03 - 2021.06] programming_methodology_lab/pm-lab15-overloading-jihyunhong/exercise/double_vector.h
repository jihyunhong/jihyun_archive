#ifndef DOUBLE_VECTOR_H_
#define DOUBLE_VECTOR_H_

#include <string>
#include <sstream>

// This class is a vector containing double values
class DoubleVector {
public:
  DoubleVector(int len);

  // getter
  int GetLength() const;
  
  // fill the vector with the same value 
  void Fill(double value);

  // 0. Implement the subscript operator
  double& operator[](int index);

  // 1. Implement Rule of Three!
  DoubleVector(const DoubleVector &copy);
  ~DoubleVector();
  DoubleVector& operator= (const DoubleVector &rhs);

  // 2. Implement vector add and vector subtraction operator
  friend DoubleVector operator+(const DoubleVector &lhs, const DoubleVector &rhs);
  friend DoubleVector operator-(const DoubleVector &lhs, const DoubleVector &rhs);


  // 3. Implement scalar multiplication operator
  friend DoubleVector operator*(const DoubleVector &rhs, double x);
  friend DoubleVector operator*(double x, const DoubleVector &rhs);


  // 4. Implement Output Operator <<
  friend std::ostream& operator<< (std::ostream &out, const DoubleVector &DoubleVector);

private:
  int length;
  double* vectorElements;
};
 
  // 0. Implement the subscript operator
  // DoubleVector vec(3);
  // vec[2] should return vec.vectorElements[2]

  // 1. Implement Rule of Three!
  // Copy Constructor, Destructor, Assignment Operator

  // 2. Implement vector add and vector subtraction operator
  // vec + vec // vec - vec
  // Assume that the two vectors' length are the same!

  // 3. Implement scalar multiplication operator
  // Shoulbe work in both ways
  // double * vec // vec * double
  // ex) 2.0 * (3.0, 4.5, 5.7) 
  //     = (3.0, 4.5, 5.7) * 2.0
  //     = (6.0, 9.0, 11.4)

  // 4. Implement Output Operator <<
  // ex) should be able to perform something like:
  // DoubleVector a(5);
  // std::cout << a;
  // Output format: (%f, %f, %f, %f, %f)
  // ex) (12.34, 2, 1.223, 0.0022221)




#endif // DOUBLE_VECTOR_H_
