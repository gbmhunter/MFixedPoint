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

// User includes
#include "MFixedPoint/FpF.hpp"
#include "MFixedPoint/FpS.hpp"

using namespace mn::MFixedPoint;

#define NUM_TESTS	100000

#define ADDITION_AVG 0.010
#define SUBTRACTION_AVG 0.010
#define EXPECTED_TIME_PER_FLOAT_OR_DOUBLE_OPERATION_ms 0.002 // 2us

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
		"Time Per Single Test (us):\t %f (%.0f%% higher than expected)\n",
		elapsed_millis,
		user_millis,
		system_millis,
		testCount,
		timePerSingleTestUs,
		percGreaterThanAvg);
}

#define min_float 0x00000000
#define max_float 0xffffffff

    #define exponent(x) (x << 1) >> 24
    #define mantissa(x) (x << 9) >> 9
    #define sign(x) x >> 31

uint32_t add(uint32_t x, uint32_t y) {
    uint32_t result_mantissa;
    uint32_t result_exponent;
    uint32_t result_sign;

    uint32_t different_sign = sign(x) ^ sign(y); //boolean but lets not do any type casting

    // catch NaN
    if (!(exponent(x) ^ 0xFF) && mantissa(x)) return x;
    if (!(exponent(y) ^ 0xFF) && mantissa(y)) return y;

    // catch Inf
    if (!(exponent(x) ^ 0xFF) && !(exponent(y) ^ 0xFF)) {
        // both are inf
        if (different_sign)
            // Inf - Inf
            return 0x7F800000 + 1; // NaN
        else
            // both Inf or -Inf
            return x;
    }
    else if (!(exponent(x) ^ 0xFF)) return x;
    else if (!(exponent(y) ^ 0xFF)) return y;

    // both numbers are non-special
    uint32_t exp_difference;
    if (different_sign) {
        exp_difference = exponent(y) + exponent(x);
    }
    else {
        // no need to account for constant BO
        // beware of underflow
        if (exponent(x) > exponent(y)) exp_difference = exponent(x) - exponent(y);
        else exp_difference = exponent(y) - exponent(x);
    }


    bool x_bigger_abs;
    if      (exponent(x) > exponent(y)) x_bigger_abs = true;
    else if (exponent(x) < exponent(y)) x_bigger_abs = false;
    else if (mantissa(x) > mantissa(y)) x_bigger_abs = true;
    else                                x_bigger_abs = false;

    if (!different_sign) {
        //both numbers have same sign (this is a sum)
        result_sign = sign(x);

        if (x_bigger_abs) {
            result_mantissa = (mantissa(x) << 1) + (mantissa(y) << 1) >> exp_difference;
            result_exponent = exponent(x);
        }
        else {
            result_mantissa = (mantissa(y) << 1) + ((mantissa(x) << 1) >> exp_difference);
            result_exponent = exponent(y);
        }
        if (result_mantissa << 31) result_mantissa = (result_mantissa >> 1) + 1;
        else result_mantissa = (result_mantissa >> 1);
    }
    else {
        // this actually is a subtraction

        if (x_bigger_abs) {
            result_sign = sign(x);
            result_exponent = exponent(x);

            // subtract and round to 23 bit 
            // this means making room in our 32bit representation
            result_mantissa = (mantissa(x) << 1) - ((mantissa(y) << 1) >> exp_difference );
        }
        else {
            result_sign = sign(y);
            result_exponent = exponent(y);

            // subtract and round to 23 bit 
            // this means making room in our 32bit representation
            result_mantissa = (mantissa(y) << 1) - ((mantissa(x) << 1) >> exp_difference);
        }

        if (result_mantissa << 31)  result_mantissa = ((result_mantissa >> 1) + 1);
        else result_mantissa = (result_mantissa >> 1);

        // normalize mantissa
        uint32_t temp = result_mantissa << 9;
        for (uint32_t count = 0; count < 23; ++count) {
            if (!((temp << count) >> 31)) {
                result_mantissa <<= ++count; // leading 1, so shift 1 more time
                result_exponent -= count;
                break;
            }
        }
    }
    uint32_t result = result_sign << 31 | result_exponent << 23 | result_mantissa;
    return result;
}

int main() {

	// // Make sure our custom float addition works
	// float testFloat1 = 1.0f;
	// float testFloat2 = 2.0f;
	// uint32_t rawResult = add(reinterpret_cast<uint32_t&>(testFloat1), reinterpret_cast<uint32_t&>(testFloat2));
	// float result = reinterpret_cast<float&>(rawResult);
	// if(result != 4.32 + 7.89) {
	// 	std::cout << "result = " << result;
	// 	throw std::runtime_error("add() did not work.");
	// }


	FpF<int32_t, 8> fp1(5.6);
	FpF<int32_t, 8> fp2(8.9);
	FpF<int32_t, 8> fp3;
	
	FpF<int64_t, 8> fp64f1(5.6);
	FpF<int64_t, 8> fp64f2(8.9);
	FpF<int64_t, 8> fp64f3;
	
	FpS<int64_t> fp64s1(5.6, 12);
	FpS<int64_t> fp64s2(8.9, 12);
	FpS<int64_t> fp64s3(0.0, 12);

	float float1 = 5.6;
	float float2 = 8.9;
	float float3 = 0.0; 

	double double1 = 5.6;
	double double2 = 8.9;
	double double3 = 0.0;

	time_measure * tu = StartTimeMeasuring();
	
	{	
		int x = 0;
		for(x = 0; x < NUM_TESTS; x++)
		{
			fp3 = fp1 + fp2;
		}
	
	}
	
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"FpF<int32_t> Addition", NUM_TESTS, ADDITION_AVG);
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
	PrintMetrics(tu, (char*)"FpF<int32_t> Subtraction", NUM_TESTS, SUBTRACTION_AVG);
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
	PrintMetrics(tu, (char*)"FpF<int64_t> Subtraction", NUM_TESTS, SUBTRACTION_AVG);
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
	PrintMetrics(tu, (char*)"FpS<int64_t> Addition", NUM_TESTS, SUBTRACTION_AVG);
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
	PrintMetrics(tu, (char*)"FpS<int64_t> Subtraction", NUM_TESTS, SUBTRACTION_AVG);
	free(tu);

	tu = StartTimeMeasuring();	
	{	
		int x = 0;
		for(x = 0; x < NUM_TESTS; x++) {
			// uint32_t rawFloat = add(*(uint32_t*)&float1, *(uint32_t*)&float2);
			float3 = float1 + float2;
		}
	}	
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"Float Addition", NUM_TESTS, EXPECTED_TIME_PER_FLOAT_OR_DOUBLE_OPERATION_ms);
	free(tu);

	tu = StartTimeMeasuring();	
	{	
		int x = 0;
		for(x = 0; x < NUM_TESTS; x++) {
			double3 = double1 + double2;
		}
	}	
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"Double Addition", NUM_TESTS, EXPECTED_TIME_PER_FLOAT_OR_DOUBLE_OPERATION_ms);
	free(tu);

	tu = StartTimeMeasuring();	
	{	
		int x = 0;
		for(x = 0; x < NUM_TESTS; x++) {
			double3 = double1 * double2;
		}
	}	
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"Double Multiplication", NUM_TESTS, EXPECTED_TIME_PER_FLOAT_OR_DOUBLE_OPERATION_ms);
	free(tu);
}
