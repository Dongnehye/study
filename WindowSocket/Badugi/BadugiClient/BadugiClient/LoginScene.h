#pragma once
#include "Scene.h"
#include "Button.h"

#define ID_EDIT 1
#define PW_EDIT 2

class LoginScene
	: public Scene
{
	char * Id;
	char * Pw;

	char Idstr[20];
	char Pwstr[20];

	HWND IdEdit;
	HWND PwEdit;

	POINT IdEditPos{ 465 , 520 };
	POINT PwEditPos{ 465 ,597 };
	SIZE IdEditSize{ 301,60 };
	SIZE PWEditSize{ 301,60 };

	Button * LoginButton;

	LoginScene();
public:
	LoginScene(HWND hWnd,SOCKET sock);
	virtual ~LoginScene();
	void SetId(char * Id);
	void SetPw(char * Pw);

	void SendLogin();

	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void MouseLClick(LPARAM lParam);
	virtual void SceneStart(HWND hWnd);
	virtual void SceneEnd(HWND hWnd);

};