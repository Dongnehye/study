#pragma once

class People
{
	int Floor;
	int wantFloor;
	int weight;

	int arrow;
public:
	People();
	~People();

	bool Init();
	bool Init(int _Floor, int _wantFloor);
	bool Init(int _Floor, int _wantFloor, int _weight);

	void SetArrow();

	int GetFloor() const;
	int GetWantFloor() const;
	int GetArrow() const;
	int GetWeight() const;
	void SetInit(int _floor, int wantfloor);
};