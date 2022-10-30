#pragma once

class Application
{
public:
	virtual void Start() {}
	virtual void Update() {}
	virtual void HandleEvents(union SDL_Event& ev) {}
};

// To be defined in CLIENT
Game* CreateEngine();

