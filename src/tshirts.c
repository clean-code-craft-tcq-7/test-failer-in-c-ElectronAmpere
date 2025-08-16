#include <stdio.h>

#include "./tshirts.h"
char tShirtSize(int cms) {
  char sizeName = '\0';
  if (cms <= 38) {
    sizeName = 'S';
  } else if (cms <= 42) {
    sizeName = 'M';
  } else {
    sizeName = 'L';
  }
  return sizeName;
}
