#ifndef __PE_KeyboardManager_H__
#define __PE_KeyboardManager_H__

#include "PEPrefix.h"

class PEKeyboardEvent
{
	public:
		enum KeyState{
			KEY_UNTOUCHED=0,
			KEY_PRESS_BEGIN,
			KEY_PRESS_LAST,
			KEY_PRESS_END,
		};
		PEKeyboardEvent(int keyId);
		~PEKeyboardEvent();

		void setSceneIn(GLFWwindow *window){
			m_window = window;
		}
		void check();

		void setPressBeginFunction(std::function<void()> fx);
		void setPressLastFunction(std::function<void()> fx);
		void setPressEndFunction(std::function<void()> fx);
	private:
		std::function<void()> m_pressBeginFunc;
		std::function<void()> m_pressLastFunc;
		std::function<void()> m_pressEndFunc;
		GLFWwindow *m_window;
		int m_keyId;
		PEKeyboardEvent::KeyState m_status;
		int m_count;
};

class PEKeyboardManager
{
public:
	
private:

};


#endif
