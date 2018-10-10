#pragma once
#include <string>
#include <fstream>
#ifdef WIN32
#include <time.h>
#include <windows.h>
#else
#include <sys/time.h>
#endif
/**
 * @file mytimer.hpp
 * @brief: the simple timer
 * @author Mr.Z
 * @version 1.0.0.0
 * @date 2018-09-22
 */

/*============< [Note] class: MyTimer >============*/
class MyTimer
{
public:
	MyTimer(){};
	virtual ~MyTimer(){};

public:
	void start()
	{
#ifdef WIN32
		m_time_start = get_time_win();
#else
		m_time_start = get_time_linux();
#endif
		m_time_last = m_time_start;
	};
	double get_esp(bool cont_flag = false)
	{
#ifdef WIN32
		double time = get_time_win();
#else
		double time = get_time_linux();
#endif
		double esp   =0 ;
		if (!cont_flag) 
		{
			esp =  time - m_time_last;
		}
		else 
		{
			esp = time - m_time_start;
		}
		m_time_last = time;
		return esp;
	};
	void log(std::string path, std::string info, double esp)
	{
		std::ofstream ofs(path,std::ios::app);
		if (!ofs.is_open()) 
		{
			return ;
		}
		time_t now  = time(0);
        struct tm tm_now;
#ifdef WIN32
		localtime_s(&tm_now, &now);
#else
		localtime_r(&now,&tm_now);
#endif
        
		char time[200]={0};
        sprintf_s(time,"[%04d-%02d-%02d %02d:%02d:%02d]>>>>", tm_now.tm_year+1900, tm_now.tm_mon+1, tm_now.tm_mday, tm_now.tm_hour, tm_now.tm_min, tm_now.tm_sec) ;
		ofs<<time << info<< ": "<<esp<<std::endl;
		ofs.close();
	};
private:

#ifdef WIN32
	double get_time_win()
	{
		LARGE_INTEGER num;
		long long time_start = 0;
		long long freq = 0;
		QueryPerformanceFrequency(&num);
		freq = num.QuadPart;
		QueryPerformanceCounter(&num);
		time_start = num.QuadPart;
		return time_start*1000.0/freq;
	}
#else
	double get_time_linux()
	{
		struct timeval time;
		gettimeofday(&time, NULL );
		return 1000.0*time.tv_sec + time.tv_usec*1.0/1000;
	}
#endif
	double m_time_start;
	double m_time_last;
};
