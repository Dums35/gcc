// { dg-do run { target c++17 } }
// { dg-require-effective-target std_allocator_new }

// Copyright (C) 2023 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

// libstdc++/96088

#include <string_view>
#include <string>
#include <map>
#include <vector>

#include <testsuite_hooks.h>
#include <replacement_memory_operators.h>

static constexpr std::initializer_list<std::pair<const char*, int>> lst =
  { {"long_str_for_dynamic_allocating", 1} };

void
test01()
{
  __gnu_test::counter::reset();
  std::map<std::string, int> m;
  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 2 );

  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 3 );

  VERIFY( !m.emplace(*lst.begin()).second );
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 4 );
}

void
test02()
{
  __gnu_test::counter::reset();
  std::map<std::string, int, std::less<std::string_view>> m;
  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 2 );

  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 2 );

  VERIFY( !m.emplace(*lst.begin()).second );
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 2 );
}

bool
less_string_f(const std::string& lhs, const std::string& rhs) noexcept
{ return lhs < rhs; }

void
test11()
{
  typedef bool (*less_string_t)(const std::string&,
				const std::string&) noexcept;
  __gnu_test::counter::reset();
  less_string_t comparer = &less_string_f;
  std::map<std::string, int, less_string_t> m(comparer);
  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 2 );

  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 3 );
}

bool
less_string_view_f(const std::string_view& lhs,
		   const std::string_view& rhs) noexcept
{ return lhs < rhs; }

void
test12()
{
  typedef bool (*less_stringview_t) (const std::string_view&,
				     const std::string_view&) noexcept;
  __gnu_test::counter::reset();
  less_stringview_t comparer = &less_string_view_f;
  std::map<std::string, int, less_stringview_t> m(comparer);
  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 2 );

  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 2 );
}

struct less_string_functor
{
  bool
  operator()(const std::string& lhs,
	     const std::string& rhs) const noexcept
  { return lhs < rhs; }
};

void
test21()
{
  __gnu_test::counter::reset();
  std::map<std::string, int, less_string_functor> m;
  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 2 );

  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 3 );
}

struct less_string_view_noexcept_functor
{
  bool
  operator()(const std::string_view& lhs,
	     const std::string_view& rhs) const noexcept
  { return lhs < rhs; }
};

void
test22()
{
  __gnu_test::counter::reset();
  std::map<std::string, int, less_string_view_noexcept_functor> m;
  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 2 );

  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 2 );
}

struct less_string_view_functor
{
  bool
  operator()(const std::string_view& lhs,
	     const std::string_view& rhs) const
  { return lhs < rhs; }
};

void
test23()
{
  __gnu_test::counter::reset();
  std::map<std::string, int, less_string_view_functor> m;
  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 2 );

  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 2 );
}

struct less_string_view_noexcept_transparent_functor
{
  bool
  operator()(const std::string_view& lhs,
	     const std::string_view& rhs) const noexcept
  { return lhs < rhs; }

  typedef std::__is_transparent is_transparent;
};

void
test24()
{
  __gnu_test::counter::reset();
  std::map<std::string, int,
	   less_string_view_noexcept_transparent_functor> m;
  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 2 );

  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 2 );
}

struct less_string_view_transparent_functor
{
  bool
  operator()(const std::string_view& lhs,
	     const std::string_view& rhs) const
  { return lhs < rhs; }

  typedef std::__is_transparent is_transparent;
};

void
test25()
{
  __gnu_test::counter::reset();
  std::map<std::string, int, less_string_view_transparent_functor> m;
  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 2 );

  m.insert(lst.begin(), lst.end());
  VERIFY( m.size() == 1 );

  VERIFY( __gnu_test::counter::count() == 2 );
  VERIFY( __gnu_test::counter::get()._M_increments == 2 );
}

void
test03()
{
  std::vector<std::pair<std::string, int>> v;
  v.insert(v.end(), lst.begin(), lst.end());

  const auto origin = __gnu_test::counter::count();

  {
    __gnu_test::counter::reset();
    std::map<std::string, int, std::less<std::string_view>> m;
    m.insert(v.begin(), v.end());
    VERIFY( m.size() == 1 );

    // Allocate a node and the std::string (unless COW).
    constexpr std::size_t increments = _GLIBCXX_USE_CXX11_ABI ? 2 : 1;

    VERIFY( __gnu_test::counter::count() == origin + increments );
    VERIFY( __gnu_test::counter::get()._M_increments == increments );

    m.insert(v.begin(), v.end());
    VERIFY( m.size() == 1 );

    VERIFY( __gnu_test::counter::count() == origin + increments );
    VERIFY( __gnu_test::counter::get()._M_increments == increments );
  }
  VERIFY( __gnu_test::counter::count() == origin );

  {
    __gnu_test::counter::reset();
    std::map<std::string, int, std::less<std::string_view>> m;
    m.insert(std::make_move_iterator(v.begin()),
	     std::make_move_iterator(v.end()));
    VERIFY( m.size() == 1 );

    // Allocate a node. String is moved.
    constexpr std::size_t increments = 1;

    VERIFY( __gnu_test::counter::count() == origin + increments );
    VERIFY( __gnu_test::counter::get()._M_increments == increments );
  }
}

int
main()
{
  test01();
  test02();
  test11();
  test12();
  test21();
  test22();
  test23();
  test24();
  test25();
  test03();
  return 0;
}
