#include <stdexcept> 
#include <cstddef>
#include <iostream>
#include <string>
#include <stdexcept>
class Person {
  public:
  std::string name;

  Person(std::string name) { this->name = name; }
  bool operator== (const Person& p) const {
    return (name == p.name);
  }
  bool operator!= (const Person& p) const {
    return (name != p.name);
  }

};
namespace cside {
template<typename T>
  class LinkedList{
    private:
      struct Node {
        T value;
        Node* next;
      };
      Node* head_{};
      Node* tail_{};
      std::size_t size_{};
    public: 
      LinkedList(std::initializer_list<T> val) : size_{0}{ 
        for (const auto& s : val) {
          push_back(s);
        }
      }
      LinkedList() = default;
      LinkedList(const LinkedList& src) {
        Node* src_current = src.head_; 
        while (src_current != nullptr) {
          this->push_back(src_current->value);
          src_current = src_current->next;
        }
      } 
      LinkedList(LinkedList&& src) : head_{src.head_}, tail_{src.tail_}, size_{src.size_} {
        src.head_ = nullptr;
        src.tail_ = nullptr;
        src.size_ = 0;
      }

      ~LinkedList() { 
        Node* current = head_;
        while (current != nullptr) {
          Node* next = current->next;
          delete current; 
          current = next;
        }
      };
      void push_back(const T& val) { Node* new_node = new Node{val, nullptr};
        if (head_ == nullptr) {
          head_ = tail_ = new_node;
        }else{
          tail_->next = new_node;
          tail_ = new_node;
        }
        ++size_;
      }
      
      const T& front() const {
        if(!empty()) {
          return head_->value;
        } else {
          throw std::out_of_range("List is empty");
        }
      }
      const T& back() const {
        if(!empty()) {
          return tail_->value;
        } else {
          throw std::out_of_range("List is empty");
        }
      }
      T& front() {
        if(!empty()) {
          return head_->value;
        } else {
          throw std::out_of_range("List is empty");
        }
      }
      T& back() {
        if(!empty()) {
          return tail_->value;
        } else {
          throw std::out_of_range("List is empty");
        }
      }

      std::size_t size() const {
        return size_;
      }
      
      T& operator[](std::size_t index) {
        Node* current = head_;
        std::size_t current_index = 0;
        while (current_index < index) {
          current = current->next;
          ++current_index;
        }
        return current->value;
      }
      const T& operator[](std::size_t index) const {
       const Node* current = head_;
        std::size_t current_index = 0;
        while (current_index < index) {
          current = current->next;
          ++current_index;
        }
        return current->value;
      }

      
      T pop_back() {
        T value = tail_->value;
        if(head_ == tail_) {
          delete tail_;
          tail_ = head_ = nullptr;
          --size_;
          return value;
        }
        Node* current = head_;
        while(current->next != tail_) {
          current = current->next;
        }
        delete tail_;
        tail_ = current;
        tail_->next = nullptr;
        --size_;
        return value;
      }
      
      bool operator==(const LinkedList& other) const {
        if (size_ != other.size_) {
          return false;
        }
        auto lhs = begin();
        auto rhs = other.begin();
        while (lhs != end()) {
          if (*lhs != *rhs) {
            return false;
          }
          ++lhs;
          ++rhs;
        }
        return true; 
      } 
      bool operator!=(const LinkedList& other) const {
        return !(*this == other);
      }
      
      bool empty() const{
        return (head_ == nullptr);
      }
      bool contains(const T& needle) const {
        for (const auto& val : *this) {
          if (val == needle) {
            return true;
          }
      }
        return false;
      }
      
      void push_front(const T& val) {
        Node* new_node = new Node{val, nullptr};
        if(head_ == nullptr) {
          head_ = tail_ = new_node;
        }else{
          new_node->next = head_;
          head_ = new_node;
        }
        ++size_;
      }
     
      T pop_front() {
        T value = head_->value;
        if(head_ == tail_) {
          delete head_;
          tail_ = head_ = nullptr;
          --size_;
          return value;
        }
        Node* new_head = head_->next; 
        delete head_;
        head_ = new_head;
        --size_;
        return value;
      }

      T& at(std::size_t index) {
        if(index >= size_) {
          throw std::out_of_range("Index is out bounds");
        }
        return (*this)[index];

      }
      void clear() {
        Node* to_delete = head_;
        while (to_delete) {
          Node* next = to_delete->next;
          delete to_delete;
          to_delete = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
      }
    
      void insert(std::size_t index, const T& val) {
        if(index == 0) {
          this->push_front(val);
          return;
        }
        if(index == size_){
          this->push_back(val);
          return;
        }
        std::size_t current_index = 0;
        Node* current = head_;
        while(current != nullptr) {
          if(current_index == index-1) {
            Node* new_node = new Node{val, current->next};
            current->next = new_node;
            break;
          } else{
            current = current->next;
            ++current_index;
          }
        }
        ++size_;
      }
      void remove(std::size_t index) {
        if (index == 0) {
          this->pop_front();
          return;
        }
        if (index == size_-1) {
          this->pop_back();
          return;
        }
        std::size_t current_index = 0;
        Node* current = head_;
        while(current != nullptr) {
          if(current_index == index-1) {
            Node* remove_node = current->next;
            current->next = remove_node->next;
            delete remove_node;
            --size_;
            return;
          }else{
            current = current->next;
            ++current_index;
          }
        }
      }
      void reverse() {
        Node* current = head_;
        Node* prev = nullptr;
        Node* next = nullptr;
        while(current != nullptr){
          next = current->next;
          current->next = prev;
          prev = current;
          current = next;
        }
        tail_ = head_;
        head_ = prev;
      }
      LinkedList& operator=(const LinkedList& src) {
        if(this == &src) { 
          return *this;
        }
        clear();
        for (const auto& val : src) {
          push_back(val);
        }
        return *this;
      }
        LinkedList& operator=(LinkedList&& src) {
        if(this == &src) { 
          return *this;
        }
        clear();
        head_ = src.head_;
        tail_ = src.tail_;
        size_ = src.size_;
        src.head_ = nullptr;
        src.tail_ = nullptr;
        src.size_ = 0;

        return *this;
      }
  template <typename ItType>
    class IteratorTempl {
      template <typename U>
        friend class IteratorTempl;
    public:
      using value_type = std::decay_t<ItType>;
      using reference = ItType&;
      using pointer = ItType*;
      using difference_type = std::ptrdiff_t;
      using iterator_category = std::forward_iterator_tag;

      explicit IteratorTempl(Node* node) : current_(node) {}
      IteratorTempl() = default;
      IteratorTempl operator++(int) {
        auto ret = *this;
        ++*this;
        return ret;
      }
      IteratorTempl& operator++() {
        if(current_) {
          current_ = current_->next;
      }
        return *this;
      }
      
      pointer operator->() const { return &current_->value; }

      reference operator*() const { return current_->value; }

      
      template <typename U>
      bool operator!=(const IteratorTempl<U>& other) const {
        return current_ != other.current_;
      }
      template <typename U>
      bool operator==(const IteratorTempl<U>& other) const {
        return !(*this != other);
      }

    private:
      Node* current_{};
  };
  using Iterator = IteratorTempl<T>;
  using ConstIterator = IteratorTempl<const T>;
  
  Iterator begin() { return Iterator(head_); }
  Iterator end() { return Iterator(nullptr); }
  ConstIterator begin() const { return ConstIterator(head_); }
  ConstIterator end() const { return ConstIterator(nullptr); }
  };
}
