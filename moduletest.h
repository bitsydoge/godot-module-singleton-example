#ifndef GODOT_ModuleTest_H
#define GODOT_ModuleTest_H

#include "core/reference.h"

class ModuleTest: public Reference {
  GDCLASS(ModuleTest, Reference);

public:
  ModuleTest();
  static ModuleTest* get_singleton();

  int get_value();

protected:
  static ModuleTest* singleton;
  static void _bind_methods();
};

#endif
