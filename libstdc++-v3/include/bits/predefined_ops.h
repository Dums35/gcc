// Default predicates for internal use -*- C++ -*-

// Copyright (C) 2013-2024 Free Software Foundation, Inc.
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

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file predefined_ops.h
 *  This is an internal header file, included by other library headers.
 *  You should not attempt to use it directly. @headername{algorithm}
 */

#ifndef _GLIBCXX_PREDEFINED_OPS_H
#define _GLIBCXX_PREDEFINED_OPS_H	1

#include <bits/move.h>
#include <bits/stl_iterator_base_types.h>

#if __cplusplus >= 201103L
# include <bits/invoke.h>
#endif

namespace __gnu_cxx
{
namespace __ops
{
#if __cplusplus >= 201103L
  struct _Less
  {
    template<typename _Lhs, typename _Rhs>
      _GLIBCXX14_CONSTEXPR
      bool
      operator()(_Lhs&& __lhs, _Rhs&& __rhs) const
      noexcept( noexcept(__lhs < __rhs) )
      { return __lhs < __rhs; }
  };
#else
  template<typename _Ref1, typename _Ref2>
    struct _LessRefs
    {
      bool
      operator()(_Ref1 __lhs, _Ref2 __rhs) const
      { return __lhs < __rhs; }

      bool
      operator()(_Ref2 __lhs, _Ref1 __rhs) const
      { return __lhs < __rhs; }

      bool
      operator()(_Ref1 __lhs, _Ref1 __rhs) const
      { return __lhs < __rhs; }

      bool
      operator()(_Ref2 __lhs, _Ref2 __rhs) const
      { return __lhs < __rhs; }
    };

  template<typename _Ref>
    struct _LessRefs<_Ref, _Ref>
    {
      bool
      operator()(_Ref __lhs, _Ref __rhs) const
      { return __lhs < __rhs; }
    };

  template<typename _Ite1, typename _Ite2>
    struct _Less
    : _LessRefs<typename std::iterator_traits<_Ite1>::reference,
		typename std::iterator_traits<_Ite2>::reference>
    { };

  template<typename _Ite>
    struct _LessCRef
    : _LessRefs<typename std::iterator_traits<_Ite>::reference,
		const typename std::iterator_traits<_Ite>::value_type&>
    { };
#endif

#if __cplusplus >= 201103L
  template<typename _Ite1, typename _Ite2>
    constexpr _Less
    __less(_Ite1, _Ite2) noexcept
    { return _Less{}; }

  constexpr _Less
  __less() noexcept
  { return _Less{}; }
#else
  template<typename _Ite1, typename _Ite2>
    inline _Less<_Ite1, _Ite2>
    __less(_Ite1, _Ite2)
    { return _Less<_Ite1, _Ite2>(); }
#endif

#if __cplusplus >= 201103L
  template<typename _Ite>
    constexpr _Less
    __less(_Ite) noexcept
    { return _Less{}; }
#else
  template<typename _Ite>
    inline _LessCRef<_Ite>
    __less(_Ite)
    { return _LessCRef<_Ite>(); }
#endif

#if __cplusplus >= 201103L
  template<typename _Comp, typename _Ite1, typename _Ite2>
    constexpr _Comp&&
    __less(_Comp&& __comp, _Ite1, _Ite2) noexcept
    { return std::forward<_Comp>(__comp); }
#else
  template<typename _Comp, typename _Ite1, typename _Ite2>
    inline _Comp
    __less(_Comp __comp, _Ite1, _Ite2)
    { return __comp; }

  template<typename _LessRef1, typename _LessRef2, typename _Ite1, typename _Ite2>
    inline _Less<_Ite1, _Ite2>
    __less(const _LessRefs<_LessRef1, _LessRef2>&, _Ite1, _Ite2)
    { return _Less<_Ite1, _Ite2>(); }
#endif

#if __cplusplus < 201103L
  template<typename _Ite, typename _Val>
    struct _LessVal : _LessRefs<typename std::iterator_traits<_Ite>::reference,
			      _Val&>
    { };
#endif

#if __cplusplus >= 201103L
  template<typename _Ite, typename _Val>
    constexpr _Less
    __less_val(_Ite, _Val&&) noexcept
    { return _Less{}; }
#else
  template<typename _Ite, typename _Val>
    inline _LessVal<_Ite, _Val>
    __less_val(_Ite, _Val&)
    { return _LessVal<_Ite, _Val>(); }
#endif

#if __cplusplus >= 201103L
  template<typename _Comp, typename _Ite, typename _Val>
    constexpr _Comp&&
    __less_val(_Comp&& __comp, _Ite, _Val&&) noexcept
    { return std::forward<_Comp>(__comp); }
#else
  template<typename _Comp, typename _Ite, typename _Val>
    inline _Comp
    __less_val(_Comp __comp, _Ite, _Val&)
    { return __comp; }

