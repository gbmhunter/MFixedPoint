///
/// \file 				main.cpp
/// \author 			Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
/// \edited 			n/a
/// \reated			    2013-05-30
/// \last-modified		2018-02-12
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

static constexpr uint32_t numCyclesPerTest = 100000;

class ExpectedRunTimes {
public:

    static constexpr double fpF32Add_ns = 6.7;
    static constexpr double fpF64Add_ns = 8.2;
    static constexpr double fpS32Add_ns = 10.6;
    static constexpr double fpS64Add_ns = 14.2;
    static constexpr double softwareFloatAdd_ns = 17.0;
    static constexpr double hardwareFloatAdd_ns = 3.4;

    static constexpr double fpF32Sub_ns = 7.5;
    static constexpr double fpF64Sub_ns = 7.5;
    static constexpr double fpS32Sub_ns = 14.0;
    static constexpr double fpS64Sub_ns = 10.4;
    static constexpr double softwareFloatSub_ns = -1.0;
    static constexpr double hardwareFloatSub_ns = 2.6;

    static constexpr double fpF32Mul_ns = 10.3;
    static constexpr double fpF64Mul_ns = 10.1;
	static constexpr double fpS32Mul_ns = 12.2;
    static constexpr double fpS64Mul_ns = 10.4;
	static constexpr double softwareFloatMul_ns = 32.0;
    static constexpr double hardwareFloatMul_ns = 2.5;

    static constexpr double fpF32Div_ns = 19.0;
    static constexpr double fpF64Div_ns = 18.0;
    static constexpr double fpS32Div_ns = 10.8;
    static constexpr double fpS64Div_ns = 19.8;
    static constexpr double softwareFloatDiv_ns = -1.0;
    static constexpr double hardwareFloatDiv_ns = 5.1;
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

void PrintMetrics(time_measure * tu, char* testName, uint32_t testCount, double avgDurationPerTest_ns) {
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
	double timePerSingleTest_ns = (elapsed_millis*1000.)/((double)testCount)*1000.0;
	double percGreaterThanAvg = ((timePerSingleTest_ns-avgDurationPerTest_ns)/avgDurationPerTest_ns)*100.0;

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
		timePerSingleTest_ns,
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

    //===============================================================================================//
    //======================================== TEST VARIABLE INIT ===================================//
    //===============================================================================================//


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

    time_measure * tu;

	//===============================================================================================//
	//====================================== ADDITION BENCHMARKING ==================================//
	//===============================================================================================//

    //===== FpF32 ADDITION =====//
	tu = StartTimeMeasuring();
	{	
		uint32_t x = 0;
		for(x = 0; x < numCyclesPerTest; x++) {
			fpF32_3 = fpF32_1 + fpF32_2;
		}
	}
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpF32 Addition", numCyclesPerTest, ExpectedRunTimes::fpF32Add_ns);
    free(tu);

    //===== FpF64 ADDITION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++) {
            fpF64_3 = fpF64_1 + fpF64_2;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpF64 Addition", numCyclesPerTest, ExpectedRunTimes::fpF64Add_ns);
    free(tu);

    //===== FpS32 ADDITION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++) {
            fpS32_3 = fpS32_1 + fpS32_2;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpS32 Addition", numCyclesPerTest, ExpectedRunTimes::fpS32Add_ns);
    free(tu);

    //===== FpS64 ADDITION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++) {
            fpS64_3 = fpS64_1 + fpS64_2;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpS64 Addition", numCyclesPerTest, ExpectedRunTimes::fpS64Add_ns);
    free(tu);

    //===== SOFTWARE FLOAT ADDITION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++) {
            uint32_t rawFloat = softFloat.Add(*(uint32_t*)&float1, *(uint32_t*)&float2);
            float3 = *(float*)&rawFloat;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"Software Float Addition", numCyclesPerTest, ExpectedRunTimes::softwareFloatAdd_ns);
    free(tu);

