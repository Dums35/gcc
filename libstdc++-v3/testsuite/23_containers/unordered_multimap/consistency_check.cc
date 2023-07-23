// { dg-do run { target c++11 } }

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

#include <testsuite_hooks.h>

namespace
{
  const int nb_elements = 1000;
  const int nb_copies = 5;

  template<typename _ElemType>
  void check(const std::unordered_multimap<_ElemType, int>& um)
    {
      VERIFY( std::distance(um.begin(), um.end()) == um.size() );
      std::size_t bkt_elems_count = 0;
      for (std::size_t i = 0; i != um.bucket_count(); ++i)
	{
	  if (um.bucket_size(i) == 0)
	    continue;

	  bkt_elems_count += um.bucket_size(i);
	  for (auto lit = um.begin(i); lit != um.end(i); ++lit)
	    {
	      VERIFY( um.bucket(lit->first) == i );
	    }
	}

      VERIFY( bkt_elems_count == um.size() );
    }

  template<typename _ElemType>
    void run(const std::vector<_ElemType>& elems, bool with_copy)
    {
      std::unordered_multimap<_ElemType, int> um;
      um.max_load_factor(nb_copies);
      check(um);

      for (int h = 0; h != nb_copies; ++h)
	for (int i = 0; i != nb_elements; ++i)
	  {
	    um.insert({ elems[i], i + i * h });
	    check(um);
	  }

      if (with_copy)
	{
	  std::unordered_multimap<_ElemType, int>(um).swap(um);
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
