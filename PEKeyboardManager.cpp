#include "PEKeyboardManager.h"

PEKeyboardEvent::PEKeyboardEvent(int keyId, bool enable)
{
	m_keyId = keyId;
	m_status = KEY_UNTOUCHED;
	m_pressBeginFunc = 0;
	m_pressLastFunc = 0;
	m_pressEndFunc = 0;
}

PEKeyboardEvent::PEKeyboardEvent(const PEKeyboardEvent &event)
{
	m_keyId = event.m_keyId;
	m_status = event.m_status;
	m_pressBeginFunc = event.m_pressBeginFunc;
	m_pressLastFunc = event.m_pressLastFunc;
	m_pressEndFunc = event.m_pressEndFunc;
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
					m_pressBeginFunc();
				}
				m_status = KEY_PRESS_BEGIN;
				m_count = 0;
			}
				break;
			case KEY_PRESS_BEGIN:
				++ m_count;
				if(m_count >= 4){					
					m_status = KEY_PRESS_LAST;
				}
				break;
			case KEY_PRESS_LAST:
			{
				if(m_pressLastFunc != 0){
					m_pressLastFunc();
				}
			}
				break;
			case KEY_PRESS_END:
				break;
			default:
				break;
		}
	}else{
		if(m_status != KEY_UNTOUCHED){
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

#pragma PEKeyboardEvent Manager

PEKeyboardManager::PEKeyboardManager()
{

}
PEKeyboardManager::~PEKeyboardManager()
{
	for(int i=0; i<m_events.size(); ++i){
		delete m_events[i];
	}
	m_events.clear();
}

static PEKeyboardManager *instance = NULL;
PEKeyboardManager *PEKeyboardManager::getInstance()
{
	if(instance == NULL){
		instance = new PEKeyboardManager();
	}
	return instance;
}

void PEKeyboardManager::purge()
{
	if(instance == NULL){
		return;
	}
	delete instance;
	instance = NULL;
}

void PEKeyboardManager::addKeyboardEvent(PEKeyboardEvent *event)
{
	std::vector<PEKeyboardEvent*>::iterator it = m_events.begin();
	while(it != m_events.end()){
		if((*it)->getKeyId() == event->getKeyId()){
			m_events.erase(it);
			break;
		}
		++ it;
	}
	event->setSceneIn(m_window);
	m_events.push_back(event);
}

void PEKeyboardManager::removeKeyboardEvent(int keyId)
{
	std::vector<PEKeyboardEvent *>::iterator it = m_events.begin();
	while(it != m_events.end()){
		if((*it)->getKeyId() == keyId){
			delete (*it);
			m_events.erase(it);
			break;
		}
		++ it;
	}
}

void PEKeyboardManager::checkAllEvents()
{
	std::vector<PEKeyboardEvent *>::iterator it = m_events.begin();
	while(it != m_events.end()){
		(*it)->check();
		++ it;
	}
}

void PEKeyboardManager::setEventView(GLFWwindow *window)
{
	m_window = window;
	std::vector<PEKeyboardEvent *>::iterator it = m_events.begin();
	while(it != m_events.end()){
		(*it)->setSceneIn(m_window);
		++ it;
	}

}
