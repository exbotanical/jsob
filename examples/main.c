#include <stdio.h>

#include "jsob.h"

int main(int argc, char const *argv[]) {
  static const char *json = "{\"some\":{\"very\": {\"nested\":\"json!\"}}}";

  char *ret = jsob_getstr(json, "some.very.nested");
  printf("retval: %s\n", ret);

  return 0;
}
