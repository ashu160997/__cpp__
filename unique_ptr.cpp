#include <iostream>
#include <memory>
#include <cassert>
#include <utility>
#include <vector>


template <typename T>
class unique_ptr
{
   private:
   T* t;
   public:
   unique_ptr():t(nullptr){}
   unique_ptr(T* ptr):t(ptr){}
   unique_ptr(const unique_ptr& u)=delete;
   unique_ptr& operator=(const unique_ptr& )=delete;

   unique_ptr(unique_ptr&& u):t(nullptr)
   {
    std::swap(t,u.t);
   }

   T& operator*()
   {
       return *t;
   }

   T* operator->()
   {
     return t;
   }

   T* get()
   {
      return t;
   }

   void reset(T* other)
   {
     if(t==other)
     return;

     delete_underlying_ptr();
     std::swap(t,other);
   }

   void delete_underlying_ptr()
   {
    if(t!=nullptr)
    {
        delete t;
        t=nullptr;
    }
   }

   T* release()
   {
    T* temp=t;
    t=nullptr;
    return temp;
   }

   ~unique_ptr()
   {
    delete_underlying_ptr();
   }

};