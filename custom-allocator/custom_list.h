#pragma once

#include <memory>

template<typename T, class Allocator = std::allocator<T>>
class CustomList {
 public:
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    using allocator_type = Allocator;

 private:
    struct Node {
        explicit Node(pointer data) : data(data) {}

        pointer data{nullptr};
        Node* next{nullptr};
    };

  class Iterator : public std::iterator<std::input_iterator_tag,
                                        T,
                                        T,
                                        const T*,
                                        T> {
   public:
      explicit Iterator(Node* node) : node_(node) {}

      Iterator& operator++() {
          node_ = node_->next;
          return *this;
      }

      Iterator operator++(int) {
          node_ = node_->next;
          return *this;
      }

      bool operator==(Iterator other) const {
          if (other.node_ == nullptr) {
              return (this->node_ == nullptr);
          }

          return *node_->data == *other.node_->data;
      }

      bool operator!=(Iterator other) const {
          return !(*this == other);
      }

      reference operator*() const {
          return *node_->data;
      }

   private:
      Node* node_{nullptr};
  };

 public:
    ~CustomList() {
        Node* next = begin_;
        while (next != nullptr) {
            Node* tmp = next->next;
            allocator_.deallocate(next->data, 1);
            delete next;
            next = tmp;
        }
    }

    void push(const_reference value) {
        pointer p;

        try {
            p = allocator_.allocate(1);
        } catch (const std::exception& e) {
            std::cerr << "raised an exception: " << e.what() << '\n';
            return;
        }

        *p = value;

        if (begin_ == nullptr) {
            begin_ = new Node(p);
            end_ = begin_;
        } else {
            end_->next = new Node(p);
            end_ = end_->next;
        }

        size_++;
    }

    Iterator begin() const {
        return Iterator(begin_);
    }

    Iterator end() const {
        return Iterator(end_->next);
    }

    bool empty() const {
        return size_ == 0;
    }

    size_t size() const {
        return size_;
    }

    reference front() const {
        return *begin_->data;
    }

    reference back() const {
        return *end_->data;
    }

 private:
    Node* begin_{nullptr};
    Node* end_{nullptr};
    size_t size_{0};
    Allocator allocator_;
};