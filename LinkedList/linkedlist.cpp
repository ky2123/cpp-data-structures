#include "linkedlist.h"
#include <stdexcept>
#include <cstddef>
#include <iostream>
#include <string>
#include <stdexcept>

cside::LinkedList::LinkedList(std::initializer_list<std::string> str) : size_{0}{ 
  for (const auto& s : str) {
    push_back(s);
  }
}
cside::LinkedList::LinkedList() : head_{nullptr}, tail_{nullptr}, size_{} {}
cside::LinkedList::LinkedList(const LinkedList& src) : head_{nullptr}, tail_{nullptr}, size_{0} {
 Node* src_current = src.head_; 
 while (src_current != nullptr) {
   this->push_back(src_current->value);
   src_current = src_current->next;
 }
} 
cside::LinkedList::LinkedList(LinkedList&& src) : head_{src.head_}, tail_{src.tail_}, size_{src.size_} {
  src.head_ = nullptr;
  src.tail_ = nullptr;
  src.size_ = 0;
}

cside::LinkedList::~LinkedList() { 
  Node* current = head_;
  while (current != nullptr) {
  Node* next = current->next;
  delete current; 
  current = next;
  }
};

void cside::LinkedList::push_back(const std::string& val) {
  Node* new_node = new Node{val, nullptr};
  if (head_ == nullptr) {
    head_ = tail_ = new_node;
}else{
  tail_->next = new_node;
  tail_ = new_node;
}
++size_;
}
const std::string& cside::LinkedList::front() const {
  return (head_ != nullptr) ? head_->value : throw std::out_of_range("List is empty");
}
const std::string& cside::LinkedList::back() const {
  return (tail_ != nullptr) ? tail_->value : throw std::out_of_range("List is empty");
}
cside::LinkedList::Node* cside::LinkedList::front_node() const {
  return head_;
}
cside::LinkedList::Node* cside::LinkedList::back_node() const {
  return tail_;
}
std::size_t cside::LinkedList::size() const {
  return size_;
}
std::string& cside::LinkedList::operator[](std::size_t index) {
  Node* current = head_;
  std::size_t current_index = 0;
  while (current_index < index) {
    current = current->next;
    ++current_index;
  }
  return current->value;
}
std::string cside::LinkedList::pop_back() {
  std::string value = tail_->value;
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
bool cside::LinkedList::operator==(const LinkedList& other) const {
  if (size_ != other.size_) {
    return false;
  }
  Node* lhs = head_;
  Node* rhs = other.head_;
  while (lhs != nullptr) {
    if (lhs->value != rhs->value){
      return false;
    }
    lhs = lhs->next;
    rhs = rhs->next;
  }
 return true; 
} 
bool cside::LinkedList::operator!=(const LinkedList& other) const {
  return !(*this == other);
}
bool cside::LinkedList::empty() const{
  return (head_ == nullptr);
}
bool cside::LinkedList::contains(const std::string& string) {
  Node* current = head_;
  while(current != nullptr) {
    if (current->value == string) {
      return true;
    }
    current = current->next;
  }
  return false;
}
void cside::LinkedList::push_front(const std::string& string) {
  Node* new_node = new Node{string, nullptr};
  if(head_ == nullptr) {
    head_ = tail_ = new_node;
}else{
  new_node->next = head_;
  head_ = new_node;
}
++size_;
}
std::string cside::LinkedList::pop_front() {
  std::string value = head_->value;
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
std::string& cside::LinkedList::at(std::size_t index) {
  if(index >= size_) {
    throw std::out_of_range("Index is out bounds");
  }
  std::string& return_val = (*this)[index];
 return return_val;
}
void cside::LinkedList::insert(std::size_t index, const std::string& string) {
  if(index == 0) {
    this->push_front(string);
    return;
  }
  if(index == size_){
    this->push_back(string);
    return;
  }
  std::size_t current_index = 0;
  Node* current = head_;
  while(current != nullptr) {
    if(current_index == index-1) {
     Node* new_node = new Node{string, current->next};
      current->next = new_node;
      break;
    } else{
      current = current->next;
      ++current_index;
    }
  }
  ++size_;
}
void cside::LinkedList::remove(std::size_t index) {
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
void cside::LinkedList::reverse() {
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
cside::LinkedList& cside::LinkedList::operator=(const LinkedList& src) {
  if(this == &src) { 
    return *this;
  }
  Node* current = head_;
  while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;
  }
  head_ = tail_ = nullptr;
  size_ = 0;
  Node* src_current = src.head_; 
  while (src_current != nullptr) {
    this->push_back(src_current->value);
    src_current = src_current->next;
  }
  return *this;
} 
cside::LinkedList& cside::LinkedList::operator=(LinkedList&& src) {
  if(this == &src) { 
    return *this;
  }
  Node* current = head_;
  while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;
  }
  head_ = src.head_;
  tail_ = src.tail_;
  size_ = src.size_;
  src.head_ = nullptr;
  src.tail_ = nullptr;
  src.size_ = 0;

  return *this;
}
void cside::LinkedList:: clear() {
  for (auto it = begin(); it != end(); ) {
    Node* to_delete = it.get_node();
    ++it;
    delete to_delete;
  }
  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}

cside::LinkedList::Iterator::Iterator(Node* node)
  : current_(node){}

cside::LinkedList::Iterator& cside::LinkedList::Iterator::operator++() {
  if(current_) current_ = current_->next;
  return *this;
}

cside::LinkedList::Node& cside::LinkedList::Iterator::operator*() const {
  return *current_;
}

cside::LinkedList::Node* cside::LinkedList::Iterator::get_node() const {
  return current_;
}

bool cside::LinkedList::Iterator::operator!=(const Iterator& other) const {
  return current_ != other.current_;
}
cside::LinkedList::Iterator cside::LinkedList::begin() {
  return Iterator(head_);
}
cside::LinkedList::Iterator cside::LinkedList::end() {
  return Iterator(nullptr);
}

