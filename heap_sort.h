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
max_pq_heap(size_t capacity) : pq_(capacity + 1){

}

bool empty() const {
    return pq_.empty();
}

void insert(const T& value, const comparator<T>& comp){
    pq_.push_back(value);
    swim(pq_.size(), comp);
}

T delMax(){
    T& maximum = pq_[1];
    size_t n = pq_.size();
    exchange(1, n);
    pq_.pop_back();
    sink(1);
    pq_[n+1] = T();
    return maximum;
}
void swim(size_t k, const comparator<T>& comp){
    while(k > 1 && less(k/2, k, comp)){
        exchange(k, k/2);
        k /= 2;
    }
}
void sink(size_t k, const comparator<T>& comp){
    size_t n = pq_.size();
    while(2 * k <= n){
        size_t j = 2 * k;
        if (j < n && less(j, j + 1, comp)){
            j++;
        }
        if(!less(k, j, comp)){
            break;
        }
        exchange(k, j);
        k = j;
    }
}


private: 
static const size_t MIN_CAPACITY_;
void exchange(size_t i , size_t j){
    T& temp = pq_[i]; 
    pq_[i] = pq_[j];
    pq_[j] = temp;
}
bool less(size_t i, size_t j, const comparator<T>& comp){
    return less(pq_[i], pq_[j], comp);
}
array_<T> pq_;
};

template<typename T>
const size_t max_pq_heap<T>::MIN_CAPACITY_ = 10;

#endif 

