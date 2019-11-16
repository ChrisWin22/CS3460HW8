

namespace usu
{
template<typename T>
	class shared_ptr{
		
		shared_ptr<T>(){
			
		}
		shared_ptr<T>(T*) {

		}


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

