#include <utility>
namespace cside {
template <typename K, typename V>
  // node itself
class Map {
  private:
  struct Node {
    Node* left{};
    Node* right{};
    Node* parent{};
    std::pair<const K, V> element;
   Node(std::pair<const K, V> p, Node* par) : left{}, right{}, parent{par}, element{std::move(p)} {}
  };
    
    Node* root{};
    std::size_t size_{};
  public: 
  // defeault constructor
  Map() = default;
// initializer constructor
  Map(std::initializer_list<std::pair<K, V>> val) {
    for (const auto& p : val ) {
        insert(p);
    }
  }
  
  Node* copy_nodes(Node* src, Node* parent) {
    if (!src) { return nullptr; }
    Node* new_node = new Node(src->element, parent);
    new_node->left = copy_nodes(src->left, new_node);
    new_node->right = copy_nodes(src->right, new_node);
    return new_node;
  }
  // copy constructor 
  Map(const Map& src) { 
    root = copy_nodes(src.root, nullptr);
    size_ = src.size_;
    }
  
  Map(Map&& src ) :  root{src.root}, size_{src.size_} {
    src.root = nullptr;
    src.size_ = 0;
  }


  void clear_impl(Node* root) {
      if (root == NULL) { return; }
      clear_impl(root->left);
      clear_impl(root->right);
      delete root;
}
 void  clear() {
    clear_impl(root);
    size_ = 0;
  }
  ~Map() {
    clear();
  }

struct Node* find_node_impl(Node* node, const K& key) {
  if (!node) { return nullptr; }
  if (key == node->element.first) {
  return node;
  } 
  return find_node_impl((key > node->element.first) ?  node->right : node->left, key);
}

Node* find_node(const K& key) {
  return find_node_impl(root, key);
}


struct Node* insert_impl(const K& k, V&& v,  Node* node, Node* parent) {
  if(node == nullptr) {
    size_++;
    return new Node(std::make_pair(k, std::move(v)), parent);
  } 
  if(k == node->element.first)  {
  node->element.second = std::move(v);
  return node;
  }
  if(k > node->element.first) {
    node->right = insert_impl(k, std::move(v), node->right, node);
    node->right->parent = node;
  } else {
    node->left = insert_impl(k, std::move(v), node->left, node);
    node->left->parent = node;
  }
  return node;
}


void insert(std::pair<const K, V> p) {
 root =  insert_impl(p.first, std::move(p.second), root, nullptr);
}

bool empty() { 
  return (root == nullptr);
}



V& at(const K& key) {
  if (find_node(key) != nullptr) {
     return find_node(key)->element.second;
}
  throw std::out_of_range("Key is absent");
  }

void erase(const K& key) {
  find_node(key)->element.second = V{};
}

V& operator[](const K& key) {
  Node* node = find_node(key);
  if(node) { return node->element.second;}
  else { insert(std::make_pair(key, V{}));
 node = find_node(key);
 return node->element.second;
  }
}

Map& operator=(const Map& src) {
  if (this == &src) {
    return *this;
  }
  clear();
  root = copy_nodes(src.root, nullptr);
  size_ = src.size_;
  
  return *this;
}

Map& operator=(Map&& src) {
  if (this == &src) {
    return *this;
  }
  clear();
  root = src.root;
  size_ = src.size_;
  src.root = nullptr;
  src.size_ = 0;
  return *this;
}

bool operator==(const Map& other) const {
 if (size_ != other.size_) {
   return false;
 }
  for(auto lhs = begin(), rhs = other.begin(); lhs != end(); ++lhs, ++rhs) {
    if(lhs->second != rhs->second || lhs->first != rhs->first) {
      return false;
    }
  }
  return true;
}
bool operator!=(const Map& rhs) const {
  return !(*this == rhs);
}

std::size_t size() const {
  return size_;
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
    using iterator_category = std::bidirectional_iterator_tag;

    explicit IteratorTempl(Node* node) : current(node) {}
    IteratorTempl() = default;

    IteratorTempl& operator++() {
      if(current->right) {
        current = current->right;
        while(current->left) {
          current = current->left;
        }
      } else  { 
       while(current->parent && current->parent->left != current) {
        current = current->parent;
       }
       current = current->parent;
      }

      return *this;
    }

    IteratorTempl operator++(int) {
      auto tmp = *this;
      ++(*this);
      return tmp;
    }
    
    IteratorTempl& operator--() {
      if(current->left) {
        current = current->left;
        while(current->right) {
          current = current->right;
        }
      } else {
        while(current->parent && current == current->parent->left) {
          current = current->parent;
        }
        current = current->parent;
      }
      return *this;
    }

    IteratorTempl operator--(int) {
      auto tmp = *this;
      --(*this);
        return tmp;
    }
    // a horrendous attempt at combining increment and decrement into one function 
    /*
    Node* node;
    using ChildPtr = Node* Node::*;
    
    void step(ChildPtr step, ChildPtr otherStep) {
      if (node == nullptr) {
        return;
      }

      Node* n = node;

      if (n->*step) {
        n = n->*step;
        while (n->*otherStep) { 
          n = n->*otherStep;
        }
          node = n;
          return;
      }
      Node* parent = n->parent;
      while(parent && n == parent->*step) {
        n = parent;
        parent = parent->parent;
      }
      node = parent;
    }
    IteratorTempl& operator++() {
      step(&Node::right, &Node::left);
      return *this;
    }
    IteratorTempl& operator--() {
     step(&Node::left, &Node::right);
      return *this;
    } 
    
*/
    pointer operator->() const { return &current->element;}
    
    reference operator*() const { return current->element;}

    template <typename U>
      bool operator!=(const IteratorTempl<U>& other) const {
        return current != other.current;
      }
    template <typename U>
      bool operator==(const IteratorTempl<U>& other) const {
        return !(*this != other);
      }

  private:
    Node* current{};
};    
using Iterator = IteratorTempl<std::pair<const K,V>>;
using ConstIterator = IteratorTempl<const std::pair<const K,V>>;

Iterator begin() {
  Node* current = root;
  if (current) {
    while(current->left) {
      current = current->left;
    }
  }

  return Iterator(current);
}

Iterator end() { return Iterator(nullptr); }
ConstIterator begin() const { 
  Node* current = root;
  if (current) {
    while(current->left) {
      current = current->left;
    }
  }

  return ConstIterator(current);
  }
ConstIterator end() const { return ConstIterator(nullptr); } 
template <typename... Args>
std::pair<Iterator, bool>emplace(Args&&... args) {
  std::pair<const K, V> p(std::forward<Args>(args)...);

  // if there is already a node with these values in the tree, return said node
  if (Node* node = find_node(p.first)) {
    return { Iterator(node), false };
  }
  // if there is no node that exist with these values, insert the new node into the tree and 
  // return an iterator refercing
  root = insert_impl(p.first, std::move(p.second), root, nullptr);
  return { Iterator(find_node(p.first)), true};

}

};
}

