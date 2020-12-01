#ifndef POOL_H
#define POOL_H

template <typename T>
class Pool {
    public:
        int size;
        T* pool;
        Pool<T>(int size);
};

#endif
