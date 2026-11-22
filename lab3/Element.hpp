#pragma once

template <typename T> class Element {
public:
  Element<T> *next, *prev;  
  T data;  
};
