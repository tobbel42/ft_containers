#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{

template <class T> struct remove_const {typedef T type;};
template <class T> struct remove_const<const T> {typedef T type;};
template <class T> struct remove_reference {typedef T type;};
template <class T> struct remove_reference<T &> {typedef T type;};


template <typename T, T v>
struct integral_constant {static const T value = v;};

typedef integral_constant<bool, true>	true_type;
typedef integral_constant<bool, false>	false_type;

template <typename T>	struct is_integral_base	: public false_type {};


template <>	struct is_integral_base<bool>					
	: public true_type {};
template <>	struct is_integral_base<char>					
	: public true_type {};
template <>	struct is_integral_base<wchar_t>				
	: public true_type {};
template <>	struct is_integral_base<signed char>			
	: public true_type {};
template <>	struct is_integral_base<short int>				
	: public true_type {};
template <>	struct is_integral_base<int>					
	: public true_type {};
template <>	struct is_integral_base<long int>				
	: public true_type {};
template <>	struct is_integral_base<long long int>			
	: public true_type {};
template <>	struct is_integral_base<unsigned char>			
	: public true_type {};
template <>	struct is_integral_base<unsigned short int>		
	: public true_type {};
template <>	struct is_integral_base<unsigned int>			
	: public true_type {};
template <>	struct is_integral_base<unsigned long int>		
	: public true_type {};
template <>	struct is_integral_base<unsigned long long int> 
	: public true_type {};


template <class T> struct is_integral : public is_integral_base<
	typename remove_const<T>::type> {};

template <bool B, typename T = void>
	struct enable_if {};

template <typename T>
	struct enable_if<true, T> {typedef T type;};

};

#endif