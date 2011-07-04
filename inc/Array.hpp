#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>
#include <algorithm>

class ArrayException : public std::exception
{
public:
    const char* what() const throw()
    {
        return "Index Out of Bound";
    }
};

template <class T, std::size_t SIZE>
class Array
{
public:
    typedef T Type;

    Array()
    {}

    Array(const Array& value) {
        for (unsigned int i = 0; i < SIZE; ++i) {
            _array[i] = value[i];
        }
    }

    ~Array() {}

    Array& operator=(const Array& orig) {
        if (this != &orig){
            for(unsigned int i = 0; i < SIZE; ++i){
                _array[i] = orig[i];
            }
        }
        return *this;
    }

    T& operator[](unsigned int i) {
        if (i >= SIZE)
            throw ArrayException();
        return _array[i];
    }

    const T& operator[](unsigned int i) const {
        if (i >= SIZE)
            throw ArrayException();
        return _array[i];
    }

    std::size_t size() const {
        return SIZE;
    }

    const T* data() const {
        return _array;
    }

private:
    T _array[SIZE];
};

#endif // ARRAY_HPP
