#ifndef ARRAYT_H_
#define ARRAYT_H_

template <typename T>
class ArrayT {
private:
  T *array;
  int size;

public:
  ArrayT();
  ArrayT(int size); // size 크기의 array를 동적할당
  ~ArrayT();
  T getElement(int pos) const;  // pos가 현재 array의 범위를 벗어나면 "Out of Range" 출력
  void setElement(int pos, T val); // pos가 현재 array의 범위를 벗어나면 "Out of Range" 출력
  int getSize() const;
  void print() const;

  ArrayT& operator=(const ArrayT& rhs); // 오른쪽의 array를 왼쪽의 array에 복사.
  ArrayT& operator[](int index);
};

#endif  // ARRAYT_H_