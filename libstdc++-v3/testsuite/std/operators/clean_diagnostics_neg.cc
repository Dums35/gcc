// { dg-do compile { xfail *-*-* } }
// { dg-add-options no_pch }

//#include <bits/stdc++.h>
#include <vector>
#if __cplusplus >= 201103L
#include <tuple>
#endif

using namespace std;

struct NoOperators
{
};

int main()
{
  NoOperators s1, s2;
  bool res __attribute__((unused)) = s1 == s2; // { dg-error "no match" }
  res = s1 < s2; // { dg-error "no match" }
  res = s1 != s2; // { dg-error "no match" }
  res = s1 > s2; // { dg-error "no match" }
  res = s1 <= s2; // { dg-error "no match" }
  res = s1 >= s2; // { dg-error "no match" }
}
