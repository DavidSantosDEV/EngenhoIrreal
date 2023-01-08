#pragma once
class InstanceCounter
{
	static int ComponentCount;
	static int objectCount;

public:
	static void AddObjectCount(class GameObject* other);
	static void RemoveObjectCount(GameObject* other);
	static void AddComponentCount(class Component* other);
	static void RemoveComponentCount(Component* other);

	static int GetComponentCount(){return ComponentCount; }
	static int GetObjectCount() { return objectCount; }

	static void PrintCounts();
};

