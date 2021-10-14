//
// Created by jacob on 10/14/21.
//

#ifndef VECTOR__VECTOR_H_
#define VECTOR__VECTOR_H_

#include <cstdio>
#include <initializer_list>

using std::size_t;

template<typename T>
class Vector {
 public:
  class Iterator {
   public:
    explicit Iterator() = default;
    Iterator(const Vector<T> &vec, size_t index) : vec_{vec}, index_{index} {}
    T &operator*() const;
    Iterator operator++();
    bool operator==(const Iterator &) const;
    bool operator!=(const Iterator &) const;

   private:
    Vector<T> vec_;
    size_t index_;

  };

  explicit Vector();
  Vector(const Vector<T> &);
  Vector(std::initializer_list<T>);
  ~Vector();
  Vector &operator=(const Vector<T> &);

  void PushBack(T);
  size_t Size() const noexcept;

  bool Empty() const noexcept;
  void Clear() noexcept;
  void Resize();

  T& operator[] (size_t);

  Iterator Begin() noexcept;
  Iterator End() noexcept;
 private:
  T *data;
  std::size_t size{};
  std::size_t capacity{};

  void Initialize();
  void Copy(const Vector &);
};

template<typename T>
T &Vector<T>::Iterator::operator*() const {

}

template<typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator++() {
  return Vector::Iterator();
}

template<typename T>
bool Vector<T>::Iterator::operator==(const Vector::Iterator &) const {
  return false;
}

template<typename T>
bool Vector<T>::Iterator::operator!=(const Vector::Iterator &) const {
  return false;
}

template<typename T>
Vector<T>::Vector() {
  Initialize();
}

template<typename T>
void Vector<T>::Initialize() {
  capacity = 10;
  data = new T[capacity];
  size = 0;
}

template<typename T>
void Vector<T>::Copy(const Vector &vec) {
  capacity = vec.capacity;
  size = vec.size;
  data = new T[capacity];
  for (int i = 0; i < size; i++) data[i] = vec.data[i];
}

template<typename T>
Vector<T>::Vector(const Vector &vec) {
  Copy(vec);
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector &vec) {
  if (this != &vec) {
    Copy(vec);
  }
  return *this;
}

template<typename T>
bool Vector<T>::Empty() const noexcept {
  return size == 0;
}

template<typename T>
size_t Vector<T>::Size() const noexcept {
  return size;
}

template<typename T>
Vector<T>::~Vector() {
  delete[] data;
}

template<typename T>
void Vector<T>::PushBack(T element) {
  if (size == capacity) {
    Resize();
  }
  data[size++] = element;
}

template<typename T>
void Vector<T>::Clear() noexcept {
  delete[] data;
  Initialize();
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::Begin() noexcept {
  return Vector::Iterator();
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::End() noexcept {
  return Vector::Iterator();
}
template<typename T>
void Vector<T>::Resize() {
  capacity = 2*capacity;
  T* temp = new T[capacity];
  for (int i = 0; i < size; i++) temp[i] = data[i];
  delete[] data;
  data = temp;
}
template<typename T>
Vector<T>::Vector(std::initializer_list<T> list) {
  std::cout << list.size() << std::endl;
}
template<typename T>
T& Vector<T>::operator[] (size_t index) {
  return data[index];
}

#endif //VECTOR__VECTOR_H_
