#ifndef POOL_H
#define POOL_H

template <typename T>
class Pool {
    protected:
        int index;
        T* pool;
    public:
        int size;
        __host__ Pool<T>(int size);
        __device__ T& operator[](int);
};

#endif
