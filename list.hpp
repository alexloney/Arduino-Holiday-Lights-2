// This is an implementation of a doubly-linked list with an Iterator for looping
// through the list.

template <class T>
struct list_node {
  list_node *prev;
  list_node *next;
  T value;
};
template <class T>
class List {
 public:
	 class Iterator {
		 public:
			 Iterator(list_node<T> *node) : node_(node) {}
			 const T &operator*() const {
				 return node_->value;
			 }
			 Iterator &operator++() {
				 node_ = node_->next;
				 return *this;
			 }
			 bool operator!=(const List<T>::Iterator &that) const {
				 return this->node_ != that.node_;
			 }
			 bool operator==(const List<T>::Iterator &that) const {
				 return !(*this != that);
			 }
		 private:
			 list_node<T> *node_;
	 };

	 Iterator begin() const {
		 return Iterator(head_);
	 }

	 Iterator end() const {
		 return Iterator(tail_);
	 }

  // Linked list constructor, initialize all values and pointers to zero.
  List() : head_(nullptr), tail_(nullptr), count_(0) {}

  // Linked list destructor, free all allocated memory
  ~List() {

    // Loop through the list and delete each node, since this is the
    // destructor, we don't need to worry about updating the next/prev
    // as we remove the items.
    while (head_ != nullptr) {
      list_node<T> *tmp = head_;
      head_ = head_->next;
      delete tmp;
    }
  }

  // Test whether container is empty
  bool empty() { return count_ == 0; }

  // Return the number of elements within the container
  unsigned int size() { return count_; }

  // Access the first element in the container
  T front() {
    if (head_ == nullptr) {
      T blank;
      return blank;
    }
    return head_->value;
  }

  // Access the last element in the container
  T back() {
    if (tail_ == nullptr) {
      T blank;
      return blank;  
    }
    return tail_->value;
  }

  // Add an element to the head of the container
  void push_front(T value) {
    list_node<T> *new_node = new list_node<T>{};
    new_node->value = value;
    new_node->next = head_;
    new_node->prev = nullptr;

    if (head_ != nullptr) {
      head_->prev = new_node;
    }

    head_ = new_node;

    if (tail_ == nullptr) {
      tail_ = head_;
    }

    ++count_;
  }

  // Remove and return the first element in the container
  T pop_front() {
    T ret_val;

    if (head_ != nullptr) {
      list_node<T> *tmp = head_;
      head_ = head_->next;
      
      if (head_ == nullptr) {
        tail_ = nullptr;        
      } else {
        head_->prev = nullptr;
      }
      
      ret_val = tmp->value;
      delete tmp;
      
      --count_;
    }
    
    return ret_val;
  }

  // Add an element to the end of the container
  void push_back(T value) {
    list_node<T> *new_node = new list_node<T>{};
    new_node->value = value;
    new_node->prev = tail_;
    new_node->next = nullptr;

    list_node<T> *old_tail = tail_;
    tail_ = new_node;

    if (old_tail != nullptr) {
      old_tail->next = tail_;
    }

    if (head_ == nullptr) {
      head_ = tail_;      
    }

    ++count_;
  }

  // Remove and return the last element in the container
  T pop_back() {
    T ret_val;

    if (tail_ != nullptr) {
      list_node<T> *tmp = tail_;
      tail_ = tail_->prev;
      
      if (tail_ == nullptr) {
        head_ = nullptr;        
      } else {
        tail_->next = nullptr;
      }
      
      ret_val = tmp->value;
      delete tmp;
      
      --count_;
    }
    
    return ret_val;
  }
  
  // void insert();
  // void erase();

  //
  /*
  void remove(size_t position) {
    // Null head, nothing to delete
    if (head_ == nullptr) {
      return;
    }

    // Base case of deleting the head
    if (position == 0) {
      list_node<T> *delme = head_;
      head_ = head_->next;
      if (head_ != nullptr) {
        head_->prev = nullptr;
      }
      delete delme;
      return;
    }

    // Loop through the list until we reach the node we want to delete
    list_node<T> *last_node = nullptr;
    list_node<T> *current_node = head_;
    size_t current_position = 0;
    while (current_position != position && current_node != nullptr) {
      last_node = current_node;
      current_node = current_node->next;
      ++current_position;
    }

    // If we're pointing to something, it must be the node we want to delete,
    // so remove it and link the last to the next. There will always be a last
    // since we covered that base case already. The next node may be NULL, but
    // that is fine.
    if (current_node != nullptr) {
      last_node->next = current_node->next;
      if (current_node->next != nullptr) {
        current_node->next->prev = last_node;
      }
      delete current_node;
    }
  }
  */

 private:
  list_node<T> *head_;
  list_node<T> *tail_;
  unsigned int count_;
};
