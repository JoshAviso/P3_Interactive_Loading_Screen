#include <Input/Input.h>

#include <Input/ILeftClickInputCallback.h>
#include <Input/IRightClickInputCallback.h>

#include <Application.h>
#include <Core/Logger.h>

void Input::UpdateInput(sf::Event& event)
{
	// Mouse Handling
    sf::Vector2i sfMousePos = sf::Mouse::getPosition(*(Application::Instance->GetWindow()));
	_instance->ProcessMousePosition({sfMousePos.x, sfMousePos.y});

	// Event Handling
	switch (event.type) {
	// Mouse Events
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left) {
			if(!Mouse.LeftDown) Mouse.LeftPressed = true;
			Mouse.LeftDown = true;
			for (auto& callback : _instance->_leftClickCallbacks)
				if(callback != nullptr) callback->OnLeftClickPressed(Mouse.Position);
		}
		else if (event.mouseButton.button == sf::Mouse::Right) {
			if(!Mouse.RightDown) Mouse.RightPressed = true;
			Mouse.RightDown = true;
			for (auto& callback : _instance->_rightClickCallbacks) 
				if(callback != nullptr) callback->OnRightClickPressed(Mouse.Position);
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Left) {
			if(Mouse.LeftDown) Mouse.LeftReleased = true;
			Mouse.LeftDown = false;
			for (auto& callback : _instance->_leftClickCallbacks)
				if (callback != nullptr) callback->OnLeftClickReleased(Mouse.Position);
		}
		else if (event.mouseButton.button == sf::Mouse::Right) {
			if(Mouse.RightDown) Mouse.RightReleased = true;
			Mouse.RightDown = false;
			for (auto& callback : _instance->_rightClickCallbacks) 
				if (callback != nullptr) callback->OnRightClickReleased(Mouse.Position);
		}
		break;
	case sf::Event::MouseWheelScrolled:
		if (event.mouseWheelScroll.wheel == sf::Mouse::Wheel::VerticalWheel) {
			Mouse.ScrollDelta = event.mouseWheelScroll.delta;
		}
		else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) {
			// Horizontal Scroll???
		}
        break;
	// Key Handling
	case sf::Event::KeyPressed:
		_instance->ProcessKeyInput(event.key.code, true);
		break;
	case sf::Event::KeyReleased:
		_instance->ProcessKeyInput(event.key.code, false);
		break;
	default:
		break;
	}
}

void Input::ResetInput()
{
	Mouse.LeftPressed = false;
	Mouse.LeftReleased = false;
	Mouse.RightPressed = false;
	Mouse.RightReleased = false;
	
	for (int i = 0; i < KEY_COUNT; i++) {
		KeyPressed[(EKeyCode)i] = false;
		KeyReleased[(EKeyCode)i] = false;
	}
}

Input::MouseData Input::Mouse = Input::MouseData();
void Input::ProcessMousePosition(Vec2i sfNewPos)
{
	Vec2i newPos = sfNewPos;
	Mouse.Delta = newPos - Mouse.Position;
	Mouse.LastPosition = Mouse.Position;
	Mouse.Position = newPos;
}

