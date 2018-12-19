#include <vector>
#include <iostream>
#include <tuple>
#include <limits>
namespace intent
{
  namespace utility
  {
    template <size_t I,typename T> 
      struct tuple_n{
        template< typename...Args> using type = typename tuple_n<I-1, T>::template type<T, Args...>;
      };

    template <typename T> 
      struct tuple_n<0, T> {
      template<typename...Args> using type = std::tuple<Args...>;
    };
    template <size_t I,typename T>  using tuple_of = typename tuple_n<I,T>::template type<>;

    class default_t
    {
    public:
      template<typename T>
        operator T() const {return T();}
    };
    default_t const defaultVal=default_t();

    template <size_t dimcount, typename T>
      struct multidimensional_vector
      {
        typedef std::vector< typename multidimensional_vector<dimcount-1, T>::type > type;

      };

    template<typename T>
      struct multidimensional_vector<0,T> 
      {
        typedef T type;
      };

    template <size_t dim, typename T, typename V>
      void defInit(int size, T val, std::vector<T>& v)
    {
      v=std::vector<T>(size,val);
    }

    template <size_t dim, typename T, typename V>
      void defInit(int size, T val, V& v)
    {
      v=std::vector<typename intent::utility::multidimensional_vector<(dim - 1), T>::type>(size);
       for (int i=0; i< size; ++i)
         defInit<dim-1,T,decltype(v[i])>(size,val,v[i]);
    }

 


  }


  template<size_t dimcount = 2, typename T = int>
  class Grid
  {

    /* TODO: initialization of v */
    /* TODO parameter for the constructor */
  public:
    Grid()
    {
    }
    Grid(const utility::default_t &t)
    {
    }

    /* Todo get a stream as parameter */
    void printDebugInfo()
    {
      std::cout << "Dimension: " << dimcount << std::endl;
      std::cout << "Type (warning, implementation-defined, might make no sense!): " << typeid(T).name() << std::endl;
    }
  private:
  utility::tuple_of<dimcount,int> _corners;
  typename intent::utility::multidimensional_vector<dimcount,T>::type v;
  };
}
