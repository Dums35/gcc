// { dg-do run { target c++11 } }

// Copyright (C) 2020 Free Software Foundation, Inc.
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

#include <deque>

#include <testsuite_iterators.h>
#include <testsuite_hooks.h>

void make_moved(std::deque<int>& inst)
{
  auto size = inst.size();
  {
    std::deque<int> d(std::move(inst));
    VERIFY( d.size() == size );
  }

  VERIFY( inst.empty() );
  VERIFY( inst.size() == 0 );
}

void test01()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  d.push_front(1);

  VERIFY( d.size() == 1 );
  VERIFY( d[0] == 1 );
}

void test02()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  d.push_back(1);

  VERIFY( d.size() == 1 );
  VERIFY( d[0] == 1 );
}

void test03()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  int one = 1;
  d.push_front(one);

  VERIFY( d.size() == 1 );
  VERIFY( d[0] == 1 );
}

void test04()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  int one = 1;
  d.push_back(one);

  VERIFY( d.size() == 1 );
  VERIFY( d[0] == 1 );
}

void test05()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  d.emplace_front(1);

  VERIFY( d.size() == 1 );
  VERIFY( d[0] == 1 );
}

void test06()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  d.emplace_back(1);

  VERIFY( d.size() == 1 );
  VERIFY( d[0] == 1 );
}

void test07()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  std::deque<int> od(d);

  VERIFY( od.size() == 0 );
  VERIFY( od.empty() );
}

void test08()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  std::deque<int> od(std::move(d));

  VERIFY( od.size() == 0 );
  VERIFY( od.empty() );
}

void test09()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  std::deque<int> od;
  od = d;

  VERIFY( od.size() == 0 );
  VERIFY( od.empty() );
}

void test10()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  std::deque<int> od;
  od = std::move(d);

  VERIFY( od.size() == 0 );
  VERIFY( od.empty() );
}

void test11()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  std::deque<int> od(7, 1);
  d = od;

  VERIFY( d.size() == 7 );
  VERIFY( !od.empty() );
}

void test12()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  std::deque<int> od(7, 1);
  d = std::move(od);

  VERIFY( od.size() == 0 );
  VERIFY( od.empty() );
  VERIFY( d.size() == 7 );
}

void test13()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  d = { 0, 1, 2 };

  VERIFY( d.size() == 3 );
}

void test14()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  d.assign(3, 3);

  VERIFY( d.size() == 3 );
}

template<typename T>
  using input_iterator_seq
    = __gnu_test::test_container<T, __gnu_test::input_iterator_wrapper>;

void test15()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  int array[] { 0, 1, 2 };
  input_iterator_seq<int> seq(array, array + 3);

  d.assign(seq.begin(), seq.end());

  VERIFY( d.size() == 3 );
}

void test16()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  std::deque<int> od(7, 1);

  d.assign(od.begin(), od.end());

  VERIFY( d.size() == 7 );
}

void test17()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  auto l = { 0, 1, 2 };
  d.assign(l);

  VERIFY( d.size() == 3 );
}

void test18()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  d.resize(3);

  VERIFY( d.size() == 3 );
  VERIFY( d[0] == 0 );
}

void test19()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  d.resize(3, 1);

  VERIFY( d.size() == 3 );
  VERIFY( d[0] == 1 );
}

void test20()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  d.shrink_to_fit();

  VERIFY( d.size() == 0 );
}

void test21()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  d.insert(d.end(), 1);

  VERIFY( d.size() == 1 );
  VERIFY( d[0] == 1 );
}

void test22()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  int one = 1;
  d.insert(d.end(), one);

  VERIFY( d.size() == 1 );
  VERIFY( d[0] == 1 );
}

void test23()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  d.emplace(d.end(), 1);

  VERIFY( d.size() == 1 );
  VERIFY( d[0] == 1 );
}

void test24()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  int one = 1;
  d.emplace(d.end(), one);

  VERIFY( d.size() == 1 );
  VERIFY( d[0] == 1 );
}

void test25()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  d.insert(d.end(), { 0, 1, 2 });

  VERIFY( d.size() == 3 );
  VERIFY( d[0] == 0 );
}

void test26()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  d.insert(d.end(), 3, 1);

  VERIFY( d.size() == 3 );
  VERIFY( d[0] == 1 );
}

void test27()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  int array[] { 0, 1, 2 };
  input_iterator_seq<int> seq(array, array + 3);

  d.insert(d.end(), seq.begin(), seq.end());

  VERIFY( d.size() == 3 );
  VERIFY( d[0] == 0 );
}

void test28()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  std::deque<int> od(7, 1);

  d.insert(d.end(), od.begin(), od.end());

  VERIFY( d.size() == 7 );
  VERIFY( d[0] == 1 );
}

void test29()
{
  std::deque<int> d(7, 0);
  make_moved(d);

  d.clear();

  VERIFY( d.size() == 0 );
}

int main()
{
  test01();
  test02();
  test03();
  test04();
  test05();
  test06();
  test07();
  test08();
  test09();
  test10();
  test11();
  test12();
  test13();
  test14();
  test15();
  test16();
  test17();
  test18();
  test19();
  test20();
  test21();
  test22();
  test23();
  test24();
  test25();
  test26();
  test27();
  test28();
  test29();
}
