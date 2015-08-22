/* CPxtoneDecoder.h -- Wrapper class for interfacing pxtone.dll
 * Copyright (c) 2008, Autch.  Distributed under the terms of zlib/libpng license.
 */

#pragma once

class CPxtoneDecoder
{
private:
	SOUNDINFO m_SoundInfo;

	struct
	{
		int beats;
		int ticks;
		int measures;
		float bpm;

		long loops;
		long meas_intro;
		long meas_loop;
	} m_LoopInfo;

	DWORD MeasToMSecs(long measures)
	{
		return (DWORD)(measures * m_LoopInfo.beats / m_LoopInfo.bpm * 60000.0);
	}

public:
	CPxtoneDecoder()
	{
		m_SoundInfo.dwBitsPerSample = 16;
		m_SoundInfo.dwChannels = 2;
		m_SoundInfo.dwReserved2 = FALSE;
		m_SoundInfo.dwSamplesPerSec = 44100;
		m_SoundInfo.dwSeekable = TRUE;
		m_SoundInfo.dwUnitRender = 44100 * 2 * 2 / 2;
		ZeroMemory(&m_LoopInfo, sizeof m_LoopInfo);
	}

	~CPxtoneDecoder()
	{
		Close();
	}

	void Close()
	{
		pxtone_Tune_Release();
	}

	BOOL Open(LPSTR szFileName, SOUNDINFO* pInfo)
	{
		BOOL r;

		r = pxtone_Tune_Load(NULL, NULL, szFileName);
		if (!r)
		{
			Close();
			return FALSE;
		}

		pxtone_Tune_GetInformation(&m_LoopInfo.beats, &m_LoopInfo.bpm, &m_LoopInfo.ticks, &m_LoopInfo.measures);
		m_LoopInfo.loops = GetMyProfileInt("kpipxtone", "loop", 2);
		if (m_LoopInfo.loops == 0)
		{
			m_SoundInfo.dwLength = MeasToMSecs(m_LoopInfo.measures);
			m_SoundInfo.dwReserved1 = FALSE;
			//pxtone_Tune_SetLoop(false);
		}
		else
		{
			m_LoopInfo.meas_intro = pxtone_Tune_GetRepeatMeas();
			m_LoopInfo.meas_loop = pxtone_Tune_GetPlayMeas();
			m_SoundInfo.dwLength = MeasToMSecs(m_LoopInfo.meas_intro
				+ (m_LoopInfo.meas_loop - m_LoopInfo.meas_intro) * m_LoopInfo.loops);
			m_SoundInfo.dwReserved1 = TRUE;
			//pxtone_Tune_SetLoop(true);
		}

		*pInfo = m_SoundInfo;
		return pxtone_Tune_Start(0, 0, 1.0f);
	}

	DWORD SetPosition(DWORD dwPos)
	{
		DWORD dwSamples;

		if(pxtone_Tune_IsStreaming())
			pxtone_Tune_Stop();

		if (m_LoopInfo.loops == 0 || dwPos < MeasToMSecs(m_LoopInfo.meas_loop))
		{
			dwSamples = dwPos * 44100 / 1000;
		}
		else
		{
			DWORD dwCorrectPos = dwPos;
			dwCorrectPos -= MeasToMSecs(m_LoopInfo.meas_intro);
			dwCorrectPos %= MeasToMSecs(m_LoopInfo.meas_loop - m_LoopInfo.meas_intro);
			dwCorrectPos += MeasToMSecs(m_LoopInfo.meas_intro);
			dwSamples = dwCorrectPos * 44100 / 1000;
		}
		pxtone_Tune_Start(dwSamples, 0, 1.0f);
		return dwPos;
	}

	DWORD Render(BYTE* pBuffer, DWORD dwSize)
	{
		BOOL r;

		r = pxtone_Tune_Vomit(pBuffer, dwSize / 4);
		return r ? dwSize : 0;
	}
};
