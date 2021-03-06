#include <memory>
#include <exception> 

namespace usu
{
    template <typename T>
    class shared_ptr
    {
      public:
        //default
        shared_ptr<T>()
        {
            count = new std::uint64_t(1);
        }

        //parameter
        shared_ptr<T>(T* ptr)
        {
            this->ptr = ptr;
            count = new std::uint64_t(1);
        }

        //copy constructor
        shared_ptr<T>(shared_ptr& obj)
        {
            this->ptr = obj.get();
            count = obj.getCount();
            //obj.setCount(obj.use_count() + 1);
            *count = *count + 1;
        }

        //move constructor
        shared_ptr<T>(shared_ptr&& obj) noexcept
        {
            this->ptr = obj.get();
            count = obj.getCount();
        }

        //deconstructor
        ~shared_ptr()
        {
            if (count == 0)
            {
                delete this;
            }
            else
            {
                count--;
            }
        }

        //copy operator
        shared_ptr& operator=(shared_ptr& rhs)
        {
            *count = *count - 1;
            count = rhs.getCount();
            this->ptr = rhs.get();
            //rhs.setCount(rhs.use_count() + 1);
            *count = *count + 1;
            return *this;
        }

        //move operator
        shared_ptr& operator=(shared_ptr&& rhs)
        {
            count = rhs.getCount();
            this->ptr = rhs.get();

            return *this;
        }

        T* operator->()
        {
            return ptr;
        }

        T& operator*()
        {
            return *ptr;
        }

        T* get()
        {
            return ptr;
        }

        void setCount(uint64_t value)
        {
            *count = value;
        }

        std::uint64_t use_count()
        {
            return *count;
        }

        std::uint64_t* getCount()
        {
            return count;
        }

      private:
        std::uint64_t* count;
        T* ptr;
    };

    template <typename T>
    class shared_ptr<T[]>
    {
      public:
        shared_ptr<T[]>()
        {
        }

        shared_ptr<T[]>(T* ptr, std::uint64_t num)
        {
            this->ptr = ptr;
            sizeOfArray = new std::uint64_t(num);
		}

        ~shared_ptr<T[]>()
        {
            //delete this;
        }

        T& operator[](std::uint64_t location)
        {
			return ptr[location];
        }

        std::uint64_t size()
        {
            return *sizeOfArray;
        }

      private:
        std::uint64_t* sizeOfArray;
        T* ptr;
    };

    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args&&... args)
    {
        return shared_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template <typename T, unsigned int N>
    shared_ptr<T[]> make_shared_array()
    {
        return shared_ptr<T[]>(new T[N], N);
    }
} // namespace usu
//initialize outside of class
//Do I need to initialize the array?
//std::initializer_list???
//delete the object not the ptr??
