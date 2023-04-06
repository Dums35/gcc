// { dg-require-fileio "" }
// { dg-do run { xfail *-*-* } }
// { dg-require-debug-mode "" }

#include <iterator>
#include <fstream>
#include <algorithm>

#include <testsuite_hooks.h>

void test01()
{
  using namespace std;

  typedef istreambuf_iterator<char> in_iterator_type;

  unsigned found = 0;

  {
    ifstream fbuf("istream_unformatted-1.txt");

    in_iterator_type beg(fbuf);
    in_iterator_type end;

    for (;;)
      {
	beg = find(beg, end, '1');
	if (beg == end)
	  break;

	++found;
	VERIFY( *beg == '1' );

	advance(beg, 9);
	VERIFY( *beg == '0' );
      }
  }

  {
    ifstream fbuf("istream_unformatted-1.txt");

    in_iterator_type beg(fbuf);
    in_iterator_type end;

    beg = find(beg, end, '1');
    VERIFY( beg != end );
    VERIFY( *beg == '1' );

    advance(beg, 9);
    VERIFY( *beg == '0' );

    unsigned line_length = 10;
    while (*++beg != '1')
      ++line_length;

    // Try to jump directly to the end + 1 through advance.
    advance(beg, (found - 2) * line_length + 9 + 2);
  }
}

int main()
{
  test01();
  return 0;
}
