#ifndef DEF_H
#define DEF_H

using uint = unsigned int;

namespace mth {
  static const double Tollerance = 1e-15;
  template<typename T>
  class vec;
}

using color = mth::vec<float>;
using vec2d = mth::vec<int>;

#endif // DEF_H
