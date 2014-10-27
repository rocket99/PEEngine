#include "PEKeyboardManager.h"

PEKeyboardEvent::PEKeyboardEvent(int keyId)
{
	m_keyId = keyId;
	m_status = KEY_UNTOUCHED;
	m_pressBeginFunc = 0;
	m_pressLastFunc = 0;
	m_pressEndFunc = 0;
}

PEKeyboardEvent::~PEKeyboardEvent()
{

}

void PEKeyboardEvent::check()
{
	if(glfwGetKey(m_window, m_keyId) == GLFW_PRESS){
		switch(m_status){
			case KEY_UNTOUCHED:
			{
				if(m_pressBeginFunc != 0){
					PELog("key press begin");
					m_pressBeginFunc();
				}
				m_status = KEY_PRESS_BEGIN;
				m_count = 0;
			}
				break;
			case KEY_PRESS_BEGIN:
				++ m_count;
				if(m_count >= 10000){
					if(m_pressLastFunc != 0){
						m_pressLastFunc();
					}
					m_status = KEY_PRESS_LAST;
				}
				break;
			case KEY_PRESS_LAST:
				break;
			case KEY_PRESS_END:
				break;
		
		}

	}else{
		if(m_status != KEY_UNTOUCHED){
			PELog("key pres end.");
			if(m_pressEndFunc != 0){
				m_pressEndFunc();
			}
		}
		m_status = KEY_UNTOUCHED;
	}
}

void PEKeyboardEvent::setPressBeginFunction(std::function<void()> fx){
	m_pressBeginFunc = fx;
}

void PEKeyboardEvent::setPressLastFunction(std::function<void()> fx){
	m_pressLastFunc = fx;
}

void PEKeyboardEvent::setPressEndFunction(std::function<void()> fx){
	m_pressEndFunc = fx;
}
