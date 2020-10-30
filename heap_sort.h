//heap sort 
// maxpq

#ifndef heap_sort_h
#define heap_sort_h



#include <functional>
#include "array.h"

template <typename T>
class heap {
    public: 
    static void sort(T* pq, size_t len, const comparator<T>& comp=fwd_comparator<T>()) {
        for (size_t k = len/2; k >= 1; k--){
            sink(pq, k, len, comp);
        }
        size_t k = len;
        while (k > 1){
            exchange(pq, 1, k--);
            sink(pq, 1, k, comp);
        }
    }
    static void sink(T* pq, size_t k, size_t len, const comparator<T>& comp){
        while( 2 * k <= len){
            size_t j = 2 * k;
            if (j < len && less(pq, j, j + 1, comp)){
                j++;
            }
            if(!less(pq, k, j, comp)){
                break;
            }
            exchange(pq, k, j);
            k = j;
        }
    }
    private:
    static void exchange(T* pq, size_t i, size_t j){
        T temp = std::move(pq[i-1]);
        pq[i-1] = std::move(pq[j-1]);
        pq[j-1] = std::move(temp);
        
    }
    static bool less(T* pq, size_t i, size_t j, const comparator<T>& comp){
        return ::less(pq[i-1], pq[j-1], comp);
    }
};

template <typename T>
class max_pq_heap{
public: 
max_pq_heap() : max_pq_heap(MIN_CAPACITY_){

}
max_pq_heap(const comparator<T>& compar) : max_pq_heap(MIN_CAPACITY, compar) {

}
 max_pq_heap(size_t capacity, const comparator<T>& compar) : pq_(capacity + 1), comp(compar) { 
      pq_.push_back(T()); 
  }  

~max_pq_heap() {

   }
T max() const {
    if (empty()) { 
    throw new std::underflow_error("no such element\n"); 
    }
    return pq_[1];
}

bool empty() const {
   return pq_.size() == 1; 
}
size_t size() const{
    return pq_.size() - 1;
}
 void clear() {
  
    while (!empty()) {
      del_Max();
    }
  
  }

void insert(const T& value){
    pq_.push_back(value);
    swim(size());
}

T del_Max(){

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
static void test_file(const std::string& filename, const comparator<std::string>& compar= fwd_comparator<std::string>()) {
    
    std::cout << "\n//======================================================\nTesting max_pq_heap with filename: '" << filename << "'...\n";

    max_pq_heap<std::string> pqheap(compar);
    std::string s;
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
      std::cerr << "Could not open file: '" << filename << "'\n";
      throw new std::invalid_argument("invalid filename\n");
    }
    
    while (ifs >> s) {
      if (s != "-") { pqheap.insert(s);
      } else {
        std::cout << pqheap.del_Max() << " ";
      }
    }
    std::cout << "\t(" << pqheap.size() << " left on the heap)\n\n";
    ifs.close();
  }


private: 
static const size_t MIN_CAPACITY_;
void exchange(size_t i , size_t j){
    T temp = pq_[i]; 
    pq_[i] = pq_[j];
    pq_[j] = temp;
}
bool less(size_t i, size_t j){
   return ::less(pq_[i], pq_[j], comp);
}
bool is_max_heap() const {
    size_t n = size();
    for (size_t i = 0; i < n; ++i) {
      if (pq_[i] == T()) { 
          return false; 
          }
    }
    for (size_t i = n + 1; i < size(); ++i) {
      if (pq_[i] != T()) { 
          return false; 
          }
    }
    if (pq_[0] != T()) { 
        return false; 
        }
    return is_max_heap_ordered(1);
  }

  bool is_max_heap_ordered(size_t k) {
    size_t n = size();
    if (k > n) { 
        return true; 
        }
    size_t left = 2 * k;
    size_t right = left + 1;
    
    if (left  <= n && less(k, left))  { 
        return false; 
        }
    if (right <= n && less(k, right)) { 
        return false; 
        }

    return is_max_heap_ordered(left) && is_max_heap_ordered(right);
  }

private:
  array_<T> pq_;              
  const comparator<T>& comp;
};

#endif 

