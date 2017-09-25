#include "JoshFaraday.h"

bool JoshFaraday::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void JoshFaraday::Update()
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	//  m_iNotDrunk += 1;

	m_pStateMachine->Update();
}

bool JoshFaraday::NotDrunk()const
{
	if (m_iNotDrunk <= NotDrunkLevel) { return true; }

	return false;
}