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

  template<typename K=T>
  class Iterator {

    using SelfType = Iterator;
   public:

    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = K;
    using pointer = K *;
    using reference = K &;

    explicit Iterator(pointer ptr = nullptr) : ptr_(ptr) {}
    Iterator(const SelfType &iterator) = default;

    SelfType &operator=(const SelfType &iterator) = default;
    SelfType &operator=(pointer ptr) {
      ptr_ = ptr;
      return *this;
    }

    SelfType &operator++() {
      ptr_++;
      return *this;
    }
    SelfType operator++(int) {
      SelfType copy = *this;
      ++(*this);
      return copy;
    }

    SelfType &operator--() {
      ptr_--;
      return *this;
    }
    SelfType operator--(int) {
      SelfType copy = *this;
      --(*this);
      return copy;
    }

    reference operator*() { return *ptr_; }
    const SelfType &operator*() const { return *ptr_; }
    pointer operator->() { return ptr_; }

    friend bool operator==(const SelfType &lhs,
                           const SelfType &rhs) {
      return lhs.ptr_ == rhs.ptr_;
    }
    friend bool operator!=(const SelfType &lhs,
                           const SelfType &rhs) {
      return lhs.ptr_ != rhs.ptr_;
    }

    SelfType &operator+=(const difference_type &movement) {
      ptr_ += movement;
      return (*this);
    }
    SelfType &operator-=(const difference_type &movement) {
      ptr_ -= movement;
      return (*this);
    }

    SelfType operator+(const difference_type &increment) {
      auto old_ptr = ptr_;
      ptr_ += increment;
      auto temp(*this);
      ptr_ = old_ptr;
      return temp;
    }

    SelfType operator-(const difference_type &increment) {
      auto old_ptr = ptr_;
      ptr_ -= increment;
      auto temp(*this);
      ptr_ = old_ptr;
      return temp;
    }

    friend difference_type operator-(const SelfType &lhs, const SelfType &rhs) {
      return std::distance(rhs.ptr_, lhs.ptr_);
    }

    friend bool operator<(const SelfType &lhs,
                          const SelfType &rhs) {
      return lhs.ptr_ < rhs.ptr_;
    }

    friend bool operator>(const SelfType &lhs,
                          const SelfType &rhs) {
      return lhs.ptr_ > rhs.ptr_;
    }

    friend bool operator<=(const SelfType &lhs,
                           const SelfType &rhs) {
      return lhs.ptr_ <= rhs.ptr_;
    }

    friend bool operator>=(const SelfType &lhs,
                           const SelfType &rhs) {
      return lhs.ptr_ >= rhs.ptr_;
    }

   private:
    pointer ptr_;

  };

  using iterator = Iterator<T>;
  using const_iterator = Iterator<const T>;

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

  iterator Begin() noexcept;
  const_iterator cBegin() const noexcept;

  iterator End() noexcept;
  const_iterator cEnd() const noexcept;
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
typename Vector<T>::template Iterator<T> Vector<T>::Begin() noexcept {
  return Vector::Iterator<T>(data_);
}

template<typename T>
typename Vector<T>::template Iterator<T> Vector<T>::End() noexcept {
  return Vector::Iterator<T>(data_ + size_);
}

template<typename T>
typename Vector<T>::template Iterator<const T> Vector<T>::cBegin() const noexcept {
  return Vector::Iterator<const T>(data_);
}

template<typename T>
typename Vector<T>::template Iterator<const T> Vector<T>::cEnd() const noexcept {
  return Vector::Iterator<const T>(data_ + size_);
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
