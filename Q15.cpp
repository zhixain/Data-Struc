#include <vector>
#include <stdlib.h>
#include <iostream>

template<class T>
class MaxHeap {
public:
    // Constructing an empty heap.
    MaxHeap() {}

    // To add an element to the heap.
    void insert(T value) {
        heap.push_back(value);
        heapifyUp();
    }

    // To remove the root element in the heap and return it.
    T extract() {
      if (heap.empty()) {
        return T();
      }
      T root = heap[0];
      heap[0] = heap.back();
      heap.pop_back();
      heapifyDown();
      return root;
    }

    // Return the number of elements in the heap.
    int count() {
        return heap.size();
    }

private:
    std::vector<T> heap;
  
    //  maintain heap property after insertion.
    void heapifyUp() {
      int index = heap.size() - 1;
      //index : current index
      while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (heap[index] > heap[parentIndex]) {
          std::swap(heap[index], heap[parentIndex]);
          index = parentIndex;
        }
        else
          break;
      }
    }

    // maintain heap property after extraction.
    void heapifyDown() {
      int index = 0;
      while (true) {
        //left : left Child Index
        //max : largestIndex
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int max = index;
        
        if (left < heap.size() && heap[left] > heap[max]) {
          max = left;
        }
        if (right< heap.size() && heap[right] > heap[max]) {
          max = right;
        }
        if (max != index) {
          std::swap(heap[index], heap[max]);
          index = max;
        }
        else
          break;
      }
    }
};

int main()
{
    MaxHeap<int> *mh = new MaxHeap<int>();
    int j;
    for(j = 0;j < 20;j++)
        mh->insert(rand() % 100);
    for(j = 0;j < 10;j ++)
        mh->extract();
    for(j = 0;j < 10;j ++)
        mh->insert(rand() % 100);
    while(mh->count())
        std::cout << mh->extract() << std::endl;
}
