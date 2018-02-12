///
/// \file 				main.cpp
/// \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
/// \edited 			n/a
/// \reated			2013-05-30
/// \last-modified		2018-01-08
/// \brief 				Has the entry point for the benchmark program.
/// \details
///		See README.rst in root dir for more info.

// System includes
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>
#include <iostream>

// 3rd party includes
#include "MFixedPoint/FpF.hpp"
#include "MFixedPoint/FpS.hpp"

// User includes
#include "SoftFloat.hpp"

using namespace mn::MFixedPoint;

#define NUM_TESTS	100000

#define ADDITION_AVG 0.010
#define SUBTRACTION_AVG 0.010
#define EXPECTED_TIME_PER_FLOAT_OR_DOUBLE_OPERATION_ms 0.002 // 2us
class Constants {
public:
	static constexpr double expectedTimeFp32SMultiply_us = 0.014;
	static constexpr double expectedTimeSoftwareFloatAdd_us = 0.017;
	static constexpr double expectedTimeSoftwareFloatMultiply_us = 0.028;
};

typedef struct tag_time_measure {
  struct timeval startTimeVal;
  struct timeval stopTimeVal;

  struct rusage startTimeUsage;
  struct rusage stopTimeUsage;
} time_measure;

time_measure* StartTimeMeasuring() {
  time_measure* tu = (time_measure*)malloc(sizeof(time_measure));
  if(!tu)
    exit(1);

  getrusage(RUSAGE_SELF, &tu->startTimeUsage);
  gettimeofday(&tu->startTimeVal,0);

  return tu;
}

void StopTimeMeasuring(time_measure * tu) {
  getrusage(RUSAGE_SELF, &tu->stopTimeUsage);
  gettimeofday(&tu->stopTimeVal,0);
}

