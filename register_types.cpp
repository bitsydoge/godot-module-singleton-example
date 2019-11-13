#include "register_types.h"
#include "core/class_db.h"
#include "core/engine.h"

#include "spawner.h"

void register_moduletest_types() 
{
	ClassDB::register_class<Bunny>();
	ClassDB::register_class<Spawner>();


	
}

void unregister_moduletest_types() {

}
