#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack {
	public:
	/*Typedefs----------------------------------------------------------------*/
	typedef T									value_type;
	typedef Container							container_type;
	typedef typename container_type::size_type 	size_type;

	protected:
	/*MemberVariabels---------------------------------------------------------*/
	container_type m_cntr;

	public:
	/*Constructors------------------------------------------------------------*/
	explicit stack(const container_type & cntr = container_type()):
		m_cntr(cntr) {};

	/*MemberFunctions---------------------------------------------------------*/
	bool empty() const { return m_cntr.empty(); };
	size_type size() const { return m_cntr.size(); };
	value_type & top() { return m_cntr.back(); };
	const value_type & top() const { return m_cntr.back(); };
	void push (const value_type& val) { m_cntr.push_back(val); };
	void pop() { m_cntr.pop_back(); };

	/*FriendsDeclarations-----------------------------------------------------*/
	template <class T1, class Container1>
	friend bool operator== (const stack<T1,Container1>& lhs,
							const stack<T1,Container1>& rhs);
	template <class T1, class Container1>
	friend bool operator!= (const stack<T1,Container1>& lhs,
							const stack<T1,Container1>& rhs);
	template <class T1, class Container1>
	friend bool operator<  (const stack<T1,Container1>& lhs,
							const stack<T1,Container1>& rhs);
	template <class T1, class Container1>
	friend bool operator<= (const stack<T1,Container1>& lhs,
							const stack<T1,Container1>& rhs);
	template <class T1, class Container1>
	friend bool operator>  (const stack<T1,Container1>& lhs,
							const stack<T1,Container1>& rhs);
	template <class T1, class Container1>
	friend bool operator>= (const stack<T1,Container1>& lhs,
							const stack<T1,Container1>& rhs);
	};

	template <class T, class Container>
	bool operator==(const stack<T,Container>& lhs,
					const stack<T,Container>& rhs) {
		return lhs.m_cntr == rhs.m_cntr;
	};
	template <class T, class Container>
	bool operator!=(const stack<T,Container>& lhs,
					const stack<T,Container>& rhs) {
		return lhs.m_cntr != rhs.m_cntr;
	};
	template <class T, class Container>
	bool operator<(const stack<T,Container>& lhs,
					const stack<T,Container>& rhs) {
		return lhs.m_cntr < rhs.m_cntr;
	};
	template <class T, class Container>
	bool operator<=(const stack<T,Container>& lhs,
					const stack<T,Container>& rhs) {
		return lhs.m_cntr <= rhs.m_cntr;
	};
	template <class T, class Container>
	bool operator>(const stack<T,Container>& lhs,
					const stack<T,Container>& rhs) {
		return lhs.m_cntr > rhs.m_cntr;
	};
	template <class T, class Container>
	bool operator>=(const stack<T,Container>& lhs,
					const stack<T,Container>& rhs) {
		return lhs.m_cntr >= rhs.m_cntr;
	};
}
#endif