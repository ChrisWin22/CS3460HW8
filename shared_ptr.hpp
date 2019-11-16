#include <memory>


namespace usu
{
template<typename T>
	class shared_ptr{
	  public:
			shared_ptr<T>(){
			
			}

			shared_ptr<T>(T* ptr)
            {
            }

			~shared_ptr() {
                if (count == 0)
                {
                    delete this;
                }
                else
                {
                    count--;
				}
			}

			T* operator->() {

			}

			T& operator* ()
            {

            }

			T* get() {
			}

			std::uint64_t use_count() {
                return count;
			}

       private:
            std::uint64_t* count;
	};

	template <typename T>
    class shared_ptr<T[]>
    {
      public:
		shared_ptr<T>(T[]* ptr, std::uint64_t numOfElements) {

		}

		T operator[](std::uint64_t location) {

		}

		std::uint64_t size() {
            return size;
		}

	  private:
        std::uint64_t size;
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
}

