#pragma once

#include "Element.hpp"
#include <cstddef>

template <typename T> class OneList {
protected:
  Element<T> *head, *tail;
  size_t _size;
public:  
  OneList() {
    head = nullptr;
    tail = nullptr;
	_size = 0;
  }
  size_t size() const { return _size; }
  Element<T> *front() { return head; }
  Element<T> *back() { return tail; }  
  bool empty() const { return _size == 0; }

  class Iterator {
    Element<T> *cur;
    OneList<T> *owner;
    Iterator(Element<T> *c, OneList<T> *o) : cur(c), owner(o) {}
    friend class OneList;
  public:
    T& operator*()  const { return cur->data; }
    T* operator->() const { return &cur->data; }

    Iterator& operator++() { cur = cur->next; return *this; }
    Iterator  operator++(int) { Iterator t(*this); ++(*this); return t; }

    Iterator& operator--() {
      if (!owner || !owner->head || cur == owner->head) return *this;
      Element<T> *p = owner->head;
      while (p->next != cur) p = p->next;
      cur = p;
      return *this;
    }
    Iterator operator--(int) { Iterator t(*this); --(*this); return t; }

    bool operator==(const Iterator &o) const { return cur == o.cur; }
    bool operator!=(const Iterator &o) const { return cur != o.cur; }
  };

  Iterator begin() { return Iterator(head,    this); }
  Iterator end()   { return Iterator(nullptr, this); }

  void push_front(T element) {
    Element<T> *el = new Element<T>;
    el->data = element;
    el->next = head;
    head = el;
    if (tail == nullptr)
      tail = head;
	_size++;
  }
  void push_back(T element) {
    Element<T> *el = new Element<T>;
    el->data = element;
    el->next = nullptr;
    if (tail != nullptr)
      tail->next = el;
    tail = el;
    if (head == nullptr)
      head = tail;
    _size++;
  }

  void insert(int index, const T &element) {
    if (index < 0 || index > _size)
      return;

    if (index == 0) {
      push_front(element);
      return;
    }

    if (index == _size) {
      push_back(element);
      return;
    }

    Element<T> *prev = head;
    for (size_t k = 1; k < index; ++k)
      prev = prev->next;

    Element<T> *el = new Element<T>;
    el->data = element;
    el->next = prev->next;
    prev->next = el;
    ++_size;
  }

  void pop_back() {
    if (_size == 0)
      return;
	_size--;
    if (head == tail) {
      delete head;
      head = nullptr;
      tail = nullptr;
	  return;
	}
    
    Element<T> *i = head;
    for (; i->next != tail; i = i->next)
      ;
    i->next = nullptr;
    delete tail;
	tail = i;
  }

  void pop_front() {
    if (_size == 0)
      return;
    _size--;
    if (head == tail) {
      delete head;      
      head = nullptr;
      tail = nullptr;
	  return;
    }
    Element<T> *i = head->next;
    delete head;
	head = i;
  }

  void remove(const T &elem) {
    while (head && head->data == elem) {
      Element<T> *tmp = head;
      head = head->next;
      delete tmp;
      --_size;
    }

    if (!head) {
      tail = nullptr;
      return;
    }

    Element<T> *cur = head;
    while (cur->next) {
      if (cur->next->data == elem) {
        Element<T> *tmp = cur->next;
        cur->next = tmp->next;
        if (tmp == tail)
          tail = cur;
        delete tmp;
        --_size;
      } else {
        cur = cur->next;
      }
    }
  }

  ~OneList() {
    while (_size > 0)
      pop_front();
  }

  OneList(const OneList &) = delete;
  OneList &operator=(const OneList &) = delete;  
};
