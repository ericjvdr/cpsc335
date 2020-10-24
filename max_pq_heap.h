//
//  max_pq_heap.h
//  sorts
//
//  Created by William McCarthy on 2310//20.
//

#ifndef max_pq_heap_h
#define max_pq_heap_h

#include "array.h"

#define MIN_CAPACITY 3

//------------------------------------------------------
template <typename T>
class max_pq_heap {
public:
  max_pq_heap() : max_pq_heap(MIN_CAPACITY_) { }
  max_pq_heap(const comparator<T>& compar) : max_pq_heap(MIN_CAPACITY, compar) { }
  max_pq_heap(size_t capacity, const comparator<T>& compar)
  : pq_(capacity + 1), comp(compar) { pq_.push_back(T()); }  // make space for skipped-over 0 entry
  
  max_pq_heap(const std::initializer_list<T>& li, const comparator<T>& compar)
  : max_pq_heap(li.size(), compar) {
    for (const T& el : li) {
      if (el != "-") { insert(el);
      } else { std::cout << del_max() << " "; }
    }
    std::cout << "\t(" << size() << " left on the heap)\n\n";\
  }

  bool empty() const { return pq_.size() == 1; }   // leaves 0 index empty
  size_t size() const { return pq_.size() - 1; }   // ditto

  void insert(const T& value) {
    pq_.push_back(value);
    swim(size());
  }
  T del_max() {
    T maximum = pq_[1];
    size_t n = size();
    
    exchange(1, n);
    pq_.pop_back();
    sink(1);
    pq_[n] = T();
    return maximum;
  }
  void swim(size_t k) {
    while (k > 1 && less(k / 2, k)) {
      exchange(k, k / 2);
      k /= 2;
    }
  }
  void sink(size_t k) {
    size_t n = size();

    while (2 * k <= n) {
      size_t j = 2 * k;
      if (j < n && less(j, j + 1)) { ++j; }
      if (!less(k, j)) { break; }

      exchange(k, j);
      k = j;
    }
  }
  friend std::ostream& operator<<(std::ostream& os, const max_pq_heap& maxpq) {
    if (maxpq.empty()) { return os << "max_pq_heap is empty\n"; }
    return os << maxpq.pq_ << "\n";
  }

private:
  static const size_t MIN_CAPACITY_;
  
  void exchange(size_t i, size_t j) {
    T temp = pq_[i];
    pq_[i] = pq_[j];
    pq_[j] = temp;
  }
  bool less(size_t i, size_t j) {
    return ::less(pq_[i], pq_[j], comp);
  }
  array_<T> pq_;                // uses expandable array from array.h, not std::array<T>
  const comparator<T>& comp;
};

#endif /* max_pq_heap_h */
