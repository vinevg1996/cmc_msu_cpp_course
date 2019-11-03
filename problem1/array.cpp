#include <iostream>
#include <vector>

int count_arr = 0;
int count_arr_copy = 0;
int count_arr_del = 0;

template <typename T>
class Array {
private:
    T* data;
    size_t size;

public:
    Array(size_t n = 0)
        : size(n)
    {
        data = new T[n];
    }

    Array(const Array &arr)
    {
//      Copy constructor overload
        size = arr.size;
        data = new T[size];
        for (int i = 0; i < arr.size; ++i) {
            data[i] = arr.data[i];
        }
    }

    const Array& operator=(const Array &arr){
//      Operator= overload
        size = arr.size;
        data = new T[size];
        for (int i = 0; i < arr.size; ++i) {
            data[i] = arr.data[i];
        }
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
        delete[] data;
    }
};

template <typename T>
const Array<T> GetArray(size_t n, T x) {
    Array<T> A(n);
    for (size_t i = 0; i != n; ++i) {
        A[i] = x;
    }
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
    std::cout << A << "\n";

    std::vector<Array<int>> vec;
    Array<int> B(n);
    // fill vector of 100 arrays 
    for (size_t i = 0; i < 100; ++i) {
        B = GetArray<int>(n, i);
        vec.push_back(B);
        //std::cout << vec[i] << "\n";
    }
}
