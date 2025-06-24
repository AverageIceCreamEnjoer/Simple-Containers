#ifndef RPC_VECTOR_ITERATORS_H
#define RPC_VECTOR_ITERATORS_H

#include "rpc_vector.h"

namespace rpc {

template <typename value_type>
class vector<value_type>::VectorIterator {
 public:
  VectorIterator() = default;
  VectorIterator(iterator ptr);

  reference operator*();
  VectorIterator& operator++();
  VectorIterator& operator--();
  VectorIterator operator++(int);
  VectorIterator operator--(int);
  bool operator==(const VectorIterator& other) const;
  bool operator!=(const VectorIterator& other) const;
  VectorIterator operator+(int n) const;
  VectorIterator operator-(int n) const;
  ptrdiff_t operator-(const VectorIterator& other) const;

 private:
  iterator ptr_;
};  // class VectorIterator

template <typename value_type>
class vector<value_type>::VectorConstIterator : public VectorIterator {
 public:
  VectorConstIterator() = default;
  VectorConstIterator(const_iterator ptr);

  const_reference operator*() const;
  VectorConstIterator& operator++();
  VectorConstIterator& operator--();
  VectorConstIterator operator++(int);
  VectorConstIterator operator--(int);
  bool operator==(const VectorConstIterator& other) const;
  bool operator!=(const VectorConstIterator& other) const;
  VectorConstIterator operator+(int n) const;
  VectorConstIterator operator-(int n) const;
  ptrdiff_t operator-(const VectorConstIterator& other) const;

 private:
  const_iterator ptr_;
};  // class VectorConstIterator

//
// Implementations
//
// VectorIterator
template <typename value_type>
vector<value_type>::VectorIterator::VectorIterator(iterator ptr) : ptr_(ptr) {}

template <typename value_type>
typename vector<value_type>::reference
vector<value_type>::VectorIterator::operator*() {
  return *ptr_;
}

template <typename value_type>
typename vector<value_type>::VectorIterator&
vector<value_type>::VectorIterator::operator++() {
  ++ptr_;
  return *this;
}

template <typename value_type>
typename vector<value_type>::VectorIterator&
vector<value_type>::VectorIterator::operator--() {
  --ptr_;
  return *this;
}

template <typename value_type>
typename vector<value_type>::VectorIterator
vector<value_type>::VectorIterator::operator++(int) {
  VectorIterator temp(*this);
  ++ptr_;
  return temp;
}

template <typename value_type>
typename vector<value_type>::VectorIterator
vector<value_type>::VectorIterator::operator--(int) {
  VectorIterator temp(*this);
  --ptr_;
  return temp;
}

template <typename value_type>
bool vector<value_type>::VectorIterator::operator==(
    const VectorIterator& other) const {
  return ptr_ == other.ptr_;
}

template <typename value_type>
bool vector<value_type>::VectorIterator::operator!=(
    const VectorIterator& other) const {
  return ptr_ != other.ptr_;
}

template <typename value_type>
typename vector<value_type>::VectorIterator
vector<value_type>::VectorIterator::operator+(int n) const {
  VectorIterator temp = *this;
  for (int i = 0; i < n; i++) temp++;
  return temp;
}

template <typename value_type>
typename vector<value_type>::VectorIterator
vector<value_type>::VectorIterator::operator-(int n) const {
  VectorIterator temp = *this;
  for (int i = 0; i < n; i++) temp--;
  return temp;
}

template <typename value_type>
ptrdiff_t vector<value_type>::VectorIterator::operator-(
    const VectorIterator& other) const {
  return ptr_ - other.ptr_;
}

// VectorConstIterator
template <typename value_type>
vector<value_type>::VectorConstIterator::VectorConstIterator(const_iterator ptr)
    : ptr_(ptr) {}

template <typename value_type>
typename vector<value_type>::const_reference
vector<value_type>::VectorConstIterator::operator*() const {
  return *ptr_;
}

template <typename value_type>
typename vector<value_type>::VectorConstIterator&
vector<value_type>::VectorConstIterator::operator++() {
  ++ptr_;
  return *this;
}

template <typename value_type>
typename vector<value_type>::VectorConstIterator&
vector<value_type>::VectorConstIterator::operator--() {
  --ptr_;
  return *this;
}

template <typename value_type>
typename vector<value_type>::VectorConstIterator
vector<value_type>::VectorConstIterator::operator++(int) {
  VectorConstIterator temp(*this);
  ++ptr_;
  return temp;
}

template <typename value_type>
typename vector<value_type>::VectorConstIterator
vector<value_type>::VectorConstIterator::operator--(int) {
  VectorConstIterator temp(*this);
  --ptr_;
  return temp;
}

template <typename value_type>
bool vector<value_type>::VectorConstIterator::operator==(
    const VectorConstIterator& other) const {
  return ptr_ == other.ptr_;
}

template <typename value_type>
bool vector<value_type>::VectorConstIterator::operator!=(
    const VectorConstIterator& other) const {
  return ptr_ != other.ptr_;
}

template <typename value_type>
typename vector<value_type>::VectorConstIterator
vector<value_type>::VectorConstIterator::operator+(int n) const {
  VectorConstIterator temp = *this;
  for (int i = 0; i < n; i++) temp++;
  return temp;
}

template <typename value_type>
typename vector<value_type>::VectorConstIterator
vector<value_type>::VectorConstIterator::operator-(int n) const {
  VectorConstIterator temp = *this;
  for (int i = 0; i < n; i++) temp--;
  return temp;
}

template <typename value_type>
ptrdiff_t vector<value_type>::VectorConstIterator::operator-(
    const VectorConstIterator& other) const {
  return ptr_ - other.ptr_;
};  // class VectorConstIterator

}  // namespace rpc

#endif  //  RPC_VECTOR_ITERATORS_H