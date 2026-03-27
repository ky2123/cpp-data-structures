#include <iostream>
#include <cassert>

namespace cside  {
  class IntArray {
    public:
      IntArray(std::size_t size) : data_{new int[size]}, size_{size}{}
    ~IntArray() {
      delete[] data_;
    }
    IntArray(const IntArray& other) : data_{new int[other.size_]}, size_{other.size_} {
      for (std::size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
      }
    }
    IntArray& operator=(const IntArray& other) {
      if (this == &other) {
        return *this;
      }
      delete[] data_;
      size_ = other.size_;
      data_ = new int[size_];
      for (std::size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
      }
      return *this;
    }
    int& get (std::size_t index) {
      return data_[index];
    }
    const int& get (std::size_t index) const {
      return data_[index];
    }
    void set(std::size_t index, int element){
      data_[index] = element;
    }
     private:
      int* data_;
      std::size_t size_;
  };
}

