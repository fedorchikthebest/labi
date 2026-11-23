#include "DoubleList.hpp"
#include "OneList.hpp"
#include <cctype>
#include <iostream>

template <typename LINKEDLIST> void print_list(LINKEDLIST &list);

template <typename LINKEDLIST> void insert_chars(LINKEDLIST &list) {

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

    print_list(list);
    for (int j = 0; j < i; j++)
      std::cout.put(' ');
    std::cout.put('^');
	std::cout.put('\n');
  }

  if (mpos1 == -1)
    return;

  list.insert(mpos2 + 1, '#');
  list.insert(mpos1, '$');
}

template <typename LINKEDLIST> void print_list(LINKEDLIST &list) {
  for (auto i = list.begin(); i != list.end(); ++i) {    
    std::cout.put(*i);
  }
  std::cout.put('\n');
}  

template <typename LINKEDLIST> void read(LINKEDLIST &list) {
  char c;
  std::cin.get(c);
  while (std::cin.get(c)) {
    if (c == '\n')
      break;
    list.push_back(c);
  }
}

template <typename LINKEDLIST> void menu() {
  char c;
  int punkt, index;
  LINKEDLIST list;
  while (true) {
    std::cin >> punkt;
    switch (punkt) {
    case 1: // Ввод массива
      read<LINKEDLIST>(list);
	  break;
    case 2: // Вывод массива
      print_list<LINKEDLIST>(list);
      break;
    case 3: // Расчет массива
      insert_chars<LINKEDLIST>(list);
	  break;
    case 4:
      std::cout << list.size() << std::endl;      
      break;
    case 5:
      std::cout << list.empty() << std::endl;      
      break;
    case 6:
      list.pop_back();
      break;
    case 7:
      list.pop_front();
      break;
    case 8:
      std::cout << list.front() << std::endl;      
      break;
    case 9:
      std::cout << list.back() << std::endl;      
      break;
    case 10:
      std::cin.get(c);      
      std::cin >> c;
      list.push_back(c);
      break;
    case 11:
      std::cin.get(c);      
      std::cin >> c;
      list.push_front(c);
      break;
    case 12:
      std::cin >> index;      
	  std::cin.get(c);
	  std::cin >> c;
      list.insert(index, c);
      break;
    case 13:
      std::cin.get(c);      
      std::cin >> c;
      list.remove(c);
      break;
    case 0:
      return;      
	}      
  }    
}

int main() {
  int num;

  while (1) {
    std::cin >> num;
    switch (num) {
    case 1:
      menu<OneList<char>>();
      break;
    case 2:
      menu<DoubleList<char>>();
    }
  }
}
