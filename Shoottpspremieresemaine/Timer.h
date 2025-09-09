#pragma once

class Timer
{

	public:
		Timer();
		int GetDataTime();
		float GetDeltaTime();
		float GetTotalTime();
		void SetDataTime(int newTime);
		void SetDeltaTime(float newTime);
		void SetTotalTime(float newTime);
		void Update();


	private:
		int m_DataTime;
		float m_DeltaTime;
		float m_TotalTime;
};