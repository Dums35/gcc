// { dg-do run { target c++11 } }

#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>

#include <testsuite_hooks.h>

namespace
{
  const int nb_elements = 2000;

  template<typename _ElemType>
    void check(const std::unordered_set<_ElemType>& us)
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
	      VERIFY( us.bucket(*lit) == i );
	    }
	}

      VERIFY( bkt_elems_count == us.size() );
    }

  template<typename _ElemType>
    void run(const std::vector<_ElemType>& elems, bool with_copy)
    {
      std::unordered_set<_ElemType> us;
      check(us);

      for (int i = 0; i != nb_elements; ++i)
	{
	  us.insert(elems[i]);
	  check(us);
	}

      if (with_copy)
	{
	  std::unordered_set<_ElemType>(us).swap(us);
	  check(us);
	}

      for (int i = nb_elements - 1; i >= 0; --i)
	{
	  auto it = us.find(elems[i]);
	  if (it != us.end())
	    {
	      us.erase(it);
	      check(us);
	    }
	}

      us.insert(elems[0]);
      check(us);
      for (int i = nb_elements - 1; i >= 0; --i)
	{
	  us.insert(elems[i]);
	  check(us);
	}

      for (int j = nb_elements - 1; j >= 0; --j)
	{
	  us.erase(elems[j]);
	  check(us);
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
