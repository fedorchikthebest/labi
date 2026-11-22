#pragma once

template <typename T> class Element {
public:
  T *next, *prev;
  T data;  
};
