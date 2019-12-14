#include <iostream>
#include <variant>
#include <vector>
#include <optional>
#include <memory>

#include "my_iterator.h"

//TRange::const_iterator
TRange::const_iterator::const_iterator(std::shared_ptr<int> p, int step) 
        : p(p)
        , step(step) {}

TRange::const_iterator::const_iterator(const const_iterator &it)
        : p(it.p) 
        , step(it.step) {}

bool TRange::const_iterator::operator!=(const const_iterator& other) const {
    return !(*this == other);
}

bool TRange::const_iterator::operator==(const const_iterator& other) const {
    return (*p == *(other.p)) && (step == other.step);
}

int64_t TRange::const_iterator::operator*() const {
    return *p;
}

TRange::const_iterator TRange::const_iterator::operator++() {
    p = std::make_shared<int>(*p + step);
    return *this;
}

TRange::const_iterator TRange::const_iterator::operator++(int) {
    p = std::make_shared<int>(*p + step);
    return *this;
}

//TRange
TRange::TRange(int64_t N, int64_t M, int64_t s) {
    if ((s == 0) || (M == N)) {
        throw std::logic_error("(s != 0) or (M == N)");
    } else {
        this->N = N;
        this->M = M;
        this->s = s;
        if (std::abs(M - N) % s) {
            this->size = std::abs(M - N) / s;
        } else {
            this->size = std::abs(M - N) / s + 1;
        }
    }
}

bool TRange::operator==(const TRange& tR2) const {
    return (N == tR2.N) && (M == tR2.M) && (s == tR2.s);
}

std::optional<int64_t> TRange::operator[](size_t i) const {
    if ((i >= 0) && (i < size)) {
        //return std::min(N, M) + s * i;
        if (N < M) {
            return N + s * i;
        } else {
            return N - s * i;
        }
    } else {
        return std::nullopt;
    }
}

int64_t TRange::GetSize() const {
    return size;
}

int64_t TRange::Get_N() const {
    return N;
}

int64_t TRange::Get_M() const {
    return M;
}

void TRange::GetAllIntegers() const {
    for (int i = 0; i < size; ++i) {
        std::cout << this->operator[](i).value() << ' ';
    }
    std::cout << std::endl;
}

TRange::const_iterator TRange::begin() const {
    std::shared_ptr<int> begin_ptr = std::make_shared<int>(N);
    return TRange::const_iterator(begin_ptr, s);
}

TRange::const_iterator TRange::end() const {
    std::shared_ptr<int> end_ptr = std::make_shared<int>(N + size * s);
    return TRange::const_iterator(end_ptr, s);
}

//TRangeHash
size_t TRangeHash::operator()(const TRange& tR) const {
    return (tR.GetSize() >> 4) + (tR.Get_N() >> 2) + (tR.Get_M());
}
