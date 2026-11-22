#pragma once

#include "OneList.hpp"
#include <cstddef>

template <typename T> class DoubleList : public OneList<T> {
public:
  class Iterator {
    Element<T> *cur;
    DoubleList<T> *owner;
    Iterator(Element<T> *c, DoubleList<T> *o) : cur(c), owner(o) {}
    friend class DoubleList;

  public:
    T &operator*() const { return cur->data; }
    T *operator->() const { return &cur->data; }

    Iterator &operator++() {
      cur = cur->next;
      return *this;
    }
    Iterator operator++(int) {
      Iterator t(*this);
      ++(*this);
      return t;
    }

    Iterator &operator--() {
      if (cur == nullptr)
        cur = owner ? owner->tail : nullptr;
      else
        cur = cur->prev;
      return *this;
    }
    Iterator operator--(int) {
      Iterator t(*this);
      --(*this);
      return t;
    }

    bool operator==(const Iterator &o) const { return cur == o.cur; }
    bool operator!=(const Iterator &o) const { return cur != o.cur; }
  };

  Iterator begin() { return Iterator(this->head, this); }
  Iterator end() { return Iterator(nullptr, this); }

  void push_front(const T &element) {
    Element<T> *el = new Element<T>;
    el->data = element;
    el->prev = nullptr;
    el->next = this->head;
    if (this->head)
      this->head->prev = el;
    this->head = el;
    if (!this->tail)
      this->tail = this->head;
    ++this->_size;
  }

  void push_back(const T &element) {
    Element<T> *el = new Element<T>;
    el->data = element;
    el->prev = this->tail;
    el->next = nullptr;
    if (this->tail)
      this->tail->next = el;
    this->tail = el;
    if (!this->head)
      this->head = this->tail;
    ++this->_size;
  }

  void insert(int index, const T &element) {
    if (index < 0 || static_cast<size_t>(index) > this->_size)
      return;

    if (index == 0) {
      push_front(element);
      return;
    }
    if (static_cast<size_t>(index) == this->_size) {
      push_back(element);
      return;
    }

    Element<T> *p = this->head;
    for (size_t k = 1; k < static_cast<size_t>(index); ++k)
      p = p->next;

    Element<T> *el = new Element<T>;
    el->data = element;
    el->prev = p;
    el->next = p->next;
    p->next->prev = el;
    p->next = el;
    ++this->_size;
  }

  void pop_front() {
    if (this->_size == 0)
      return;
    --this->_size;
    Element<T> *tmp = this->head;
    this->head = this->head->next;
    if (this->head)
      this->head->prev = nullptr;
    else
      this->tail = nullptr;
    delete tmp;
  }

  void pop_back() {
    if (this->_size == 0)
      return;
    --this->_size;
    Element<T> *tmp = this->tail;
    this->tail = this->tail->prev;
    if (this->tail)
      this->tail->next = nullptr;
    else
      this->head = nullptr;
    delete tmp;
  }

  void remove(const T &elem) {
    Element<T> *cur = this->head;
    while (cur) {
      if (cur->data == elem) {
        Element<T> *nxt = cur->next;
        if (cur->prev)
          cur->prev->next = cur->next;
        else
          this->head = cur->next;
        if (cur->next)
          cur->next->prev = cur->prev;
        else
          this->tail = cur->prev;
        delete cur;
        --this->_size;
        cur = nxt;
      } else {
        cur = cur->next;
      }
    }
  }
};