  template<typename _Ref1, typename _Ref2, typename _Ite, typename _Val>
    inline _LessVal<_Ite, _Val>
    __less_val(const _LessRefs<_Ref1, _Ref2>&, _Ite, _Val&)
    { return _LessVal<_Ite, _Val>(); }
#endif

#if __cplusplus >= 201103L
  struct _EqualTo
  {
    template<typename _Lhs, typename _Rhs>
      _GLIBCXX20_CONSTEXPR
      bool
      operator()(_Lhs&& __lhs, _Rhs&& __rhs) const
      noexcept( noexcept(__lhs == __rhs) )
      { return __lhs == __rhs; }
  };
#else
  template<typename _Ref1, typename _Ref2>
    struct _EqualToRefs
    {
      bool
      operator()(_Ref1 __lhs, _Ref2 __rhs) const
      { return __lhs == __rhs; }

      bool
      operator()(_Ref2 __lhs, _Ref1 __rhs) const
      { return __lhs == __rhs; }

      bool
      operator()(_Ref1 __lhs, _Ref1 __rhs) const
      { return __lhs == __rhs; }

      bool
      operator()(_Ref2 __lhs, _Ref2 __rhs) const
      { return __lhs == __rhs; }
    };

  template<typename _Ref>
    struct _EqualToRefs<_Ref, _Ref>
    {
      bool
      operator()(_Ref __lhs, _Ref __rhs) const
      { return __lhs == __rhs; }
    };

  template<typename _Ite1, typename _Ite2>
    struct _EqualTo
      : _EqualToRefs<typename std::iterator_traits<_Ite1>::reference,
		     typename std::iterator_traits<_Ite2>::reference>
    { };
#endif

#if __cplusplus >= 201103L
  template<typename _Ite1, typename _Ite2>
    constexpr _EqualTo
    __equal_to(_Ite1, _Ite2) noexcept
    { return _EqualTo{}; }

  constexpr _EqualTo
  __equal_to() noexcept
  { return _EqualTo{}; }
#else
  template<typename _Ite1, typename _Ite2>
    inline _EqualTo<_Ite1, _Ite2>
    __equal_to(_Ite1, _Ite2)
    { return _EqualTo<_Ite1, _Ite2>(); }
#endif

#if __cplusplus >= 201103L
  template<typename _Ite>
    constexpr _EqualTo
    __equal_to(_Ite) noexcept
    { return _EqualTo{}; }
#else
  template<typename _Ite>
    inline _EqualTo<_Ite, _Ite>
    __equal_to(_Ite)
    { return _EqualTo<_Ite, _Ite>(); }
#endif

#if __cplusplus < 201103L
  template<typename _Ite, typename _Val>
    struct _EqualToVal
      : _EqualToRefs<typename std::iterator_traits<_Ite>::reference, _Val&>
    { };
#endif

#if __cplusplus >= 201103L
  template<typename _Comp, typename _Ite, typename _Val>
    constexpr _Comp&&
    __equal_to_val(_Comp&& __comp, _Ite, _Val&&) noexcept
    { return std::forward<_Comp>(__comp); }
#else
  template<typename _Comp, typename _Ite, typename _Val>
    inline _Comp
    __equal_to_val(_Comp __comp, _Ite, _Val&)
    { return __comp; }

  template<typename _Ref1, typename _Ref2, typename _Ite, typename _Val>
    inline _EqualToVal<_Ite, _Val>
    __equal_to_val(const _EqualToRefs<_Ref1, _Ref2>&, _Ite, _Val&)
    { return _EqualToVal<_Ite, _Val>(); }
#endif

#if __cplusplus >= 201103L
  template<typename _Val>
    struct _EqualVal
    {
    private:
      _Val _M_val;

    public:
      constexpr
      _EqualVal(_Val __val)
      : _M_val(__val) { }

      template<typename _Lhs>
	_GLIBCXX20_CONSTEXPR
	bool
	operator()(_Lhs&& __lhs) const
	noexcept( noexcept(__lhs == _M_val) )
	{ return __lhs == _M_val; }
    };
#else
  template<typename _Ref, typename _Val>
    struct _EqualValRef
    {
    private:
      _Val _M_val;

    public:
      _EqualValRef(_Val __val)
      : _M_val(__val)
      { }

      bool
      operator()(_Ref __lhs) const
      { return __lhs == _M_val; }
    };

