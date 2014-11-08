#pragma once
class IdGenerator
{
public:

	static IdGenerator* Instance();
	unsigned GetID();

private:

	unsigned int ID;
	IdGenerator(void);
	~IdGenerator(void);


};

