#ifndef JF_PERFORMANCE_TIMER_H
#define JF_PERFORMANCE_TIMER_H

#define __linux__ //Change to platform we are running on

#ifdef __WIN32__
#include <windows.h>
typedef struct {
    LARGE_INTEGER start;
    LARGE_INTEGER stop;
} stopWatch;
#endif

#ifdef __linux__
#include <sys/time.h>
#endif

/*
 * =====================================================================================
 *        Class: jfPerformanceTimer
 *  Description: Cross-platform, microsecond accurate timer
 * =====================================================================================
 */
class jfPerformanceTimer
{
    public:

        jfPerformanceTimer();

        virtual ~jfPerformanceTimer();

        void start();

        void stop();

        double getElapsedTime();

        double getCurrentTime();

    protected:
#ifdef __WIN32__
		stopWatch timer;
        LARGE_INTEGER frequency;
#endif
#ifdef __linux__
		timeval startTime, endTime;
#endif
    private:
};

#endif 
