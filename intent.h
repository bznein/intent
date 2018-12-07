#include <vector>
#include <iostream>
#include <tuple>
#include <limits>
namespace intent
{
  namespace utility
  {

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


    using bbox = std::tuple<int,int,int,int>;
  public:

    Grid()
    {
      _corners=bbox(0,0,std::numeric_limits<int>::max(),std::numeric_limits<int>::max());
    }
    Grid(const utility::default_t &t)
    {
      _corners=bbox(0,0,std::numeric_limits<int>::max(),std::numeric_limits<int>::max());
    }
    Grid(int minX, int minY, int maxX, int maxY)
      {
        _corners=bbox(minX,minY,maxX,maxY);
      };

    /* Todo get a stream as parameter */
    void printDebugInfo()
    {
      std::cout << "Dimension: " << dimcount << std::endl;
      std::cout << "Type (warning, implementation-defined, might make no sense!): " << typeid(T).name() << std::endl;
    }
  private:
    bbox _corners;
    utility::multidimensional_vector<dimcount,T> v;
  };
};
