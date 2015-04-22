/**
 * Printing algorithms for more involved (but common) data structures
 * Authors: Erich Gubler, erichdongubler@gmail.com
 */
#ifndef PRINTALGORITHMS_H
#define PRINTALGORITHMS_H
#include <iostream>
using namespace std;

// Stream functor that prints random-access ranges of the form "[a, b, c]"
template<typename Iter>
class RangePrinter
{
private:
	Iter begin;
	Iter end;

public:
	RangePrinter(Iter b, Iter e) : begin(b), end(e) {}

	friend ostream& operator<<(ostream& os, RangePrinter& rp)
	{
		os << '[';
		if(rp.begin != rp.end)
			os << *rp.begin++;
		while(rp.begin != rp.end)
			os << ", " << *rp.begin++;
		return os << ']';
	}
};

template<typename T>
void print_range(T begin, T end, std::ostream& os = std::cout)
{
	auto rp = RangePrinter<T>(begin, end);
	os << rp;
}

template<typename Iter, typename F>
class TransformedRangePrinter
{
private:
	Iter begin;
	Iter end;
	F func;

public:
	TransformedRangePrinter(Iter b, Iter e, F f) : begin(b), end(e), func(f) {}

	friend ostream& operator<<(std::ostream& os, TransformedRangePrinter& trp)
	{
		os << '[';
		if(trp.begin != trp.end)
			os << trp.func(*trp.begin++);
		while(trp.begin != trp.end)
			os << ", " << trp.func(*trp.begin++);
		return os << ']';
	}
};

template<typename T, typename F>
void print_transformed_range(T begin, T end, F f, std::ostream& os = std::cout)
{
	auto trp = TransformedRangePrinter<T, F>(begin, end, f);
	os << trp;
}

template<typename M>
class MapPrinter
{
private:
	M& map;

public:
	MapPrinter(M& m) : map(m) {}
	friend ostream& operator<<(std::ostream& os, MapPrinter& mp)
	{
		auto begin = mp.map.begin();
		auto end = mp.map.end();
		os << '{';
		if(begin != end)
		{
			auto& pair = *begin++;
			os << pair.first << ": " << pair.second;
		}
		while(begin != end)
		{
			auto& pair = *begin++;
			os << ", " << pair.first << ": " << pair.second;
		}
		return os << '}';
	}
};

template<typename Map>
void print_map(Map m, std::ostream& os = std::cout)
{
	auto mp = MapPrinter<Map>(m);
	os << mp;
}
#endif