#include <vector>
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


  template<size_t dimcount, typename T>
  class Grid
  {


    using bbox = std::tuple<int,int,int,int>;
  public:
    Grid(int minX, int minY, int maxX, int maxY)
      {
        _corners=bbox(minX,minY,maxX,maxY);
      };
  private:
    bbox _corners;
    utility::multidimensional_vector<dimcount,T> v;
  };
};
