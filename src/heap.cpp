#include <cmath>
#include <iostream>
#include <vector>

struct Item {
  int key;
  int data;
};

typedef std::vector<Item> ItemList;

class MinHeap {
public:
  MinHeap(const ItemList &given) : list{given} {
  }
  void insert(Item &item) {
    list.push_back(item);
    makeHeap();
  }
  Item min() { return list[0]; }
  void print() {
    for (auto &item : list) {
      std::cout << item.key << " ";
    }
    std::cout << "\n";
  }

protected:
  void makeHeap() {
    for (int i = list.size() / 2 - 1; i >= 0; i--) {
      heapify(i);
    }
  }
  void heapify(int i) {
    if (i > list.size() / 2) {
      return;
    }
    int least = minKeyIndex(left(i), right(i));
    if (list[i].key > list[least].key) {
      swap(i, least);
      heapify(least);
    }
  }
  void swap(int i, int j) {
    std::cout << "swap(" << i << ", " << j << ")\n";
    if (i < 0 || j < 0 || i >= list.size() || j >= list.size()) {
      return;
    }
    auto tmp = list[i];
    list[i] = list[j];
    list[j] = tmp;
  }
  int left(int i) { return (i + 1) * 2 - 1; }
  int right(int i) { return (i + 1) * 2; }
  int minKeyIndex(int i, int j) {
    if (i >= list.size()) {
      return j;
    }
    if (j >= list.size()) {
      return i;
    }
    if (list[i].key < list[j].key) {
      return i;
    }
    return j;
  }
  int parent(int i) { return (i + 1) / 2 - 1; }

  ItemList list;
};

int main() {
  int n;
  std::cin >> n;
  ItemList list;
  for (int i = 0; i < n; i++) {
    int j;
    std::cin >> j;
    list.push_back({j, j});
  }
  MinHeap heap(list);
  heap.print();
}
