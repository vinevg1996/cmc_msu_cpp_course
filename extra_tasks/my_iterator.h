#ifndef MY_ITERATOR
#define MY_ITERATOR

#include <cmath>
#include <optional>
#include <iterator>
#include <memory>
#include <unordered_set>

class TRange {
    int64_t N;
    int64_t M;
    int64_t s;
    int64_t size;

public:
    class const_iterator {
        std::shared_ptr<int> p;
        int step;

        const_iterator(std::shared_ptr<int> p, int step);

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = int64_t;
        using difference_type = int64_t;
        using pointer = int64_t*;
        using reference = int64_t&;

        const_iterator(const const_iterator& it);
        bool operator!=(const const_iterator& other) const;
        bool operator==(const const_iterator& other) const;
        int64_t operator*() const;
    	const_iterator operator++();
    	const_iterator operator++(int);

    	friend TRange;
    };

    TRange(int64_t N, int64_t M, int64_t s);
    
    bool operator==(const TRange& tR2) const;
    std::optional<int64_t> operator[](size_t i) const;
    int64_t GetSize() const;
    int64_t Get_N() const;
    int64_t Get_M() const;
    void GetAllIntegers() const;
    const_iterator begin() const;
    const_iterator end() const;
};

class TRangeHash {
public:
    size_t operator()(const TRange& tR) const;
};

#endif
