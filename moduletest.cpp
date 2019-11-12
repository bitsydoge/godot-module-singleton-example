#include "moduletest.h"

ModuleTest * ModuleTest::singleton;

ModuleTest::ModuleTest() {
  singleton = this;
}

ModuleTest* ModuleTest::get_singleton() {
  return singleton;
}

int ModuleTest::get_value()
{
  return 1233219090;
}

void ModuleTest::_bind_methods() {
  ClassDB::bind_method("get_value", &ModuleTest::get_value);
}
