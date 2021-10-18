//
// Created by jacob on 10/14/21.
//

#ifndef VECTOR__VECTOR_H_
#define VECTOR__VECTOR_H_

#include <cstdio>
#include <iterator>
#include <initializer_list>

namespace library {

template<typename T>
class Vector {

 public:

  using value_type = T;
  using size_type = std::size_t;
  using reference = T &;
  using const_reference = const T *;

  class Iterator {
   public:

    using self_type = Iterator;
    using self_type_reference = Iterator;

    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;

    explicit Iterator() = default;
    explicit Iterator(pointer ptr) : ptr_(ptr) {}
    self_type_reference operator++() {
      ptr_++;
      return *this;
    }
    self_type operator++(int) {
      self_type copy = *this;
      ++(*this);
      return copy;
    }
    reference operator*() { return *ptr_; }
    pointer operator->() { return ptr_; }
    friend bool operator==(const self_type &lhs, const self_type &rhs) {
      return lhs.ptr_ == rhs.ptr_;
    }
    friend bool operator!=(const self_type &lhs, const self_type &rhs) {
      return lhs.ptr_ != rhs.ptr_;
    }

    friend bool operator<(const self_type &lhs, const self_type &rhs) {
      return lhs.ptr_ < rhs.ptr_;
    }

    friend bool operator>(const self_type &lhs, const self_type &rhs) {
      return lhs.ptr_ > rhs.ptr_;
    }

    friend bool operator<=(const self_type &lhs, const self_type &rhs) {
      return lhs.ptr_ <= rhs.ptr_;
    }

    friend bool operator>=(const self_type &lhs, const self_type &rhs) {
      return lhs.ptr_ >= rhs.ptr_;
    }

   private:
    pointer ptr_;

  };

  using iterator = Iterator;
  using const_iterator = const Iterator;

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

  T &operator[](size_t) const;

  Iterator Begin() noexcept;
  Iterator End() noexcept;
 private:
  T *data_;
  size_t size_{};
  size_t capacity_{};

  void Initialize();
  void Allocate(size_t, size_t);
  void Copy(const Vector &);

};

template<typename T>
Vector<T>::Vector() {
  Initialize();
}

template<typename T>
void Vector<T>::Initialize() {
  Allocate(0, 10);
}

template<typename T>
void Vector<T>::Copy(const Vector &vec) {
  Allocate(vec.size_, vec.capacity_);
  for (size_t i = 0; i < size_; i++) data_[i] = vec.data_[i];
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
  return size_ == 0;
}

template<typename T>
size_t Vector<T>::Size() const noexcept {
  return size_;
}

template<typename T>
Vector<T>::~Vector() {
  delete[] data_;
}

template<typename T>
void Vector<T>::PushBack(T element) {
  if (size_ == capacity_) {
    Resize();
  }
  data_[size_++] = element;
}

template<typename T>
void Vector<T>::Clear() noexcept {
  delete[] data_;
  Initialize();
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::Begin() noexcept {
  return Vector::Iterator(data_);
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::End() noexcept {
  return Vector::Iterator(data_ + size_);
}
template<typename T>
void Vector<T>::Resize() {
  capacity_ = 2 * capacity_;
  T *temp = new T[capacity_];
  for (size_t i = 0; i < size_; i++) temp[i] = data_[i];
  delete[] data_;
  data_ = temp;
}
template<typename T>
Vector<T>::Vector(std::initializer_list<T> list) {
  Allocate(list.size(), list.size() + 1);
  size_t i = 0;
  for (auto it = list.begin(); it != list.end(); ++it) {
    data_[i++] = std::move(*it);
  }
}
template<typename T>
T &Vector<T>::operator[](size_t index) const {
  return data_[index];
}

template<typename T>
void Vector<T>::Allocate(size_t size, size_t capacity) {
  size_ = size;
  capacity_ = capacity;
  data_ = new T[capacity];
}

}

#endif //VECTOR__VECTOR_H_