  template<typename _Ite, typename _Val>
    struct _EqualVal
    : _EqualValRef<typename std::iterator_traits<_Ite>::reference, _Val>
    {
      typedef
      _EqualValRef<typename std::iterator_traits<_Ite>::reference, _Val> _Base;

      _EqualVal(_Val __val)
      : _Base(__val)
      { }
    };
#endif

#if __cplusplus >= 201103L
  template<typename _Ite, typename _Val>
    constexpr _EqualVal<const _Val&>
    __equal_val(_Ite, const _Val& __val) noexcept
    {return _EqualVal<const _Val&>(__val);}

  template<typename _Val>
    constexpr _EqualVal<const _Val&>
    __equal_val(const _Val& __val) noexcept
    {return _EqualVal<const _Val&>(__val);}
#else
  template<typename _Ite, typename _Val>
    inline _EqualVal<_Ite, const _Val&>
    __equal_val(_Ite, const _Val& __val)
    { return _EqualVal<_Ite, const _Val&>(__val); }
#endif

#if __cplusplus >= 201103L
  template<typename _BinaryPred, typename _Val>
    struct _CompVal
    {
      template<typename _BPred>
	constexpr
	_CompVal(_BPred&& __pred, _Val __val)
	: _M_binary_pred(std::forward<_BPred>(__pred))
	, _M_val(__val)
	{ }

      _CompVal(const _CompVal&) = default;
      _CompVal(_CompVal&&) = default;
      ~_CompVal() = default;

      // Macro to define operator() with given cv-qualifiers ref-qualifiers,
      // forwarding _M_binary_pred and the function arguments with the same
      // qualifiers, and deducing the return type and exception-specification.
# define _GLIBCXX_BINARY_PRED_CALL_OP( _QUALS )				\
      template<typename _Arg,						\
	       typename = std::__enable_if_t<std::__is_invocable<	\
		 _BinaryPred _QUALS, _Arg, _Val>::value>> 	\
	_GLIBCXX20_CONSTEXPR						\
	bool								\
	operator()(_Arg&& __arg) _QUALS					\
	noexcept(std::__is_nothrow_invocable<				\
		 _BinaryPred _QUALS, _Arg, _Val>::value)		\
	{								\
	  return std::__invoke(						\
		   std::forward< _BinaryPred _QUALS >(_M_binary_pred),	\
		   std::forward<_Arg>(__arg), _M_val);			\
	}								\
									\
      template<typename _Arg,						\
	       typename = std::__enable_if_t<!std::__is_invocable<	\
		 _BinaryPred _QUALS, _Arg, _Val>::value>>	\
	void operator()(_Arg&&) _QUALS = delete;

      _GLIBCXX_BINARY_PRED_CALL_OP( & )
      _GLIBCXX_BINARY_PRED_CALL_OP( const & )
      _GLIBCXX_BINARY_PRED_CALL_OP( && )
      _GLIBCXX_BINARY_PRED_CALL_OP( const && )
# undef _GLIBCXX_BINARY_PRED_CALL_OP
#else
  template<typename _BinaryPred, typename _Ite, typename _Val>
    struct _CompVal
    {
      _CompVal(_BinaryPred __pred, _Val __val)
      : _M_binary_pred(__pred), _M_val(__val)
      { }

      bool
      operator()(typename std::iterator_traits<_Ite>::reference __lhs)
      { return bool(_M_binary_pred(__lhs, _M_val)); }
#endif

    private:
      _BinaryPred _M_binary_pred;
      _Val	  _M_val;
    };

#if __cplusplus >= 201103L
  template<typename _BPred, typename _Ite, typename _Val>
    _GLIBCXX20_CONSTEXPR inline
    _CompVal<std::__decay_t<_BPred>, const _Val&>
    __comp_val(_BPred&& __pred, _Ite, const _Val& __val)
    noexcept(std::is_nothrow_constructible<std::__decay_t<_BPred>,
	     _BPred&&>::value)
    {
      return
	_CompVal<std::__decay_t<_BPred>, const _Val&>
	(std::forward<_BPred>(__pred), __val);
    }
#else
  template<typename _BPred, typename _Ite, typename _Val>
    inline _CompVal<_BPred, _Ite, const _Val&>
    __comp_val(_BPred __pred, _Ite, const _Val& __val)
    { return _CompVal<_BPred, _Ite, const _Val&>(__pred, __val); }
#endif

#if __cplusplus >= 201103L
  template<typename _BPred, typename _InIte, typename _Ite>
    _GLIBCXX20_CONSTEXPR inline
    _CompVal<std::__decay_t<_BPred>,
	     typename std::iterator_traits<_Ite>::reference>
    __equal_ite(_BPred&& __pred, _InIte, _Ite  __ite)
    noexcept(std::is_nothrow_constructible<std::__decay_t<_BPred>,
	     _BPred&&>::value)
    {
      return
	_CompVal<std::__decay_t<_BPred>,
		 typename std::iterator_traits<_Ite>::reference>
	(std::forward<_BPred>(__pred), *__ite);
    }

