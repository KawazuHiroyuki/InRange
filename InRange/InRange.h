#pragma once

#include <cassert>
#include <algorithm>
#include <limits>
#include <type_traits>
#include <functional>


template <bool IncludeBounds>
struct Compare
{
};

template <>
struct Compare<true>
{
    template <typename Type>
    constexpr bool operator()(const Type& lhs, const Type& rhs) const
    {
        return std::less_equal<Type>()(lhs, rhs);
    }
};

template <>
struct Compare<false>
{
    template <typename Type>
    constexpr bool operator()(const Type& lhs, const Type& rhs) const
    {
        return std::less<Type>()(lhs, rhs);
    }
};


template <
    typename Type_,
    bool IncludeMin = true,
    bool IncludeMax = true
>
class InRange
{
public:
    using Type = Type_;
    using MinCompare = Compare<IncludeMin>;
    using MaxCompare = Compare<IncludeMax>;

private:
    Type min = std::numeric_limits<Type>::min();
    Type max = std::numeric_limits<Type>::max();

public:
    InRange(Type min_ = std::numeric_limits<Type>::min(), Type max_ = std::numeric_limits<Type>::max())
        : min(min_)
        , max(max_)
    {
        assert(min <= max);
    }

    constexpr bool within(const Type& value) const
    {
        if (!MinCompare()(min, value)) {
            return false;
        }
        if (!MaxCompare()(value, max)) {
            return false;
        }
        return true;
    }

    // NG
    constexpr const Type& clamp(const Type& value) const
    {
        return std::min(std::max(value, min, MaxCompare()), max, MinCompare());
    }

private:
    

};

template <
    typename Type_,
    Type_ Min_ = std::numeric_limits<Type_>::min(),
    Type_ Max_ = std::numeric_limits<Type_>::max()
>
class InRangeEx
{
    //statc_assert(std::less_equal<Type_>()(typename Min_, typename Max_), "");

public:
    using Type = Type_;

private:
    static constexpr Type Min = Min_;
    static constexpr Type Max = Max_;

public:

    constexpr bool within(const Type& value) const
    {
        if (!std::less_equal<Type>()(Min, value)) {
            return false;
        }
        if (!std::less_equal<Type>()(value, Max)) {
            return false;
        }
        return true;
    }

    constexpr const Type& clamp(const Type& value) const
    {
        return std::min(std::max(value, Min), Max);
    }
};