/**
 * Printing algorithms for more involved (but common) data structures
 * Authors: Erich Gubler, erichdongubler@gmail.com
 */
#ifndef PRINTALGORITHMS_H
#define PRINTALGORITHMS_H
#include <iostream>


// Stream functor that prints random-access ranges of the form "[a, b, c]"
template<typename Iter>
class RangePrinter
{
private:
	Iter begin;
	Iter end;

public:
	RangePrinter(Iter b, Iter e) : begin(b), end(e) {}

	friend std::ostream& operator<<(std::ostream& os, RangePrinter&& rp)
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
RangePrinter<T> range_printer(T begin, T end)
{
	return RangePrinter<T>(begin, end);
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

	friend std::ostream& operator<<(std::ostream& os, TransformedRangePrinter&& trp)
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
TransformedRangePrinter<T, F> transformed_range_printer(T begin, T end, F f)
{
	return TransformedRangePrinter<T, F>(begin, end, f);
}

template<typename M>
class MapPrinter
{
private:
	M& map;

public:
	MapPrinter(M& m) : map(m) {}
	friend std::ostream& operator<<(std::ostream& os, MapPrinter& mp)
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
void map_printer(Map& m)//TODO: Make const!
{
	return MapPrinter<Map>(m);
}

#endif