#include "utilities.h"

int                         comp_str(const char *str1, const char *str2)
{
  int                       i;

  i = 0;
  while (str1[i] && str2[i] && str1[i] == str2[i])
  {
      ++i;
  }
  return (str1[i] == str2[i] || !str1[i] ||!str2[i]);
}

