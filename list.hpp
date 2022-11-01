template <class T>
struct list_node {
  list_node *next;
  T value;
};
template <class T>
class List {
 public:
  List() {
    head_ = nullptr;
    count_ = 0;
  }
  ~List() {
    while (head_ != nullptr) {
      list_node<T> *tmp = head_;
      head_ = head_->next;
      delete tmp;
    }
  }
  bool empty() { return count_ == 0; }

  unsigned int size() { return count_; }

  T front() {
    if (head_ == nullptr) {
      T blank;
      return blank;
    }
    return head_->value;
  }

  unsigned int pop_front() {
    T ret_val;
    if (head_ != nullptr) {
      list_node<T> *tmp = head_;
      head_ = head_->next;
      ret_val = tmp->value;
      delete tmp;
      --count_;
    }
    return ret_val;
  }

  void insert(T value) {
    list_node<T> *new_node = new list_node<T>{};
    new_node->next = nullptr;
    new_node->value = value;

    if (head_ == nullptr) {
      head_ = new_node;
    } else {
      list_node<T> *tmp = head_;
      while (tmp->next != nullptr) {
        tmp = tmp->next;
      }
      tmp->next = new_node;
    }
    ++count_;
  }

  void remove(size_t position) {
    // Null head, nothing to delete
    if (head_ == nullptr) {
      return;
    }

    // Base case of deleting the head
    if (position == 0) {
      list_node<T> *delme = head_;
      head_ = head_->next;
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
      delete current_node;
    }
  }

 private:
  list_node<T> *head_;
  unsigned int count_;
};