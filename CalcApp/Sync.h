#pragma once

#include <qsemaphore.h>

class Sync
{
private:
	static Sync* instance;
	Sync();
	~Sync();

public:
	static Sync* get();
	QSemaphore console_sem;
};

