#pragma once

#include <type_traits>

namespace linAlg { 

template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

} // namespace linAlg
