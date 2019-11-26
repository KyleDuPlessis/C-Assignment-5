//=================================================================================
// Name        : Driver.cpp
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 07/05/2019
// Description : A simple audio manipulation program to process audio sounds clips
// 				 using various editing operations - written in C++, Ansi-style
//=================================================================================

#include "Driver.h"

// main function
int main(int argc, char* argv[]) { // argc and argv values passed into main

	// argc - number of all items on command line
	// argv array - contains simple C-strings for each of these items
	// argv[0] is always the application name, and argv[1] the first argument

	string inputFileName1, inputFileName2, outputFileName, operation;

	outputFileName = "out";

	int bitCount, numChannels, position, sampleRateInHz;

	if (string(argv[2]) == "44100") {

		sampleRateInHz = processIntVal(argv[2]);

	}

	if ((string(argv[4]) == "8-bit") | (string(argv[4]) == "16-bit")) {

		if (string(argv[4]) == "8-bit") {

			bitCount = 8;

		} else {

			bitCount = 16;

		}

	}

	if ((processIntVal(argv[6]) == 1) | (processIntVal(argv[6]) == 2)) {

		if (processIntVal(argv[6]) == 1) {

			numChannels = 1;

		} else {

			numChannels = 2;

		}

	}

	if (string(argv[7]) == "-o") {

		outputFileName = argv[8];

		operation = argv[9];

		position = 9;

	} else {

		operation = argv[7];

		position = 7;

	}

	// audio operation (-add)
	if (operation == "-add") {

		cout << "Performing operation: " << operation << endl;

		inputFileName1 = argv[++position];

		inputFileName2 = argv[++position];

		add(sampleRateInHz, bitCount, numChannels, inputFileName1,
				inputFileName2, outputFileName);

		// audio operation (-cut r1 r2)
	} else if (operation == "-cut") {

		int r1, r2;

		cout << "Performing operation: " << operation << endl;

		r1 = processIntVal(argv[++position]);

		r2 = processIntVal(argv[++position]);

		pair<int, int> r = make_pair(r1, r2);

		inputFileName1 = argv[++position];

		cut(sampleRateInHz, bitCount, numChannels, inputFileName1, r,
				outputFileName);

		// audio operation (-radd r1 r2 s1 s2)
	} else if (operation == "-radd") {

		int r1, r2;

		cout << "Performing operation: " << operation << endl;

		r1 = processIntVal(argv[++position]);

		r2 = processIntVal(argv[++position]);

		pair<int, int> r = make_pair(r1, r2);

		inputFileName1 = argv[++position];

		inputFileName2 = argv[++position];

		radd(sampleRateInHz, bitCount, numChannels, inputFileName1,
				inputFileName2, r, outputFileName);

		// audio operation (-cat)
	} else if (operation == "-cat") {

		cout << "Performing operation: " << operation << endl;

		inputFileName1 = argv[++position];

		inputFileName2 = argv[++position];

		cat(sampleRateInHz, bitCount, numChannels, inputFileName1,
				inputFileName2, outputFileName);

		// audio operation (-v r1 r2)
	} else if (operation == "-v") {

		float r1, r2;

		cout << "Performing operation: " << operation << endl;

		r1 = processFloatVal(argv[++position]);

		if (numChannels == 2) {

			r2 = processFloatVal(argv[++position]);

			pair<float, float> p = make_pair(r1, r2);

			inputFileName1 = argv[++position];

			volumeFactorStereo(sampleRateInHz, bitCount, numChannels, inputFileName1,
					outputFileName, p);

		} else {

			inputFileName1 = argv[++position];

			volumeFactorMono(sampleRateInHz, bitCount, numChannels, inputFileName1,
					outputFileName, r1);

		}

		// audio operation (-rms)
	} else if (operation == "-rms") {

		cout << "Performing operation: " << operation << endl;

		inputFileName1 = argv[++position];

		rms(sampleRateInHz, bitCount, numChannels, inputFileName1);

		// audio operation (-rev)
	} else if (operation == "-rev") {

		cout << "Performing operation: " << operation << endl;

		inputFileName1 = argv[++position];

		rev(sampleRateInHz, bitCount, numChannels, inputFileName1,
				outputFileName);

		// audio operation (-norm r1 r2)
	} else if (operation == "-norm") {
		float r1, r2;

		cout << "Performing operation: " << operation << endl;

		r1 = processFloatVal(argv[++position]);

		if (numChannels == 2) {

			r2 = processFloatVal(argv[++position]);

			pair<float, float> p = make_pair(r1, r2);

			inputFileName1 = argv[++position];

			normalStereo(sampleRateInHz, bitCount, numChannels, inputFileName1,
					outputFileName, p);
		}

		inputFileName1 = argv[++position];

		normalMono(sampleRateInHz, bitCount, numChannels, inputFileName1,
				outputFileName, r1);

	} else {

		cout << "Incorrect audio operation!" << endl;

		exit(1);

	}

	return 0;

}
