#include "Potal.h"

using namespace std;

Potal::Potal()
{
	bBlock = false;
}

Potal::~Potal()
{
}

void Potal::Init(int _sceneNumber)
{
	sceneNumber = _sceneNumber;
}

void Potal::Jump()
{
	GameManager * gm;
	gm->GetInstance()->JumpScene(sceneNumber);
}

void Potal::reaction()
{
	Jump();
}

void Potal::printActor()
{
	cout << "¢ç";
}
