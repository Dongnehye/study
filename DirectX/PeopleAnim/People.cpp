#include "People.h"



void People::SetupJoints()
{
	D3DXVECTOR3 Vector{0,0,0};
	D3DXVECTOR3 Scale{0.5f,0.5f,0.5f};
	Joints * Body = new Joints(nullptr, Vector, Scale);
	VecJoints.push_back(Body);

	Vector = { 0,1.f,0 };
	Scale = { 1.f,0.5f,1.f };
	Joints * Chest = new Joints(Body, Vector, Scale);
	VecJoints.push_back(Chest);		 
									 
	Vector = { 0,1.f,0 };			 
	Scale = { 0.5f,0.5f,0.5f };		 
	Joints * Head = new Joints(Chest, Vector, Scale);
	VecJoints.push_back(Head);		 
									 
	Vector = { -1,-1.f,0 };			 
	Scale = { 0.2f,1.f,0.5f };
	Joints * LArm = new Joints(Chest, Vector, Scale);
	VecJoints.push_back(LArm);		 
									 
	Vector = { 1,-1.f,0 };			 
	Scale = { 0.2f,1.f,0.5f };
	Joints * RArm = new Joints(Chest, Vector, Scale);
	VecJoints.push_back(RArm);		 
									 
	Vector = { 0,-1.f,0 };			 
	Scale = { 0.2f,1.f,0.5f };
	Joints * LHand = new Joints(LArm, Vector, Scale);
	VecJoints.push_back(LHand);		 
									 
	Vector = { 0,-1.f,0 };			 
	Scale = { 0.2f,1.f,0.5f };
	Joints * RHand = new Joints(RArm, Vector, Scale);
	VecJoints.push_back(RHand);		 
									 
	Vector = { 0,-1.f,0 };			 
	Scale = { 0.7f,0.5f,0.5f };
	Joints * Heap = new Joints(Body, Vector, Scale);
	VecJoints.push_back(Heap);		 
									 
	Vector = { -0.5f,-1.f,0 };		 
	Scale = { 0.2f,1.f,0.5f };
	Joints * LLeg = new Joints(Heap, Vector, Scale);
	VecJoints.push_back(LLeg);		 
									 
	Vector = { 0.5f,-1.f,0 };		 
	Scale = { 0.2f,1.f,0.5f };
	Joints * RLeg = new Joints(Heap, Vector, Scale);
	VecJoints.push_back(RLeg);		 
									 
	Vector = { 0,-1.f,0 };			 
	Scale = { 0.2f,1.f,0.5f };
	Joints * LFoot = new Joints(LLeg, Vector, Scale);
	VecJoints.push_back(LFoot);		 
									 
	Vector = { 0,-1.f,0 };			 
	Scale = { 0.2f,1.f,0.5f };
	Joints * RFoot = new Joints(RLeg, Vector, Scale);
	VecJoints.push_back(RFoot);

	VecJoints[BODY]->SetRotateY(75.f);
}

People::People()
{
	SetupJoints();
	Attack();
}

People::~People()
{
	for (auto iter = VecJoints.begin(); iter != VecJoints.end(); ++iter)
	{
		delete (*iter);
	}
}

void People::Move(float Time)
{
	//D3DXVECTOR3 v;
	//D3DXVec3Lerp(&v, &aniPos[0], &aniPos[1], Time);
	//D3DXMatrixTranslation(&matTMParent, 0, 0, 0);
}

void People::Animate(float Time)
{
	for (auto iter = VecJoints.begin(); iter != VecJoints.end(); ++iter)
	{
		(*iter)->Animate(Time);
	}
}

void People::InitAnimation()
{
	for (auto iter = VecJoints.begin(); iter != VecJoints.end(); ++iter)
	{
		(*iter)->InitAnimation();
	}
}

void People::Attack()
{
	//VecJoints[Body]->YawPitchRoll(90.0f,0, 0);
	VecJoints[LARM]->YawPitchRoll(0,90.0f,0);
	VecJoints[RARM]->YawPitchRoll(0,90.0f,0);
}