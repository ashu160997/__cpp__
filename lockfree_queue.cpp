#include <iostream>
#include <array>
#include <atomic>
#include <utility>
#include <thread>

template<typename T,size_t size>
class LockFreeQueue{
    private:
    static constexpr size_t getpositionAfter(size_t pos)
    {
        return ++pos==ringbuffersize ? 0 : pos;
    }
    std:array<T,ringbuffersize> buffer;
    std::atomic<size_t> readpos;
    std::atomic<size_t> writepos;
    static constexpr size_t ringbuffersize=size+1;
    public:
    LockFreeQueue()
    {
        readpos.store(0);
        writepos.store(0);
    }
    bool push(const T& newElement)
    {
        auto oldwritepos=writepos.load();
        auto newwritepos=getpositionAfter(oldwritepos);
        if(newwritepos==readpos.load())
        return false;

        buffer[oldwritepos]=newElement;
        writepos.store(newwritepos);
        return true;
    }
    bool pop(T& returnedElement)
    {
        auto oldreadpos=readpos.load();
        auto oldwritepos=writepos.load();
        if(oldreadpos==oldwritepos)
        return false;

        returnedElement=buffer(oldreadpos);
        readpos.store(getpositionAfter(oldreadpos));
        return std::move(returnedElement);

        return true;
    }
    
};

int main()
{
    return 0;
}
