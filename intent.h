#include <vector>
#include <iostream>
#include <tuple>
namespace intent
{
  namespace utility
  {
    template<size_t dimcount, typename T>
      struct multidimensional_vector
      {
        typedef std::vector< typename multidimensional_vector<dimcount-1, T>::type > type;
      };

    template<typename T>
      struct multidimensional_vector<0,T>
      {
        typedef T type;
      };
  }


  template<size_t dimcount = 2, typename T = int>
  class Grid
  {


    using bbox = std::tuple<int,int,int,int>;
  public:
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