Input::EKeyCode Input::LastUsedKey = Input::EKeyCode::KEY_COUNT;
Dict<Input::EKeyCode, bool> Input::KeyDown;
Dict<Input::EKeyCode, bool> Input::KeyPressed;
Dict<Input::EKeyCode, bool> Input::KeyReleased;
void Input::ProcessKeyInput(sf::Keyboard::Key key, bool pressed)
{
    EKeyCode keycode;  
    switch (key) {  
       case sf::Keyboard::A: keycode = Key_A; break;  
       case sf::Keyboard::B: keycode = Key_B; break;  
       case sf::Keyboard::C: keycode = Key_C; break;  
       case sf::Keyboard::D: keycode = Key_D; break;  
       case sf::Keyboard::E: keycode = Key_E; break;  
       case sf::Keyboard::F: keycode = Key_F; break;  
       case sf::Keyboard::G: keycode = Key_G; break;  
       case sf::Keyboard::H: keycode = Key_H; break;  
       case sf::Keyboard::I: keycode = Key_I; break;  
       case sf::Keyboard::J: keycode = Key_J; break;  
       case sf::Keyboard::K: keycode = Key_K; break;  
       case sf::Keyboard::L: keycode = Key_L; break;  
       case sf::Keyboard::M: keycode = Key_M; break;  
       case sf::Keyboard::N: keycode = Key_N; break;  
       case sf::Keyboard::O: keycode = Key_O; break;  
       case sf::Keyboard::P: keycode = Key_P; break;  
       case sf::Keyboard::Q: keycode = Key_Q; break;  
       case sf::Keyboard::R: keycode = Key_R; break;  
       case sf::Keyboard::S: keycode = Key_S; break;  
       case sf::Keyboard::T: keycode = Key_T; break;  
       case sf::Keyboard::U: keycode = Key_U; break;  
       case sf::Keyboard::V: keycode = Key_V; break;  
       case sf::Keyboard::W: keycode = Key_W; break;  
       case sf::Keyboard::X: keycode = Key_X; break;  
       case sf::Keyboard::Y: keycode = Key_Y; break;  
       case sf::Keyboard::Z: keycode = Key_Z; break;  
       case sf::Keyboard::Num0: keycode = Key_0; break;  
       case sf::Keyboard::Num1: keycode = Key_1; break;  
       case sf::Keyboard::Num2: keycode = Key_2; break;  
       case sf::Keyboard::Num3: keycode = Key_3; break;  
       case sf::Keyboard::Num4: keycode = Key_4; break;  
       case sf::Keyboard::Num5: keycode = Key_5; break;  
       case sf::Keyboard::Num6: keycode = Key_6; break;  
       case sf::Keyboard::Num7: keycode = Key_7; break;  
       case sf::Keyboard::Num8: keycode = Key_8; break;  
       case sf::Keyboard::Num9: keycode = Key_9; break;  
       case sf::Keyboard::Escape: keycode = Key_Escape; break;  
       case sf::Keyboard::LControl: keycode = Key_LCtrl; break;  
       case sf::Keyboard::LShift: keycode = Key_LShift; break;  
       case sf::Keyboard::LAlt: keycode = Key_LAlt; break;  
       case sf::Keyboard::RControl: keycode = Key_RCtrl; break;  
       case sf::Keyboard::RShift: keycode = Key_RShift; break;  
       case sf::Keyboard::RAlt: keycode = Key_RAlt; break;   
       case sf::Keyboard::Menu: keycode = Key_Menu; break;  /*
       case sf::Keyboard::LBracket: keycode = Key_LBracket; break;  
       case sf::Keyboard::RBracket: keycode = Key_RBracket; break;  
       case sf::Keyboard::Semicolon: keycode = Key_Semicolon; break;  
       case sf::Keyboard::Comma: keycode = Key_Comma; break;  
       case sf::Keyboard::Period: keycode = Key_Period; break;  
       case sf::Keyboard::Quote: keycode = Key_Quote; break;  
       case sf::Keyboard::Slash: keycode = Key_Slash; break;  
       case sf::Keyboard::Backslash: keycode = Key_Backslash; break;  
       case sf::Keyboard::Tilde: keycode = Key_Tilde; break;  
       case sf::Keyboard::Equal: keycode = Key_Equal; break;  
       case sf::Keyboard::Hyphen: keycode = Key_Hyphen; break;  */
       case sf::Keyboard::Space: keycode = Key_Space; break;  
       case sf::Keyboard::Enter: keycode = Key_Enter; break;  
       case sf::Keyboard::Backspace: keycode = Key_Backspace; break;  
       case sf::Keyboard::Tab: keycode = Key_Tab; break;  
       case sf::Keyboard::PageUp: keycode = Key_PageUp; break;  
       case sf::Keyboard::PageDown: keycode = Key_PageDown; break;  
       case sf::Keyboard::End: keycode = Key_End; break;  
       case sf::Keyboard::Home: keycode = Key_Home; break;  
       case sf::Keyboard::Insert: keycode = Key_Insert; break;  
       case sf::Keyboard::Delete: keycode = Key_Delete; break;  /*
       case sf::Keyboard::Add: keycode = Key_Add; break;  
       case sf::Keyboard::Subtract: keycode = Key_Subtract; break;  
       case sf::Keyboard::Multiply: keycode = Key_Multiply; break;  
       case sf::Keyboard::Divide: keycode = Key_Divide; break;  */
       case sf::Keyboard::Left: keycode = Key_Left; break;  
       case sf::Keyboard::Right: keycode = Key_Right; break;  
       case sf::Keyboard::Up: keycode = Key_Up; break;  
       case sf::Keyboard::Down: keycode = Key_Down; break;  
       case sf::Keyboard::Numpad0: keycode = Key_Numpad0; break;  
       case sf::Keyboard::Numpad1: keycode = Key_Numpad1; break;  
       case sf::Keyboard::Numpad2: keycode = Key_Numpad2; break;  
       case sf::Keyboard::Numpad3: keycode = Key_Numpad3; break;  
       case sf::Keyboard::Numpad4: keycode = Key_Numpad4; break;  
       case sf::Keyboard::Numpad5: keycode = Key_Numpad5; break;  
       case sf::Keyboard::Numpad6: keycode = Key_Numpad6; break;  
       case sf::Keyboard::Numpad7: keycode = Key_Numpad7; break;  
       case sf::Keyboard::Numpad8: keycode = Key_Numpad8; break;  
       case sf::Keyboard::Numpad9: keycode = Key_Numpad9; break;  
       case sf::Keyboard::F1: keycode = Key_F1; break;  
       case sf::Keyboard::F2: keycode = Key_F2; break;  
       case sf::Keyboard::F3: keycode = Key_F3; break;  
       case sf::Keyboard::F4: keycode = Key_F4; break;  
       case sf::Keyboard::F5: keycode = Key_F5; break;  
       case sf::Keyboard::F6: keycode = Key_F6; break;  
       case sf::Keyboard::F7: keycode = Key_F7; break;  
       case sf::Keyboard::F8: keycode = Key_F8; break;  
       case sf::Keyboard::F9: keycode = Key_F9; break;  
       case sf::Keyboard::F10: keycode = Key_F10; break;  
       case sf::Keyboard::F11: keycode = Key_F11; break;  
       case sf::Keyboard::F12: keycode = Key_F12; break;  
       case sf::Keyboard::Pause: keycode = Key_Pause; break;  
       default: keycode = KEY_COUNT; break;  
    }
    
    if (keycode == KEY_COUNT) return;
    
    LastUsedKey = keycode;
    KeyDown[keycode] = pressed;
    KeyPressed[keycode] = !KeyDown[keycode] && pressed ? true : KeyPressed[keycode];
    KeyReleased[keycode] = KeyDown[keycode] && !pressed ? true : KeyPressed[keycode];
}

void Input::RegisterLeftClickCallback(ILeftClickInputCallback* callback)
{
	_instance->_leftClickCallbacks.push_back(callback);
}

void Input::UnregisterLeftClickCallback(ILeftClickInputCallback* callback)
{
	auto it = std::find(_instance->_leftClickCallbacks.begin(), _instance->_leftClickCallbacks.end(), callback);
	if (it != _instance->_leftClickCallbacks.end()) {
		_instance->_leftClickCallbacks.erase(it);
	}
}

void Input::RegisterRightClickCallback(IRightClickInputCallback* callback)
{
	_instance->_rightClickCallbacks.push_back(callback);
}

void Input::UnregisterRightClickCallback(IRightClickInputCallback* callback)
{
	auto it = std::find(_instance->_rightClickCallbacks.begin(), _instance->_rightClickCallbacks.end(), callback);
	if (it != _instance->_rightClickCallbacks.end()) {
		_instance->_rightClickCallbacks.erase(it);
	}
}

// SINGLETON 
Input* Input::_instance = nullptr;
Input* Input::Initialize()
{
    if (_instance != nullptr) return _instance;

    _instance = new Input();
    return _instance;
}

Input::Input()
{

}

Input::~Input() {}
