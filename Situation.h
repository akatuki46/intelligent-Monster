//親ステート
#pragma once
class Situation
{
public:
	virtual void Action() {};

	virtual int GetStatus() { return 0; }
private:

};

