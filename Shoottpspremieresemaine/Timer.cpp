#include "framework.h"
#include "Timer.h"


Timer::Timer()
{

}

int Timer::GetDataTime()
{
	return m_DataTime;
}

float Timer::GetDeltaTime()
{
	return m_DeltaTime;
}

float Timer::GetTotalTime()
{
	return m_TotalTime;
}

void Timer::SetDataTime(int newTime)
{
	m_DataTime = newTime;
}

void Timer::SetDeltaTime(float newTime)
{
	m_DeltaTime = newTime;
}

void Timer::SetTotalTime(float newTime)
{
	m_TotalTime = newTime;
}


void Timer::Update()
{
	unsigned int newTime = timeGetTime();
	unsigned int deltaTime = newTime - GetDataTime();
	m_DataTime = newTime;

	SetDeltaTime(deltaTime / 1000.0f);
	SetTotalTime(GetTotalTime() + GetDeltaTime());


}

