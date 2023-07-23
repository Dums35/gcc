// { dg-do run { target c++11 } }

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

#include <testsuite_hooks.h>

namespace
{
  const int nb_elements = 2000;

  template<typename _ElemType>
  void check(const std::unordered_map<_ElemType, int>& us)
    {
      VERIFY( std::distance(us.begin(), us.end()) == us.size() );
      std::size_t bkt_elems_count = 0;
      for (std::size_t i = 0; i != us.bucket_count(); ++i)
	{
	  if (us.bucket_size(i) == 0)
	    continue;

	  bkt_elems_count += us.bucket_size(i);
	  for (auto lit = us.begin(i); lit != us.end(i); ++lit)
	    {
	      VERIFY( us.bucket(lit->first) == i );
	    }
	}

      VERIFY( bkt_elems_count == us.size() );
    }

  template<typename _ElemType>
    void run(const std::vector<_ElemType>& elems, bool with_copy)
    {
      std::unordered_map<_ElemType, int> um;
      check(um);

      for (int i = 0; i != nb_elements; ++i)
	{
	  um.insert({ elems[i], i });
	  check(um);
	}

      if (with_copy)
	{
	  std::unordered_map<_ElemType, int>(um).swap(um);
	  check(um);
	}

      for (int i = nb_elements - 1; i >= 0; --i)
	{
	  auto it = um.find(elems[i]);
	  if (it != um.end())
	    {
	      um.erase(it);
	      check(um);
	    }
	}

      um.insert({ elems[0], 0 });
      check(um);

      for (int i = nb_elements - 1; i >= 0; --i)
	{
	  um.insert({ elems[i], i });
	  check(um);
	}

      for (int j = nb_elements - 1; j >= 0; --j)
	{
	  um.erase(elems[j]);
	  check(um);
	}
    }
}

int main()
{
  {
    std::vector<int> elems;
    elems.reserve(nb_elements);
    for (int i = 0; i != nb_elements; ++i)
      elems.push_back(i);

    run(elems, false);
    run(elems, true);
  }

  {
    std::vector<std::string> elems;
    {
      elems.reserve(nb_elements);
      for (int i = 0; i != nb_elements; ++i)
	{
	  std::ostringstream ostr;
	  ostr << "string #" << i << ' ' << std::string(1000, 'a' + i);
	  elems.push_back(ostr.str());
	}
    }

    run(elems, false);
    run(elems, true);
  }

  return 0;
}
