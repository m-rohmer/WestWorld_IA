#include "Barman.h"

bool Barman::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Barman::Update()
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}