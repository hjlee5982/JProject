#include "pch.h"
#include "IExecute.h"

void IExecute::Loop()
{
	Update();
	LateUpdate();
	Render();
}
