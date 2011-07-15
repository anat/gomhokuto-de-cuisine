#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <boost/thread.hpp>
#include <boost/bind.hpp>

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

    enum {
        ARRAY_SIZE = SIZE
    };

    Array()
    {}

    Array(const Array& value) {
        this->operator =(value);
    }

    ~Array() {}

    Array& threadAssign(const Array& orig) {
        if (this != &orig) {
            boost::thread_group threadGroup;

            for (unsigned int i = 0; i < SIZE; ++i) {
                threadGroup.create_thread(
                        boost::bind(&Array::assign, this, i, boost::ref(orig[i]))
                        );
            }
            threadGroup.join_all();
        }
        return *this;
    }

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

    void assign(unsigned int i, const T& orig) {
        _array[i] = orig;
    }

    T _array[SIZE];
};

#endif // ARRAY_HPP
