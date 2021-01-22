#ifndef POOL_H
#define POOL_H

template <typename T>
class Pool {
    protected:
        int index;
        T* pool;
    public:
        int size;
        Pool<T>(int size);
        T& operator[](int);
};

#endif
