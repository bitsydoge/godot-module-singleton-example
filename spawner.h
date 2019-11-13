#ifndef SPAWNER_H
#define SPAWNER_H

#include "scene/2d/sprite.h"
#include "scene/main/timer.h"

//class Spawner : public Node 
//{
//	GDCLASS(Spawner, Node);
//
//	float max_timer;
//	float current_timer;
//	Ref<PackedScene> scene_to_spawn;
//	
//protected:
//	void set_max_timer(float timer);
//	float get_max_timer() const;
//	void set_scene_to_spawn(const Ref<PackedScene> &scene);
//	Ref<PackedScene> get_scene_to_spawn() const;
//	static void _bind_methods();
//
//public:
//	Spawner();
//	void Ready();
//	void Process(float delta);
//	void _notification(int p_what);
//
//	void Spawn();
//};

class Spawner : public Timer
{
	GDCLASS(Spawner, Timer);
	Ref<PackedScene> scene_to_spawn;
	Node * last_spawned = nullptr;
	
	void Spawn();
	
protected:
	void set_scene_to_spawn(const Ref<PackedScene> &scene);
	Ref<PackedScene> get_scene_to_spawn() const;
	Node *get_last_spawned();
	static void _bind_methods();

public:
	Spawner();
	void _notification(int p_what);
};

// ------------------------------------------------------ //
//                   Test Class                           //
// ------------------------------------------------------ //

class Bunny : public Sprite {
	GDCLASS(Bunny, Sprite);

	int gravity;
	int max_x;
	int min_x=0;
	int max_y;
	int min_y=0;
	Vector2 velocity;

protected:
	static void _bind_methods();

public:
	Bunny();
	void Ready();
	void Process(float delta);

	void _notification(int p_what);
	void _on_viewport_resize();
};

#endif
