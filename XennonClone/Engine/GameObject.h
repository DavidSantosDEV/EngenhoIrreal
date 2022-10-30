#pragma once
#include <vector>
#include <memory>

class GameObject
{
public:
	virtual void Start();
	virtual void Update();

	void AddComponent(std::shared_ptr<class Component> componentToAdd);

protected:
	std::vector<std::shared_ptr<class Component>> components;
};