  template<typename _InIte, typename _Ite>
    _GLIBCXX20_CONSTEXPR inline
    _EqualVal<typename std::iterator_traits<_Ite>::reference>
    __equal_ite(_EqualTo, _InIte, _Ite __ite)
    {
      return
	_EqualVal<typename std::iterator_traits<_Ite>::reference>(*__ite);
    }
#else
  template<typename _BPred, typename _InIte, typename _Ite>
    inline
      _CompVal<_BPred, _InIte, typename std::iterator_traits<_Ite>::reference>
    __equal_ite(_BPred __pred, _InIte, _Ite __ite)
    {
      return
	_CompVal<_BPred, _InIte, typename std::iterator_traits<_Ite>::reference>
	(__pred, *__ite);
    }

  template<typename _Ref1, typename _Ref2, typename _InIte, typename _Ite>
    inline
      _EqualVal<_InIte, typename std::iterator_traits<_Ite>::reference>
    __equal_ite(const _EqualToRefs<_Ref1, _Ref2>&, _InIte, _Ite __ite)
    {
      return
	_EqualVal<_InIte, typename std::iterator_traits<_Ite>::reference>
	(*__ite);
    }
#endif
} // namespace __ops
} // namespace __gnu_cxx


namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

#if __cplusplus >= 201103L
  /// Generalized negator.
  template<typename _Fn>
    class _Not_fn
    {
      template<typename _Fn2, typename... _Args>
	using __inv_res_t = typename __invoke_result<_Fn2, _Args...>::type;

      template<typename _Tp>
	static decltype(!std::declval<_Tp>())
	_S_not() noexcept(noexcept(!std::declval<_Tp>()));

    public:
      template<typename _Fn2>
	constexpr
	_Not_fn(_Fn2&& __fn, int)
	: _M_fn(std::forward<_Fn2>(__fn)) { }

      _Not_fn(const _Not_fn& __fn) = default;
      _Not_fn(_Not_fn&& __fn) = default;
      ~_Not_fn() = default;

      // Macro to define operator() with given cv-qualifiers ref-qualifiers,
      // forwarding _M_fn and the function arguments with the same qualifiers,
      // and deducing the return type and exception-specification.
# define _GLIBCXX_NOT_FN_CALL_OP( _QUALS )				\
      template<typename... _Args,					\
	       typename = __enable_if_t<__is_invocable<_Fn _QUALS, _Args...>::value>> \
	_GLIBCXX20_CONSTEXPR						\
	decltype(_S_not<__inv_res_t<_Fn _QUALS, _Args...>>())		\
	operator()(_Args&&... __args) _QUALS				\
	noexcept(__is_nothrow_invocable<_Fn _QUALS, _Args...>::value	\
	    && noexcept(_S_not<__inv_res_t<_Fn _QUALS, _Args...>>()))	\
	{								\
	  return !std::__invoke(std::forward< _Fn _QUALS >(_M_fn),	\
				std::forward<_Args>(__args)...);	\
	}								\
									\
      template<typename... _Args,					\
	       typename = __enable_if_t<!__is_invocable<_Fn _QUALS, _Args...>::value>> \
	void operator()(_Args&&... __args) _QUALS = delete;

      _GLIBCXX_NOT_FN_CALL_OP( & )
      _GLIBCXX_NOT_FN_CALL_OP( const & )
      _GLIBCXX_NOT_FN_CALL_OP( && )
      _GLIBCXX_NOT_FN_CALL_OP( const && )
# undef _GLIBCXX_NOT_FN_CALL_OP
#else
  /// Generalized negator.
  template<typename _Fn, typename _Ite>
    class _Not_fn
    {
    public:
      _Not_fn(_Fn __fn)
      : _M_fn(__fn) { }

      bool
      operator()(typename std::iterator_traits<_Ite>::reference __arg)
      { return !bool(_M_fn(__arg)); }
#endif
    private:
      _Fn _M_fn;
    };

  template<typename _Fn, typename _Ite>
    inline _GLIBCXX20_CONSTEXPR
#if __cplusplus >= 201103L
    _Not_fn<std::__decay_t<_Fn>>
    __not_fn(_Fn&& __fn, _Ite)
    noexcept(std::is_nothrow_constructible<std::__decay_t<_Fn>, _Fn&&>::value)
    { return _Not_fn<std::__decay_t<_Fn>>{std::forward<_Fn>(__fn), 0}; }
#else
    _Not_fn<_Fn, _Ite>
    __not_fn(_Fn __fn, _Ite)
    { return _Not_fn<_Fn, _Ite>(__fn); }
#endif

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace std

#endif
