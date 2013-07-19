//!
//! @file 		FpBench-Main.cpp
//! @author 	Geoffrey Hunter <gbmhunter@gmail.com> (www.cladlab.com)
//! @edited 	n/a
//! @date 		2013/05/30
//! @brief 		Has the entry point for the benchmark program.
//! @details
//!				See README.rst

#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>

// 32-bit fixed-point library
#include "../src/include/FixedPoint-Fp32.hpp"

using namespace Fp;

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

int main()
{
	Fp32<8> fp1 = Fp32<8>(5.6);
	Fp32<8> fp2 = Fp32<8>(8.9);
	Fp32<8> fp3;

	time_measure * tu = StartTimeMeasuring();
	
	{	
		int x = 0;
		for(x = 0; x < 10000000; x++)
		{
			fp3 = fp1 + fp2;
		}
	
	}
	
	StopTimeMeasuring(tu);
	PrintMeasuredTime(tu);
	free(tu);
}