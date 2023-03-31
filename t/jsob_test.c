#include "jsob.h"

#include "tap.c/tap.h"

static const char *json =
    "{\"key\":\"value\",\"name\": {\"cookie\": {\"value\": "
    "\"someval\"},\"star\": 4,\"hits\": [1, 2, 3, 4]},\"fork\": \"spoon\"}";

void test_jsob_getstr_toplvl_happycase() {
  is(jsob_getstr(json, "fork"), "spoon",
     "retrieves a top-level JSON string value");

  is(jsob_getstr(json, "key"), "value",
     "retrieves a top-level JSON string value");
}

void test_jsob_getstr_toplvl_sadcase() {
  is(jsob_getstr(json, "keyd"), NULL,
     "non-existent top-level key returns NULL");
}

void test_jsob_getstr_nested_happycase() {
  is(jsob_getstr(json, "name.cookie.value"), "someval",
     "retrieves a nested JSON string value");
}

void test_jsob_getstr_nested_sadcase_nomatch() {
  is(jsob_getstr(json, "name.cookie.valsue"), NULL,
     "non-existent nested key returns NULL");

  is(jsob_getstr(json, "name.cookie.value.cdc"), NULL,
     "non-existent nested key returns NULL");

  is(jsob_getstr(json, "name.cookie"), NULL,
     "non-existent nested key returns NULL");
}

void test_jsob_getstr_nested_sadcase_nonterminal() {
  is(jsob_getstr(json, "name.cookie"), NULL,
     "non-terminal nested key returns NULL");
}

void test_jsob_getstr_nested_wrongtype() {
  is(jsob_getstr(json, "name.star"), NULL, "wrong type returns NULL");
}

void test_jsob_getint() {
  ok(jsob_getint(json, "name.star") == 4, "retrieves a nested JSON int value");
}

void test_jsob_getint_sadcase() {
  ok(jsob_getint(json, "name.star.v") == 0,
     "non-existent nested key returns 0");
}

int main() {
  plan(11);

  test_jsob_getstr_toplvl_happycase();
  test_jsob_getstr_toplvl_sadcase();
  test_jsob_getstr_nested_happycase();
  test_jsob_getstr_nested_sadcase_nomatch();
  test_jsob_getstr_nested_sadcase_nonterminal();
  test_jsob_getstr_nested_wrongtype();
  test_jsob_getint();
  test_jsob_getint_sadcase();

  done_testing();
}
