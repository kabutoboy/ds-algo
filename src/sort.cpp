#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <vector>

struct Item {
  int key;
  int data;
};

typedef std::vector<Item*> ItemList;

ItemList binaryInsertToSorted(const ItemList &list, Item *item) {
  ItemList sorted(list);
  int left = 0;
  int right = sorted.size();
  while (right > left) {
    int i = left + (right - left) / 2;
    if (sorted[i]->key < item->key) {
      left = i + 1;
    } else if (sorted[i]->key > item->key) {
      right = i;
    } else {
      sorted.insert(sorted.begin() + i, item);
      return sorted;
    }
  }
  sorted.insert(sorted.begin() + left, item);
  return sorted;
}

ItemList insertToSorted(const ItemList &list, Item *item) {
  ItemList sorted(list);
  for (int i = 0; i < sorted.size(); i++) {
    if (sorted[i]->key > item->key) {
      sorted.insert(sorted.begin() + i, item);
      return sorted;
    }
  }
  sorted.push_back(item);
  return sorted;
}

ItemList insertionSort(const ItemList &list) {
  ItemList sorted;
  sorted.push_back(list[0]);
  for (int i = 1; i < list.size(); i++) {
    sorted = insertToSorted(sorted, list[i]);
  }
  return sorted;
}

ItemList binaryInsertionSort(const ItemList &list) {
  ItemList sorted;
  sorted.push_back(list[0]);
  for (int i = 1; i < list.size(); i++) {
    sorted = binaryInsertToSorted(sorted, list[i]);
  }
  return sorted;
}

void printList(const ItemList &list) {
  for (auto &it : list) {
    std::cout << it->key << ", ";
  }
  std::cout << "\n";
}

void timeIt(std::function<void()> action) {
  std::clock_t start;
  double duration;
  start = std::clock();

  action();

  duration = (std::clock() - start);
  std::cout << "used " << duration << "ms\n";
}

ItemList randomList(int n) {
  ItemList list;
  for (int i = 0; i < n; i++) {
    Item *item = new Item;
    item->key = std::rand() % n;
    item->data = item->key;
    list.push_back(item);
  }
  return list;
}

int main() {
  std::srand(std::time(0));

  int n;
  std::cout << "Enter n: ";
  std::cin >> n;

  for (int i = n; i <= n; i++) {
    ItemList list = randomList(i);
    // std::cout << "\n";
    // std::cout << "Before sorting\n";
    // printList(list);

    // std::cout << std::setw(30) << "insertion sort ";
    // timeIt([&list]() {
    //   insertionSort(list);
    //   // printList(insertionSort(list));
    // });
    //
    // std::cout << std::setw(30) << "binary insertion sort ";
    // timeIt([&list]() {
    //   binaryInsertionSort(list);
    //   // printList(binaryInsertionSort(list));
    // });

    std::cout << std::setw(30) << "std sort ";
    timeIt([&list]() {
      std::sort(list.begin(), list.end(), [](const auto &a, const auto &b) {
        return a->key < b->key;
      });
    });
  }

  return 0;

}
