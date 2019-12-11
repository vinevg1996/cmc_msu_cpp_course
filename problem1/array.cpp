#include <iostream>
#include <vector>
#include <memory>
#include <utility>

template <typename T>
class Array {
private:
    T* data;
    size_t size;

public:
    Array(size_t n = 0) 
        : size(0) 
        , data(nullptr) {}

    Array(size_t n, T x) 
            : size(n) {
        data = new T[n];
        for (size_t i = 0; i != n; ++i) {
            data[i] = x;
        }
    }
    
    Array(const Array &arr) = delete;
    const Array& operator=(const Array &arr) = delete;

    Array(Array &&arr)
            : size(arr.size)
            , data(arr.data) {
        //std::cerr << __FILE__ << " " << __LINE__ << std::endl;
        arr.data = nullptr;
        arr.size = 0;
    }

    Array& operator=(Array &&arr){
        //std::cerr << __FILE__ << " " << __LINE__ << std::endl;
        if (&arr == this) {
            return *this;
        }
        //this->~Array();
        if (data) {
        	delete[] data;
        	size = 0;
        	data = nullptr;
        }
        data = arr.data;
        size = arr.size;
        //std::swap(arr.data, data);
        //std::swap(arr.size, size);
        
        arr.data = nullptr;
        arr.size = 0;
        //return std::move(*this);
        return *this;
    }

    T& operator[](size_t i) {
        if ((i >= 0) && (i < size)) {
            return data[i];
        }
    }

    const T& operator[](size_t i) const {
        if ((i >= 0) && (i < size)) {
            return data[i];
        }
    }

    const size_t GetSize() const {
        return size;
    }

    ~Array() {
        if (data) {
            //std::cerr << __FILE__ << " " << __LINE__ << std::endl;
            delete[] data;
            data = nullptr;
            size = 0;
        }
    }
};

template <typename T>
Array<T> GetArray(size_t n, T x) {
    Array<T> A(n, x);
    return A;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Array<T>& A) {
    for (size_t i = 0; i != A.GetSize(); ++i) {
        out << A[i] << " ";
    }
    out << "\n";
    return out;
}

int main() {
    size_t n;
    std::cin >> n;
    Array<int> A(n);
    A = GetArray<int>(n, 0);
    // print the array
    std::cout << "size = " << A.GetSize() << "\n";
    std::cout << A << "\n";
    
    std::vector<Array<int>> vec;
    Array<int> B(n);
    // fill vector of 100 arrays 
    for (size_t i = 0; i < 100; ++i) {
        B = GetArray<int>(n, i);
        vec.push_back(std::move(B));
        //std::cout << vec[i];
    }
    
    return 0;
}
