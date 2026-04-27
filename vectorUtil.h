#pragma once
#include <vector>
#include <algorithm>

class vectorUtil
{
public:
    template <typename T>
    static bool contains(const std::vector<T>& vec, const T& elem)
    {
        return std::find(vec.begin(), vec.end(), elem) != vec.end();
    }
};

