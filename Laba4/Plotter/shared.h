#ifndef SHARED_H
#define SHARED_H

#include <string>
#include <list>
#include <memory>

struct Rect
{
    double x;
    double y;
    double width;
    double height;
};

struct Point
{
    double x;
    double y;
};

struct Line
{
    Point beg;
    Point end;
};

template <typename T>
using List = std::list<T>;

template <typename T>
struct Range
{
    T begin;
    T end;
};

using RangeD = Range<double>;

template <typename T>
using Ptr = std::shared_ptr<T>;

template <typename T>
using WeakPtr = std::weak_ptr<T>;

#endif // SHARED_H