void PrintMeasuredTime(time_measure * tu) {
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

void PrintMetrics(time_measure * tu, char* testName, uint32_t testCount, double avg) {
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
	double percGreaterThanAvg = ((timePerSingleTestUs-avg)/avg)*100.0;

	printf("\n\n---%s--- \n", testName);
	printf(
		"Total (ms):\t\t\t %f\n"
		"User (ms):\t\t\t %f\n"
		"System (ms):\t\t\t %f\n"
		"Num. Tests:\t\t\t %u\n"
		"Time Per Single Test (ns):\t %f (%.0f%% higher than expected)\n",
		elapsed_millis,
		user_millis,
		system_millis,
		testCount,
		timePerSingleTestUs*1000.0,
		percGreaterThanAvg);
}




int main() {

	// Make sure our custom float addition works
	float testFloat1 = 4.32f;
	float testFloat2 = 7.89f;

	SoftFloat softFloat;
	f32 rawResult = softFloat.Multiply(reinterpret_cast<uint32_t&>(testFloat1), reinterpret_cast<uint32_t&>(testFloat2));
	float result = reinterpret_cast<float&>(rawResult);
	if(result > 4.32 * 7.89 + 0.1 || result < 4.32 * 7.89 - 0.1) {
		std::cout << "result = " << result;
		throw std::runtime_error("add() did not work.");
	}


	FpF32<8> fpF32_1(5.6);
	FpF32<8> fpF32_2(8.9);
	FpF32<8> fpF32_3;

	FpS32 fpS32_1(5.6, 8);
	FpS32 fpS32_2(8.9, 8);
	FpS32 fpS32_3(8.9, 8);
	
	FpF64<8> fpF64_1(5.6);
	FpF64<8> fpF64_2(8.9);
	FpF64<8> fpF64_3;
	
	FpS64 fpS64_1(5.6, 12);
	FpS64 fpS64_2(8.9, 12);
	FpS64 fpS64_3(0.0, 12);

	float float1 = 5.6;
	float float2 = 8.9;
	float float3 = 0.0; 

	double double1 = 5.6;
	double double2 = 8.9;
	double double3 = 0.0;

    time_measure * tu;

	//===============================================================================================//
	//====================================== ADDITION BENCHMARKING ==================================//
	//===============================================================================================//

    //===== FpF32 ADDITION =====//
	tu = StartTimeMeasuring();
	{	
		int x = 0;
		for(x = 0; x < NUM_TESTS; x++)
		{
			fpF32_3 = fpF32_1 + fpF32_2;
		}
	
	}
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpF32 Addition", NUM_TESTS, SUBTRACTION_AVG);
    free(tu);

    //===== FpF64 ADDITION =====//
    tu = StartTimeMeasuring();
    {
        int x = 0;
        for(x = 0; x < NUM_TESTS; x++)
        {
            fpF64_3 = fpF64_1 + fpF64_2;
        }

    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpF64 Addition", NUM_TESTS, SUBTRACTION_AVG);
    free(tu);

    //===== FpS32 ADDITION =====//
    tu = StartTimeMeasuring();
    {
        int x = 0;
        for(x = 0; x < NUM_TESTS; x++)
        {
            fpS32_3 = fpS32_1 + fpS32_2;
        }

    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpS32 Addition", NUM_TESTS, SUBTRACTION_AVG);
    free(tu);

    //===== FpS64 ADDITION =====//
    tu = StartTimeMeasuring();
    {
        int x = 0;
        for(x = 0; x < NUM_TESTS; x++)
        {
            fpS64_3 = fpS64_1 + fpS64_2;
        }

    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpS64 Addition", NUM_TESTS, SUBTRACTION_AVG);
    free(tu);

    tu = StartTimeMeasuring();
    {
        int x = 0;
        for(x = 0; x < NUM_TESTS; x++) {
            SoftFloat softFloat;
            uint32_t rawFloat = softFloat.Add(*(uint32_t*)&float1, *(uint32_t*)&float2);
            float3 = *(float*)&rawFloat;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"Software Float Addition", NUM_TESTS, Constants::expectedTimeSoftwareFloatAdd_us);
    free(tu);

    tu = StartTimeMeasuring();
    {
        int x = 0;
        for(x = 0; x < NUM_TESTS; x++) {
            float3 = float1 + float2;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"Hardware Float Addition", NUM_TESTS, EXPECTED_TIME_PER_FLOAT_OR_DOUBLE_OPERATION_ms);
    free(tu);

    //===============================================================================================//
    //==================================== SUBTRACTION BENCHMARKING =================================//
    //===============================================================================================//

    //===== FpF32 SUBTRACTION =====//
	tu = StartTimeMeasuring();
	{	
		int x = 0;
		for(x = 0; x < NUM_TESTS; x++)
		{
			fpF32_3 = fpF32_1 - fpF32_2;
		}
	
	}
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"FpF32 Subtraction", NUM_TESTS, SUBTRACTION_AVG);
	//PrintMeasuredTime(tu);
	free(tu);

    //===== FpF64 SUBTRACTION =====//
	tu = StartTimeMeasuring();
	{	
		int x = 0;
		for(x = 0; x < NUM_TESTS; x++)
		{
			fpF64_3 = fpF64_1 - fpF64_2;
		}
	
	}
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"FpF64 Subtraction", NUM_TESTS, SUBTRACTION_AVG);
	free(tu);

    //===== FpS32 SUBTRACTION =====//
    tu = StartTimeMeasuring();
    {
        int x = 0;
        for(x = 0; x < NUM_TESTS; x++)
        {
            fpS32_3 = fpS32_1 - fpS32_2;
        }

    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpS32 Subtraction", NUM_TESTS, SUBTRACTION_AVG);
    free(tu);

    //===== FpS64 SUBTRACTION =====//
    tu = StartTimeMeasuring();
    {
        int x = 0;
        for(x = 0; x < NUM_TESTS; x++)
        {
            fpS64_3 = fpS64_1 - fpS64_2;
        }

    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpS64 Subtraction", NUM_TESTS, SUBTRACTION_AVG);
    free(tu);

    //===============================================================================================//
    //================================== MULTIPLICATION BENCHMARKING ================================//
    //===============================================================================================//

    //===== FpF32 MULTIPLICATION =====//
    tu = StartTimeMeasuring();
    {
        int x = 0;
        for(x = 0; x < NUM_TESTS; x++)
        {
            fpF32_3 = fpF32_1*fpF32_2;
        }

    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpF32 Multiplication", NUM_TESTS, Constants::expectedTimeFp32SMultiply_us);
    free(tu);

    //===== FpF64 MULTIPLICATION =====//
    tu = StartTimeMeasuring();
    {
        int x = 0;
        for(x = 0; x < NUM_TESTS; x++)
        {
            fpF64_3 = fpF64_1*fpF64_2;
        }

    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpF64 Multiplication", NUM_TESTS, Constants::expectedTimeFp32SMultiply_us);
    free(tu);

    //===== FpS32 MULTIPLICATION =====//
	tu = StartTimeMeasuring();
	{	
		int x = 0;
		for(x = 0; x < NUM_TESTS; x++)
		{
			fpS32_3 = fpS32_1*fpS32_2;
		}
	
	}
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"FpS32 Multiplication", NUM_TESTS, Constants::expectedTimeFp32SMultiply_us);
	free(tu);

    //===== FpS64 MULTIPLICATION =====//
    tu = StartTimeMeasuring();
    {
        int x = 0;
        for(x = 0; x < NUM_TESTS; x++)
        {
            fpS64_3 = fpS64_1*fpS64_2;
        }

    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpS64 Multiplication", NUM_TESTS, Constants::expectedTimeFp32SMultiply_us);
    free(tu);

    //===== SOFTWARE FLOAT MULTIPLICATION =====//
    tu = StartTimeMeasuring();
    {
        int x = 0;
        for(x = 0; x < NUM_TESTS; x++) {
            SoftFloat softFloat;
            uint32_t rawFloat = softFloat.Multiply(reinterpret_cast<uint32_t&>(float1), reinterpret_cast<uint32_t&>(float2));
            float3 = *(float*)&rawFloat;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"Software Float Multiplication", NUM_TESTS, Constants::expectedTimeSoftwareFloatMultiply_us);
    free(tu);

    //===== HARDWARE FLOAT MULTIPLICATION =====//
	tu = StartTimeMeasuring();	
	{	
		int x = 0;
		for(x = 0; x < NUM_TESTS; x++) {
			float3 = float1 * float2;
		}
	}	
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"Hardware Float Multiplication", NUM_TESTS, EXPECTED_TIME_PER_FLOAT_OR_DOUBLE_OPERATION_ms);
	free(tu);

    //===============================================================================================//
    //======================================= DIVISION BENCHMARKING =================================//
    //===============================================================================================//

    //===== FpF32 DIVISION =====//
    tu = StartTimeMeasuring();
    {
        int x = 0;
        for(x = 0; x < NUM_TESTS; x++)
        {
            fpF32_3 = fpF32_1/fpF32_2;
        }

    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpF32 Division", NUM_TESTS, Constants::expectedTimeFp32SMultiply_us);
    free(tu);

    //===== FpF64 DIVISION =====//
    tu = StartTimeMeasuring();
    {
        int x = 0;
        for(x = 0; x < NUM_TESTS; x++)
        {
            fpF64_3 = fpF64_1/fpF64_2;
        }

    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpF64 Division", NUM_TESTS, Constants::expectedTimeFp32SMultiply_us);
    free(tu);

    //===== FpS32 DIVISION =====//
    tu = StartTimeMeasuring();
    {
        int x = 0;
        for(x = 0; x < NUM_TESTS; x++)
        {
            fpS32_3 = fpS32_1*fpS32_2;
        }

    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpS32 Division", NUM_TESTS, Constants::expectedTimeFp32SMultiply_us);
    free(tu);

    //===== FpS64 DIVISION =====//
    tu = StartTimeMeasuring();
    {
        int x = 0;
        for(x = 0; x < NUM_TESTS; x++)
        {
            fpS64_3 = fpS64_1/fpS64_2;
        }

    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpS64 Division", NUM_TESTS, Constants::expectedTimeFp32SMultiply_us);
    free(tu);

    //===== HARDWARE FLOAT DIVISION =====//
    tu = StartTimeMeasuring();
    {
        int x = 0;
        for(x = 0; x < NUM_TESTS; x++) {
            float3 = float1 / float2;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"Hardware Float Division", NUM_TESTS, EXPECTED_TIME_PER_FLOAT_OR_DOUBLE_OPERATION_ms);
    free(tu);
}
