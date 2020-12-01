#ifndef POOL_H
#define POOL_H

template <typename T>
class Pool {
    protected:
        int index;
    public:
        int size;
        T* pool;
        Pool<T>(int size);
};

#endif
