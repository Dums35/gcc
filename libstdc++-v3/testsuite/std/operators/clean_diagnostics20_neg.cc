// { dg-do compile { target c++20 xfail *-*-* } }
// { dg-add-options no_pch }

//#include <bits/stdc++.h>
#include <vector>
#include <tuple>

using namespace std;

struct NoOperators
{
};

int main()
{
  NoOperators s1, s2;
  bool res [[maybe_unused]] = s1 == s2; // { dg-error "no match" }
  res = s1 < s2; // { dg-error "no match" }
  res = s1 != s2; // { dg-error "no match" }
  res = s1 > s2; // { dg-error "no match" }
  res = s1 <= s2; // { dg-error "no match" }
  res = s1 >= s2; // { dg-error "no match" }
  auto way [[maybe_unused]] = s1 <=> s2; // { dg-error "no match" }
}
