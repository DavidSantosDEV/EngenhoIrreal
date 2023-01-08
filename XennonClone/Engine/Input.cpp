#include "Input.h"
#include "SDL.h"
#include "Log.h"
#include "InitError.h"
#include "MathHelper.h"

SDL_Event Input::m_Event;

SDL_GameController* m_GameController = nullptr;
constexpr int JOYSTICK_DEAD_ZONE = 8000;
constexpr int JOYSTICK_MAX = 25000;

Input::Input()
{
	if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG_ERROR("SDL gamecontroller subsystem init error");
		throw InitError();
	}
	if (SDL_NumJoysticks() < 1)
	{
		LOG_WARNING("No gamepad detected");
	}
	else
	{
		m_GameController = SDL_GameControllerOpen(0);
	}
}

void Input::ReceiveEvent(union SDL_Event& ev)
{
	m_Event = ev;
}

union SDL_Event Input::GetInputEvent()
{
	return m_Event;
}

int Input::GetRightAxisValue()
{
	// Get and clamp gamepad axis value from -1 to 1
	int gamepadRightAxis = SDL_GameControllerGetAxis(m_GameController, SDL_CONTROLLER_AXIS_LEFTX);
	MathHelper::ClampIntRef(gamepadRightAxis, -JOYSTICK_MAX, JOYSTICK_MAX);

	// Get Keyboard state (supports key yield down)
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_RIGHT] ||
		gamepadRightAxis > JOYSTICK_DEAD_ZONE)
	{
		return 1;
	}
	else if (currentKeyStates[SDL_SCANCODE_LEFT] || gamepadRightAxis < -JOYSTICK_DEAD_ZONE)
	{
		return -1;
	}
	return 0;
}

int Input::GetUpAxisValue()
{
	// Get and clamp gamepad axis value from -1 to 1
	int gamepadUpAxis = SDL_GameControllerGetAxis(m_GameController, SDL_CONTROLLER_AXIS_LEFTY);
	MathHelper::ClampIntRef(gamepadUpAxis, -JOYSTICK_MAX, JOYSTICK_MAX);

	// Get Keyboard state (supports key yield down)
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_UP] ||
		gamepadUpAxis < -JOYSTICK_DEAD_ZONE)
	{
		return 1;
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN] || gamepadUpAxis > JOYSTICK_DEAD_ZONE)
	{
		return -1;
	}
	return 0;
}

bool Input::IsFireKeyDown()
{
	// Returns 0 or 1
	short isGamepadButtonPressed = SDL_GameControllerGetButton(m_GameController, SDL_CONTROLLER_BUTTON_A);
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	return currentKeyStates[SDL_SCANCODE_SPACE] || isGamepadButtonPressed;
}

bool Input::IsChangeRenderingKeyDown()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	return currentKeyStates[SDL_SCANCODE_P];
}
