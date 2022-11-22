#pragma once
class InstanceCounter
{
	static int ComponentCount;
	static int objectCount;

public:
	static void AddObjectCount() { objectCount++; }
	static void RemoveObjectCount() { objectCount--; }
	static void AddComponentCount() { ComponentCount++; }
	static void RemoveComponentCount() { ComponentCount--; }

	static int GetComponentCount(){return ComponentCount; }
	static int GetObjectCount() { return objectCount; }

	static void PrintCounts();
};

