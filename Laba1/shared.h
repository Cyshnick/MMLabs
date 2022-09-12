#ifndef SHARED_H
#define SHARED_H

#include <functional>
#include <cmath>
#include <vector>
#include <tuple>
#include <memory>

using Real = double;
using RealFunc = std::function<Real(Real)>;

template <typename T>
using Container = std::vector<T>;
using Reals = Container<double>;

using RealsContainer = Container<Reals>;

using RealPair = std::pair<Real, Real>;
using RealPairs = Container<std::pair<Real, Real>>;
using RealFunctions = Container<RealFunc>;

const Real PI = 3.1415926535897932384626433832795;

template <typename T>
using Ptr = std::shared_ptr<T>;

template <typename T>
using WeakPtr = std::weak_ptr<T>;

#endif // SHARED_H
