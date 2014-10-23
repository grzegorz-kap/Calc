#include "Sync.h"

Sync* Sync::instance = nullptr;

Sync::Sync()
	:console_sem(1)
{
}


Sync::~Sync()
{
}

Sync* Sync::get()
{
	if (instance == nullptr)
		instance = new Sync();
	return instance;
}
