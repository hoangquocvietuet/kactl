#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define print_op(...) ostream& operator<<(ostream& out, const __VA_ARGS__& u)
#define db(val) "["#val" = "<<(val)<<"] "
#define CONCAT_(x, y) x##y
#define CONCAT(x, y) CONCAT_(x, y)
#ifdef LOCAL   
#   define clog cerr << setw(__db_level * 2) << setfill(' ') << "" << setw(0)
#   define DB() debug_block CONCAT(dbbl, __LINE__)
	int __db_level = 0;
	struct debug_block {
		debug_block() { clog << "{" << endl; ++__db_level; }
		~debug_block() { --__db_level; clog << "}" << endl; }
	};
#else
#   define clog if (0) cerr
#   define DB(...)
#endif
template<class U, class V> print_op(pair<U, V>) {
	return out << "(" << u.first << ", " << u.second << ")";
}
template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator<<(ostream& out, const Con& con) { 
	out << "{";
	for (auto beg = con.begin(), it = beg; it != con.end(); ++it)
		out << (it == beg ? "" : ", ") << *it;
	return out << "}";
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
	if constexpr(i == tuple_size<T>::value) return out << ")"; 
	else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> print_op(tuple<U...>) {
	return print_tuple_utils<0, tuple<U...>>(out, u);
}
template <typename A, typename B> bool maximize(A& a, B b) {
	return a < b ? a = b, true : false;
}
template <typename A, typename B> bool minimize(A& a, B b) {
	return a > b ? a = b, true : false;
}
cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
