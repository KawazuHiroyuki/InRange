#include <iostream>
#include "InRange.h"


template<typename Type, bool IncludeMin, bool IncludeMax>
bool within(const InRange<Type, IncludeMin, IncludeMax>& range, const Type& value)
{
    return range.within(value);
}

template<typename Type, bool IncludeMin, bool IncludeMax>
const Type& clamp(const InRange<Type, IncludeMin, IncludeMax>& range, const Type& value)
{
    return range.clamp(value);
}

template<typename Type, Type Min, Type Max>
bool within(const InRangeEx<Type, Min, Max>& range, const Type& value)
{
    return range.within(value);
}

template<typename Type, Type Min, Type Max>
const Type& clamp(const InRangeEx<Type, Min, Max>& range, const Type& value)
{
    return range.clamp(value);
}

int main()
{
    {
        InRange<int, false, false> a(0, 21);
        bool result0;
        result0 = a.within(-1);
        result0 = a.within(0);
        result0 = a.within(1);
        result0 = a.within(20);
        result0 = a.within(21);
        result0 = a.within(22);

        int result1 = a.clamp(-1);
        result1 = -100;
        result1 = a.clamp(0);
        result1 = -100;
        result1 = a.clamp(1);
        result1 = -100;
        result1 = a.clamp(20);
        result1 = -100;
        result1 = a.clamp(21);
        result1 = -100;
        result1 = a.clamp(22);

        bool result6 = within(a, 1);
        bool result7 = within(a, -1);
        bool result8 = within(a, 22);

        int result9 = clamp(a, 3);
        int result10 = clamp(a, -2);
        int result11 = clamp(a, 23);
        int b = result11;
    }

    {
        InRangeEx<int, 0, 21> a;
        bool result0 = a.within(1);
        bool result1 = a.within(-1);
        bool result2 = a.within(22);

        int result3 = a.clamp(3);
        int result4 = a.clamp(-2);
        int result5 = a.clamp(23);

        bool result6 = within(a, 1);
        bool result7 = within(a, -1);
        bool result8 = within(a, 22);

        int result9 = clamp(a, 3);
        int result10 = clamp(a, -2);
        int result11 = clamp(a, 23);
        int b = result11;
    }
}
