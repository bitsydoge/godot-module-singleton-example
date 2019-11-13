#include "spawner.h"
#include "core/engine.h"
#include "scene/main/viewport.h"
#include "scene/resources/packed_scene.h"

void Spawner::_bind_methods() {
	// SceneToLoad
	ClassDB::bind_method(D_METHOD("set_scene_to_spawn", "scene_to_load"), &Spawner::set_scene_to_spawn);
	ClassDB::bind_method(D_METHOD("get_scene_to_spawn"), &Spawner::get_scene_to_spawn);

	ClassDB::bind_method(D_METHOD("spawn"), &Spawner::Spawn);

	ClassDB::bind_method(D_METHOD("get_last_spawned"), &Spawner::get_last_spawned);
	
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "scene_to_spawn", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_scene_to_spawn", "get_scene_to_spawn");
	ADD_SIGNAL(MethodInfo("spawned", PropertyInfo(Variant::OBJECT, "node", PROPERTY_HINT_RESOURCE_TYPE, "Node")));
}

Spawner::Spawner(){
	
}

void Spawner::set_scene_to_spawn(const Ref<PackedScene> &scene) {
	scene_to_spawn = scene;
}

Ref<PackedScene> Spawner::get_scene_to_spawn() const {
	return scene_to_spawn;
}

Node * Spawner::get_last_spawned() {
	if (last_spawned != nullptr)
		return last_spawned;

	//ERR_FAIL_COND_V_MSG(!last_spawned, Node*(), "Can't find overlapping bodies when monitoring is off.");
	return nullptr;
}


void Spawner::Spawn()
{
	Node *new_node = scene_to_spawn->instance();
	add_child(new_node);
	emit_signal("spawned", new_node);
	last_spawned = new_node;
}

void Spawner::_notification(int p_what)
{
	switch (p_what)
	{
		case NOTIFICATION_READY:
		{
			if (Engine::get_singleton()->is_editor_hint() == false) {
				//set_process(true);
				connect("timeout", this, "spawn");
			}
		} break;
		case NOTIFICATION_PROCESS:
		{
			//float delta = get_process_delta_time();
		} break;
	}
}

//void Spawner::_bind_methods() {
//	// MaxTimer
//	ClassDB::bind_method(D_METHOD("set_max_timer", "max_timer"), &Spawner::set_max_timer);
//	ClassDB::bind_method(D_METHOD("get_max_timer"), &Spawner::get_max_timer);
//	// SceneToLoad
//	ClassDB::bind_method(D_METHOD("set_scene_to_spawn", "scene_to_load"), &Spawner::set_scene_to_spawn);
//	ClassDB::bind_method(D_METHOD("get_scene_to_spawn"), &Spawner::get_scene_to_spawn);
//
//	ADD_PROPERTY(PropertyInfo(Variant::REAL, "max_timer"), "set_max_timer", "get_max_timer");
//	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "scene_to_spawn", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_scene_to_spawn", "get_scene_to_spawn");
//
//	ADD_SIGNAL(MethodInfo("on_spawn"));
//}
//
//Spawner::Spawner() {
//	max_timer = 1.0f;
//	current_timer = 0.0f;
//}
//
//void Spawner::set_max_timer(const float timer) {
//	max_timer = timer;
//}
//
//float Spawner::get_max_timer() const {
//	return max_timer;
//}
//
//void Spawner::set_scene_to_spawn(const Ref<PackedScene> &scene) {
//	scene_to_spawn = scene;
//}
//
//Ref<PackedScene> Spawner::get_scene_to_spawn() const {
//	return scene_to_spawn;
//}
//
//void Spawner::Spawn() {
//	Node *new_scene = scene_to_spawn->instance();
//	add_child(new_scene);
//	emit_signal("on_spawn");
//}
//
//void Spawner::Ready() {
//}
//
//void Spawner::Process(float delta) {
//	current_timer += delta;
//	if (current_timer >= max_timer) {
//		current_timer = 0;
//		Spawn();
//	}
//}
//
//void Spawner::_notification(int p_what) {
//	switch (p_what) {
//		case NOTIFICATION_READY: {
//			if (Engine::get_singleton()->is_editor_hint() == false) {
//				set_process(true);
//			}
//		} break;
//		case NOTIFICATION_PROCESS: {
//			Process(get_process_delta_time());
//		} break;
//		default:;
//	}
//}

// ------------------------------------------------------ //
//                   Test Class                           //
// ------------------------------------------------------ //

void Bunny::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_viewport_resize"), &Bunny::_on_viewport_resize);
}

Bunny::Bunny() {
	gravity = 3;
	const float rand_x_velocity = Math::randf() * 10;
	const float rand_y_velocity = Math::random(5, 10);
	velocity = Vector2(rand_x_velocity, rand_y_velocity);
}

void Bunny::Ready() 
{
	get_viewport()->connect("size_changed", this, "_on_viewport_resize");
	_on_viewport_resize();
}

void Bunny::Process(float delta) {
	Vector2 pos = get_position();
	pos.x += velocity.x;
	pos.y += velocity.y;
	velocity.y += gravity;

	if (pos.x > max_x) {
		velocity.x *= -1;
		pos.x = max_x;
	} else if (pos.x < min_x) {
		velocity.x *= -1;
		pos.x = min_x;
	}

	if (pos.y > max_y) {
		velocity.y *= -0.8;
		pos.y = max_y;
		if (Math::randf() > 0.5) {
			velocity.y -= Math::randf() * 12;
		}

	} else if (pos.y < min_y) {
		velocity.y = 0;
		pos.y = min_y;
	}

	set_position(pos);
}

void Bunny::_notification(int p_what) {

	switch (p_what) {
		case NOTIFICATION_READY: {
			if (Engine::get_singleton()->is_editor_hint() == false) {
				set_process(true);
				Ready();
			}
		} break;
		case NOTIFICATION_PROCESS: {
			Process(get_process_delta_time());
		} break;
		default:;
	}
}

// Signal CallBack
void Bunny::_on_viewport_resize() {
	const Rect2 viewport = get_viewport_rect();
	max_x = viewport.size.x;
	max_y = viewport.size.y;
}
