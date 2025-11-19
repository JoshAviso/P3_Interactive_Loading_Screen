#pragma once

#include <SFML/Graphics.hpp>

#include <Core/Common.h>
#include <Math/Vec2.h>
#include <Math/Vec2i.h>

class ILeftClickInputCallback;
class IRightClickInputCallback;

class Input
{
public:
	struct MouseData {
		bool LeftDown = false;
		bool LeftPressed = false;
		bool LeftReleased = false;
		bool RightDown = false;
		bool RightPressed = false;
		bool RightReleased = false;
		Vec2i Position = { 0, 0 };
		Vec2i LastPosition = { 0, 0 };
		Vec2i Delta = {0, 0} ;
		float ScrollDelta = 0.f;
	};	
	static MouseData Mouse;

    enum EKeyCode {
					// Alphabet keys
					Key_A,
					Key_B,
					Key_C,
					Key_D,
					Key_E,
					Key_F,
					Key_G,
					Key_H,
					Key_I,
					Key_J,
					Key_K,
					Key_L,
					Key_M,
					Key_N,
					Key_O,
					Key_P,
					Key_Q,
					Key_R,
					Key_S,
					Key_T,
					Key_U,
					Key_V,
					Key_W,
					Key_X,
					Key_Y,
					Key_Z,

					// Numeric keys
					Key_0,
					Key_1,
					Key_2,
					Key_3,
					Key_4,
					Key_5,
					Key_6,
					Key_7,
					Key_8,
					Key_9,

					// Function keys
					Key_F1,
					Key_F2,
					Key_F3,
					Key_F4,
					Key_F5,
					Key_F6,
					Key_F7,
					Key_F8,
					Key_F9,
					Key_F10,
					Key_F11,
					Key_F12,

					// Navigation keys
					Key_Up,
					Key_Down,
					Key_Left,
					Key_Right,
					Key_PageUp,
					Key_PageDown,
					Key_Home,
					Key_End,
					Key_Insert,
					Key_Delete,

					// Modifier keys
					Key_LCtrl,
					Key_RCtrl,
					Key_LShift,
					Key_RShift,
					Key_LAlt,
					Key_RAlt,

					// Special keys
					Key_Space,
					Key_Escape,
					Key_Enter,
					Key_Backspace,
					Key_Tab,
					Key_CapsLock,
					Key_NumLock,
					Key_ScrollLock,

					// Numpad keys
					Key_Numpad0,
					Key_Numpad1,
					Key_Numpad2,
					Key_Numpad3,
					Key_Numpad4,
					Key_Numpad5,
					Key_Numpad6,
					Key_Numpad7,
					Key_Numpad8,
					Key_Numpad9,
					Key_NumpadAdd,
					Key_NumpadSubtract,
					Key_NumpadMultiply,
					Key_NumpadDivide,
					Key_NumpadDecimal,
					Key_NumpadEnter,

					// Miscellaneous keys
					Key_PrintScreen,
					Key_Pause,
					Key_Menu,

					// Total count
					KEY_COUNT
    };
	static Dict<EKeyCode, bool> KeyDown;
	static Dict<EKeyCode, bool> KeyPressed;
	static Dict<EKeyCode, bool> KeyReleased;
	static EKeyCode LastUsedKey;

private:
	List<ILeftClickInputCallback*> _leftClickCallbacks;
	List<IRightClickInputCallback*> _rightClickCallbacks;
	static void RegisterLeftClickCallback(ILeftClickInputCallback* callback);
	static void UnregisterLeftClickCallback(ILeftClickInputCallback* callback);
	static void RegisterRightClickCallback(IRightClickInputCallback* callback);
	static void UnregisterRightClickCallback(IRightClickInputCallback* callback);
	
private:
	static void UpdateInput(sf::Event& event);
	static void ResetInput();
	void ProcessMousePosition(Vec2i sfNewPos);
	void ProcessKeyInput(sf::Keyboard::Key key, bool pressed);

// SINGLETON
public:
	static Input* Initialize();
private:
	static Input* _instance;
	explicit Input();
	~Input();
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

public:
	friend class Application;
	friend class ILeftClickInputCallback;
	friend class IRightClickInputCallback;
};

