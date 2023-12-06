#ifndef _TURQUOISE_INDIGO_UTILS_H__
#define _TURQUOISE_INDIGO_UTILS_H__

#include <string>

enum TIColor {TURQUIOISE, INDIGO};

template <typename T>
std::string to_string( const T& value )
{
  std::ostringstream ss;
  ss << value;
  return ss.str();
}

#endif