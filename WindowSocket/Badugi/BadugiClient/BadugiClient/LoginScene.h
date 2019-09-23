#pragma once
#include "Scene.h"



class LoginScene
	: public Scene
{
	char * Id;
	char * Pw;


	LoginScene();
public:
	LoginScene(HWND hWnd,SOCKET sock);
	virtual ~LoginScene();
	void SetId(char * Id);
	void SetPw(char * Pw);

	void SendLogin();

	virtual void Draw(HDC hdc);
};