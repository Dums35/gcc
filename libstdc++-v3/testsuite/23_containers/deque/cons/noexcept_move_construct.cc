// { dg-do compile { target c++11 } }
// { dg-require-versionnamespace-mode "" }
// Copyright (C) 2020 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

#include <deque>

typedef std::deque<int> type;

static_assert( std::is_nothrow_move_constructible<type>::value,
	       "noexcept move constructor" );
static_assert( noexcept( type(std::declval<type>(),
		std::declval<const typename type::allocator_type&>()) ),
	       "noexcept move constructor with allocator" );
