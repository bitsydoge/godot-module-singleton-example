#include "register_types.h"
#include "core/class_db.h"
#include "core/engine.h"
#include "moduletest.h"

static ModuleTest* ModuleTestPtr = NULL;

void register_moduletest_types() {
  ClassDB::register_class<ModuleTest>();
  ModuleTestPtr = memnew(ModuleTest);
  Engine::get_singleton()->add_singleton(Engine::Singleton("ModuleTest", ModuleTest::get_singleton()));
}

void unregister_moduletest_types() {
  memdelete(ModuleTestPtr);
}
