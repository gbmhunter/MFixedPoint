//!
//! @file 				main.cpp
//! @author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @edited 			n/a
//! @created			2013-05-30
//! @last-modified		2017-06-27
//! @brief 				Has the entry point for the benchmark program.
//! @details
//!		See README.rst in root dir for more info.

// System includes
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>

// User includes
#include "MFixedPoint/Fp32f.hpp"
#include "MFixedPoint/Fp64f.hpp"
#include "MFixedPoint/Fp64s.hpp"

using namespace mn::MFixedPoint;

#define NUM_TESTS	10000

#define ADDITION_AVG 0.010
#define SUBTRACTION_AVG 0.010

typedef struct tag_time_measure
{
  struct timeval startTimeVal;
  struct timeval stopTimeVal;

  struct rusage startTimeUsage;
  struct rusage stopTimeUsage;
} time_measure;

time_measure* StartTimeMeasuring()
{
  time_measure* tu = (time_measure*)malloc(sizeof(time_measure));
  if(!tu)
    exit(1);

  getrusage(RUSAGE_SELF, &tu->startTimeUsage);
  gettimeofday(&tu->startTimeVal,0);

  return tu;
}

void StopTimeMeasuring(time_measure * tu)
{
  getrusage(RUSAGE_SELF, &tu->stopTimeUsage);
  gettimeofday(&tu->stopTimeVal,0);
}

void PrintMeasuredTime(time_measure * tu)
{
	struct timeval elapsedVal;
	struct timeval userVal;
	struct timeval systemVal;

	double elapsed_millis = 0.0f;
	double user_millis = 0.0f;
	double system_millis = 0.0f;

	timersub(&tu->stopTimeVal, &tu->startTimeVal, &elapsedVal);
	timersub(&tu->stopTimeUsage.ru_utime, &tu->startTimeUsage.ru_utime, &userVal);
	timersub(&tu->stopTimeUsage.ru_stime, &tu->startTimeUsage.ru_stime, &systemVal);

	elapsed_millis = elapsedVal.tv_sec * 1000 + (double) elapsedVal.tv_usec / 1000;
	user_millis = userVal.tv_sec * 1000 + (double) userVal.tv_usec / 1000;
	system_millis = systemVal.tv_sec * 1000 + (double) systemVal.tv_usec / 1000;

	printf("\n\n---Execution times in milliseconds--- \n");
	printf("Total:\t\t %f\nUser:\t\t %f\nSystem:\t\t %f\n", elapsed_millis, user_millis, system_millis);
}

void PrintMetrics(time_measure * tu, char* testName, uint32_t testCount, double avg)
{
	struct timeval elapsedVal;
	struct timeval userVal;
	struct timeval systemVal;

	double elapsed_millis = 0.0f;
	double user_millis = 0.0f;
	double system_millis = 0.0f;

	timersub(&tu->stopTimeVal, &tu->startTimeVal, &elapsedVal);
	timersub(&tu->stopTimeUsage.ru_utime, &tu->startTimeUsage.ru_utime, &userVal);
	timersub(&tu->stopTimeUsage.ru_stime, &tu->startTimeUsage.ru_stime, &systemVal);

	elapsed_millis = elapsedVal.tv_sec * 1000 + (double) elapsedVal.tv_usec / 1000;
	user_millis = userVal.tv_sec * 1000 + (double) userVal.tv_usec / 1000;
	system_millis = systemVal.tv_sec * 1000 + (double) systemVal.tv_usec / 1000;
	double timePerSingleTestUs = (elapsed_millis*1000.)/((double)testCount);

	printf("\n\n---%s--- \n", testName);
	printf(
		"Total (ms):\t\t\t %f\n"
		"User (ms):\t\t\t %f\n"
		"System (ms):\t\t\t %f\n"
		"Num. Tests:\t\t\t %u\n"
		"Time Per Single Test (us):\t %f (%.0f%% higher than expected)\n",
		elapsed_millis,
		user_millis,
		system_millis,
		testCount,
		timePerSingleTestUs,
		(timePerSingleTestUs/avg)*100.0);
}

int main()
{
	Fp32f<8> fp1 = Fp32f<8>(5.6);
	Fp32f<8> fp2 = Fp32f<8>(8.9);
	Fp32f<8> fp3;
	
	Fp64f<8> fp64f1 = Fp64f<8>(5.6);
	Fp64f<8> fp64f2 = Fp64f<8>(8.9);
	Fp64f<8> fp64f3;
	
	Fp64s fp64s1 = Fp64s(5.6, 12);
	Fp64s fp64s2 = Fp64s(8.9, 12);
	Fp64s fp64s3;

	time_measure * tu = StartTimeMeasuring();
	
	{	
		int x = 0;
		for(x = 0; x < NUM_TESTS; x++)
		{
			fp3 = fp1 + fp2;
		}
	
	}
	
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"Fp32f Addition", NUM_TESTS, ADDITION_AVG);
	//PrintMeasuredTime(tu);
	free(tu);
	
	tu = StartTimeMeasuring();
	
	{	
		int x = 0;
		for(x = 0; x < NUM_TESTS; x++)
		{
			fp3 = fp1 - fp2;
		}
	
	}
	
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"Fp32f Subtraction", NUM_TESTS, SUBTRACTION_AVG);
	//PrintMeasuredTime(tu);
	free(tu);
	
	tu = StartTimeMeasuring();
	
	{	
		int x = 0;
		for(x = 0; x < NUM_TESTS; x++)
		{
			fp64f3 = fp64f1 - fp64f2;
		}
	
	}
	
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"Fp64f Subtraction", NUM_TESTS, SUBTRACTION_AVG);
	//PrintMeasuredTime(tu);
	free(tu);
	
	tu = StartTimeMeasuring();
	
	{	
		int x = 0;
		for(x = 0; x < NUM_TESTS; x++)
		{
			fp64s3 = fp64s1 + fp64s2;
		}
	
	}
	
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"Fp64s Addition", NUM_TESTS, SUBTRACTION_AVG);
	free(tu);
	
	tu = StartTimeMeasuring();
	
	{	
		int x = 0;
		for(x = 0; x < NUM_TESTS; x++)
		{
			fp64s3 = fp64s1 - fp64s2;
		}
	
	}
	
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"Fp64s Subtraction", NUM_TESTS, SUBTRACTION_AVG);
	free(tu);
}
