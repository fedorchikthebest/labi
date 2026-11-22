#include "DoubleList.hpp"
#include <cctype>
#include <iostream>
#define LINKEDLIST OneList<char>

void insert_chars(LINKEDLIST &list) {

  auto it2 = list.begin();
  auto it3 = it2;
  ++it3;
  auto it1 = it2;

  int i = 1;
  bool have_it1 = false;

  int mpos1 = -1, mpos2 = -1;
  int pos1 = 0, pos2 = 0;
  int best = 0;

  for (; it3 != list.end(); ++it2, ++it3, ++i) {
    char a = *it2;
    char b = *it3;

    if (std::isdigit((unsigned char)a) && std::isdigit((unsigned char)b) &&
        b > a) {

      bool start_new = (i == 1) || !have_it1;
      if (!start_new) {
        char c = *it1;
        if (!std::isdigit((unsigned char)c) || c > a)
          start_new = true;
      }

      if (start_new)
        pos1 = i - 1;
      pos2 = i;

      if (pos2 - pos1 > best) {
        best = pos2 - pos1;
        mpos1 = pos1;
        mpos2 = pos2;
      }
    }

    it1 = it2;
    have_it1 = true;
  }

  if (mpos1 == -1)
    return;

  list.insert(mpos2 + 1, '#');
  list.insert(mpos1, '$');
}

int main() {
  char c;
  LINKEDLIST list;
  while (std::cin.get(c)) {
    if (c == '\n')
      break;
    list.push_back(c);
  }
  insert_chars(list);

  for (auto i = list.begin(); i != list.end(); ++i) {
    std::cout.put(*i);
  }
  std::cout.put('\n');
}
