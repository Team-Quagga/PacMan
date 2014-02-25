#pragma once
#include <vector>
class IScreen;
class ScreenManager
{
	std::vector<IScreen*> m_scenes;
	unsigned short m_focused;
	unsigned short m_size;
	int getIndex(IScreen* scene);
public:
	ScreenManager();
	~ScreenManager();
	void Update();
	void Draw();
	void AddScene(IScreen* scene);
	void RemoveScene(IScreen* scene);
	void SetFocus(IScreen* scene);
	IScreen* GetFocusedScene();
};

#include "IScreen.h"
inline int ScreenManager::getIndex(IScreen* scene)
{
	for (int i = 0; i < m_size; i++)
	if (m_scenes[i] == scene)
		return i;
}
inline ScreenManager::ScreenManager()
{
	m_size = 0; m_focused = 0;
};

inline ScreenManager::~ScreenManager()
{
};

inline void ScreenManager::Update()
{
	for (int i = 0; i < m_size; i++)
		m_scenes[i]->Update();
}

inline void ScreenManager::Draw()
{
	for (int i = 0; i < m_size; i++)
		m_scenes[i]->Draw();
}

inline void ScreenManager::AddScene(IScreen* scene)
{
	m_size++;
	m_scenes.push_back(scene);
}

inline void ScreenManager::RemoveScene(IScreen* scene)
{
	m_scenes.erase(m_scenes.begin() + getIndex(scene));
}

inline void ScreenManager::SetFocus(IScreen* scene)
{
	m_focused = getIndex(scene);
}

inline IScreen* ScreenManager::GetFocusedScene()
{
	return (m_size != 0) ? m_scenes[m_focused] : nullptr;
}