    //===== HARDWARE FLOAT ADDITION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++) {
            float3 = float1 + float2;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"Hardware Float Addition", numCyclesPerTest, ExpectedRunTimes::hardwareFloatAdd_ns);
    free(tu);

    //===============================================================================================//
    //==================================== SUBTRACTION BENCHMARKING =================================//
    //===============================================================================================//

    //===== FpF32 SUBTRACTION =====//
	tu = StartTimeMeasuring();
	{	
		uint32_t x = 0;
		for(x = 0; x < numCyclesPerTest; x++) {
			fpF32_3 = fpF32_1 - fpF32_2;
		}
	}
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"FpF32 Subtraction", numCyclesPerTest, ExpectedRunTimes::fpF32Sub_ns);
	//PrintMeasuredTime(tu);
	free(tu);

    //===== FpF64 SUBTRACTION =====//
	tu = StartTimeMeasuring();
	{	
		uint32_t x = 0;
		for(x = 0; x < numCyclesPerTest; x++) {
			fpF64_3 = fpF64_1 - fpF64_2;
		}
	}
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"FpF64 Subtraction", numCyclesPerTest, ExpectedRunTimes::fpF64Sub_ns);
	free(tu);

    //===== FpS32 SUBTRACTION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++) {
            fpS32_3 = fpS32_1 - fpS32_2;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpS32 Subtraction", numCyclesPerTest, ExpectedRunTimes::fpS32Sub_ns);
    free(tu);

    //===== FpS64 SUBTRACTION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++) {
            fpS64_3 = fpS64_1 - fpS64_2;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpS64 Subtraction", numCyclesPerTest, ExpectedRunTimes::fpS64Sub_ns);
    free(tu);

    //===== HARDWARE FLOAT SUBTRACTION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++) {
            float3 = float1 - float2;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"Hardware Float Subtraction", numCyclesPerTest, ExpectedRunTimes::hardwareFloatSub_ns);
    free(tu);

    //===============================================================================================//
    //================================== MULTIPLICATION BENCHMARKING ================================//
    //===============================================================================================//

    //===== FpF32 MULTIPLICATION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++) {
            fpF32_3 = fpF32_1*fpF32_2;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpF32 Multiplication", numCyclesPerTest, ExpectedRunTimes::fpF32Mul_ns);
    free(tu);

    //===== FpF64 MULTIPLICATION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++) {
            fpF64_3 = fpF64_1*fpF64_2;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpF64 Multiplication", numCyclesPerTest, ExpectedRunTimes::fpF64Mul_ns);
    free(tu);

    //===== FpS32 MULTIPLICATION =====//
	tu = StartTimeMeasuring();
	{	
		uint32_t x = 0;
		for(x = 0; x < numCyclesPerTest; x++) {
			fpS32_3 = fpS32_1*fpS32_2;
		}
	}
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"FpS32 Multiplication", numCyclesPerTest, ExpectedRunTimes::fpS32Mul_ns);
	free(tu);

    //===== FpS64 MULTIPLICATION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++) {
            fpS64_3 = fpS64_1*fpS64_2;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpS64 Multiplication", numCyclesPerTest, ExpectedRunTimes::fpS64Mul_ns);
    free(tu);

    //===== SOFTWARE FLOAT MULTIPLICATION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++) {
            SoftFloat softFloat;
            uint32_t rawFloat = softFloat.Multiply(reinterpret_cast<uint32_t&>(float1), reinterpret_cast<uint32_t&>(float2));
            float3 = *(float*)&rawFloat;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"Software Float Multiplication", numCyclesPerTest, ExpectedRunTimes::softwareFloatMul_ns);
    free(tu);

    //===== HARDWARE FLOAT MULTIPLICATION =====//
	tu = StartTimeMeasuring();	
	{	
		uint32_t x = 0;
		for(x = 0; x < numCyclesPerTest; x++) {
			float3 = float1 * float2;
		}
	}	
	StopTimeMeasuring(tu);
	PrintMetrics(tu, (char*)"Hardware Float Multiplication", numCyclesPerTest, ExpectedRunTimes::hardwareFloatMul_ns);
	free(tu);

    //===============================================================================================//
    //======================================= DIVISION BENCHMARKING =================================//
    //===============================================================================================//

    //===== FpF32 DIVISION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++)
        {
            fpF32_3 = fpF32_1/fpF32_2;
        }

    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpF32 Division", numCyclesPerTest, ExpectedRunTimes::fpF32Div_ns);
    free(tu);

    //===== FpF64 DIVISION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++) {
            fpF64_3 = fpF64_1/fpF64_2;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpF64 Division", numCyclesPerTest, ExpectedRunTimes::fpF64Div_ns);
    free(tu);

    //===== FpS32 DIVISION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++) {
            fpS32_3 = fpS32_1*fpS32_2;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpS32 Division", numCyclesPerTest, ExpectedRunTimes::fpS32Div_ns);
    free(tu);

    //===== FpS64 DIVISION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++) {
            fpS64_3 = fpS64_1/fpS64_2;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"FpS64 Division", numCyclesPerTest, ExpectedRunTimes::fpS64Div_ns);
    free(tu);

    //===== HARDWARE FLOAT DIVISION =====//
    tu = StartTimeMeasuring();
    {
        uint32_t x = 0;
        for(x = 0; x < numCyclesPerTest; x++) {
            float3 = float1 / float2;
        }
    }
    StopTimeMeasuring(tu);
    PrintMetrics(tu, (char*)"Hardware Float Division", numCyclesPerTest, ExpectedRunTimes::hardwareFloatDiv_ns);
    free(tu);
}
