#pragma once
#include <vector>
class IScreen;
class ScreenManager
{
	std::vector<IScreen*> mScreens;
	unsigned short m_focused;
	unsigned short m_size;
	int getIndex(IScreen* screen);
public:
	ScreenManager();
	~ScreenManager();
	void Update();
	void Draw();
	void AddScreen(IScreen* screen);
	void RemoveScreen(IScreen* screen);
	void SetFocus(IScreen* screen);
	IScreen* GetFocusedscreen();
};

#include "IScreen.h"
inline int ScreenManager::getIndex(IScreen* screen)
{
	for (int i = 0; i < m_size; i++)
	if (mScreens[i] == screen)
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
		mScreens[i]->Update();
}

inline void ScreenManager::Draw()
{
	for (int i = 0; i < m_size; i++)
		mScreens[i]->Draw();
}

inline void ScreenManager::AddScreen(IScreen* screen)
{
	m_size++;
	mScreens.push_back(screen);
}

inline void ScreenManager::RemoveScreen(IScreen* screen)
{
	m_size--;
	mScreens.erase(mScreens.begin() + getIndex(screen));
}

inline void ScreenManager::SetFocus(IScreen* screen)
{
	m_focused = getIndex(screen);
}

inline IScreen* ScreenManager::GetFocusedscreen()
{
	return (m_size != 0) ? mScreens[m_focused] : nullptr;
}
