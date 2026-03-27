#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <cstddef>
#include <string>
namespace cside{
  class LinkedList{
    private:
      struct Node {
        std::string value;
        Node* next;
      };
      Node* head_{};
      Node* tail_{};
      std::size_t size_;
    public:
      LinkedList();
      LinkedList(std::initializer_list<std::string> str);
      LinkedList(const LinkedList& src); 
      LinkedList(LinkedList&& src);
      ~LinkedList();
      void push_back(const std::string& val);
      const std::string& front() const;
      const std::string& back() const;
      Node* front_node() const;
      Node* back_node() const;
      std::size_t size() const;
      std::string& operator[](std::size_t index);
      bool operator==(const LinkedList& list) const;
      bool operator!=(const LinkedList& list) const;
      std::string pop_back();
      bool empty() const;
      bool contains(const std::string& string);
      void push_front(const std::string& string);
      std::string pop_front();
      std::string& at(std::size_t index);
      void insert(std::size_t index, const std::string& string);
      void remove(std::size_t index);
      void reverse();
      LinkedList& operator=(const LinkedList& src);
      LinkedList& operator=(LinkedList&& src);
      void clear();
      class Iterator {
        public:
          Iterator(Node* node); 
          Iterator& operator++();
          Node& operator*() const;
          Node* get_node() const;
          bool operator!=(const Iterator& other) const;
        private:
         Node* current_; 
      };
      Iterator begin();
      Iterator end();
  };
} 

#endif 



