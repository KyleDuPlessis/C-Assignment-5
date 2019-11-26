//=================================================================================
// Name        : Driver.h
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 07/05/2019
// Description : A simple audio manipulation program to process audio sounds clips
// 				 using various editing operations - written in C++, Ansi-style
//=================================================================================

#include <iostream>
#include "Audio.h"

#ifndef LIBS_DRIVER_H
#define LIBS_DRIVER_H

using namespace DPLKYL002;

namespace DPLKYL002 {

void radd(int samplingRate, int bCount, int numChannels, string inputFileName1,
		string inputFileName2, pair<int, int> r, string outputFileName) {

	if (bCount == 8) {

		if (numChannels == 1) {

			Audio<int8_t> audioFile1 = Audio<int8_t>(inputFileName1,
					samplingRate);

			Audio<int8_t> audioFile2 = Audio<int8_t>(inputFileName2,
					samplingRate);

			Audio<int8_t> audio = audioFile1.rangedAdd(audioFile2, r);
			audio.saveAudioFile(outputFileName);

		} else {

			Audio<pair<int8_t, int8_t>> audioFile1 =
					Audio<pair<int8_t, int8_t>>(inputFileName1, samplingRate);

			Audio<pair<int8_t, int8_t>> audioFile2 =
					Audio<pair<int8_t, int8_t>>(inputFileName2, samplingRate);

			Audio<pair<int8_t, int8_t>> audio = audioFile1.rangedAdd(audioFile2,
					r);

			audio.saveAudioFile(outputFileName);

		}

	} else {

		if (numChannels == 1) {

			Audio<int16_t> audioFile1 = Audio<int16_t>(inputFileName1,
					samplingRate);

			Audio<int16_t> audioFile2 = Audio<int16_t>(inputFileName2,
					samplingRate);

			Audio<int16_t> audio = audioFile1.rangedAdd(audioFile2, r);

			audio.saveAudioFile(outputFileName);

		} else {

			Audio<pair<int16_t, int16_t>> audioFile1 = Audio<
					pair<int16_t, int16_t>>(inputFileName1, samplingRate);

			Audio<pair<int16_t, int16_t>> audioFile2 = Audio<
					pair<int16_t, int16_t>>(inputFileName2, samplingRate);

			Audio<pair<int16_t, int16_t>> audio = audioFile1.rangedAdd(
					audioFile2, r);

			audio.saveAudioFile(outputFileName);

		}

	}

}

void cat(int samplingRate, int bCount, int numChannels, string inputFileName1,
		string inputFileName2, string outputFileName) {

	if (bCount == 8) {

		if (numChannels == 1) {

			Audio<int8_t> audioFile1 = Audio<int8_t>(inputFileName1,
					samplingRate);

			Audio<int8_t> audioFile2 = Audio<int8_t>(inputFileName2,
					samplingRate);

			Audio<int8_t> audio = audioFile1 | audioFile2;
			audio.saveAudioFile(outputFileName);

		} else {
			Audio<pair<int8_t, int8_t>> audioFile1 =
					Audio<pair<int8_t, int8_t>>(inputFileName1, samplingRate);

			Audio<pair<int8_t, int8_t>> audioFile2 =
					Audio<pair<int8_t, int8_t>>(inputFileName2, samplingRate);

			Audio<pair<int8_t, int8_t>> audio = audioFile1 | audioFile2;

			audio.saveAudioFile(outputFileName);

		}
	} else {
		if (numChannels == 1) {

			Audio<int16_t> audioFile1 = Audio<int16_t>(inputFileName1,
					samplingRate);

			Audio<int16_t> audioFile2 = Audio<int16_t>(inputFileName2,
					samplingRate);

			Audio<int16_t> audio = audioFile1 | audioFile2;

			audio.saveAudioFile(outputFileName);

		} else {

			Audio<pair<int16_t, int16_t>> audioFile1 = Audio<
					pair<int16_t, int16_t>>(inputFileName1, samplingRate);

			Audio<pair<int16_t, int16_t>> audioFile2 = Audio<
					pair<int16_t, int16_t>>(inputFileName2, samplingRate);

			Audio<pair<int16_t, int16_t>> audio = audioFile1 | audioFile2;

			audio.saveAudioFile(outputFileName);

		}

	}

}

void add(int samplingRate, int bCount, int numChannels, string inputFileName1,
		string inputFileName2, string outputFileName) {

	if (bCount == 8) {

		if (numChannels == 1) {

			Audio<int8_t> audioFile1 = Audio<int8_t>(inputFileName1,
					samplingRate);

			Audio<int8_t> audioFile2 = Audio<int8_t>(inputFileName2,
					samplingRate);

			Audio<int8_t> audio = audioFile1 + audioFile2;

			audio.saveAudioFile(outputFileName);

		} else {

			Audio<pair<int8_t, int8_t>> audioFile1 =
					Audio<pair<int8_t, int8_t>>(inputFileName1, samplingRate);

			Audio<pair<int8_t, int8_t>> audioFile2 =
					Audio<pair<int8_t, int8_t>>(inputFileName2, samplingRate);

			Audio<pair<int8_t, int8_t>> audio = audioFile1 + audioFile2;

			audio.saveAudioFile(outputFileName);

		}

	} else {

		if (numChannels == 1) {

			Audio<int16_t> audioFile1 = Audio<int16_t>(inputFileName1,
					samplingRate);

			Audio<int16_t> audioFile2 = Audio<int16_t>(inputFileName2,
					samplingRate);

			Audio<int16_t> audio = audioFile1 + audioFile2;

			audio.saveAudioFile(outputFileName);

		} else {

			Audio<pair<int16_t, int16_t>> audioFile1 = Audio<
					pair<int16_t, int16_t>>(inputFileName1, samplingRate);

			Audio<pair<int16_t, int16_t>> audioFile2 = Audio<
					pair<int16_t, int16_t>>(inputFileName2, samplingRate);

			Audio<pair<int16_t, int16_t>> audio = audioFile1 + audioFile2;

			audio.saveAudioFile(outputFileName);

		}

	}

}

void cut(int samplingRate, int bCount, int numChannels, string inputFileName,
		pair<int, int> range, string outputFileName) {

	if (bCount == 8) {

		if (numChannels == 1) {

			Audio<int8_t> audioFile = Audio<int8_t>(inputFileName,
					samplingRate);

			Audio<int8_t> audio = audioFile ^ range;

			audio.saveAudioFile(outputFileName);

		} else {

			Audio<pair<int8_t, int8_t>> audioFile = Audio<pair<int8_t, int8_t>>(
					inputFileName, samplingRate);

			Audio<pair<int8_t, int8_t>> audio = audioFile ^ range;

			audio.saveAudioFile(outputFileName);

		}

	} else {

		if (numChannels == 1) {

			Audio<int16_t> audioFile = Audio<int16_t>(inputFileName,
					samplingRate);

			Audio<int16_t> audio = audioFile ^ range;

			audio.saveAudioFile(outputFileName);

		} else {

			Audio<pair<int16_t, int16_t>> audioFile = Audio<
					pair<int16_t, int16_t>>(inputFileName, samplingRate);

			Audio<pair<int16_t, int16_t>> audio = audioFile ^ range;

			audio.saveAudioFile(outputFileName);

		}
	}
}

void rev(int samplingRate, int bCount, int numChannels, string inputFileName,
		string outputFileName) {

	if (bCount == 8) {

		if (numChannels == 1) {

			Audio<int8_t> audioFile = Audio<int8_t>(inputFileName,
					samplingRate);

			audioFile.revOrdering();

			audioFile.saveAudioFile(outputFileName);

		} else {

			Audio<pair<int8_t, int8_t>> audioFile = Audio<pair<int8_t, int8_t>>(
					inputFileName, samplingRate);

			audioFile.revOrdering();

			audioFile.saveAudioFile(outputFileName);

		}

	} else {

		if (numChannels == 1) {

			Audio<int16_t> audioFile = Audio<int16_t>(inputFileName,
					samplingRate);

			audioFile.revOrdering();

			audioFile.saveAudioFile(outputFileName);

		} else {

			Audio<pair<int16_t, int16_t>> audioFile = Audio<
					pair<int16_t, int16_t>>(inputFileName, samplingRate);

			audioFile.revOrdering();

			audioFile.saveAudioFile(outputFileName);

		}

	}

}

void normalMono(int samplingRate, int bCount, int numChannels,
		string inputFileName, string outputFileName, float r1) {

	if (bCount == 8) {

		Audio<int8_t> audioFile = Audio<int8_t>(inputFileName, samplingRate);

		Audio<int8_t> audio = audioFile.normalizeSound(r1);

		audio.saveAudioFile(outputFileName);

	} else {

		Audio<int16_t> audioFile = Audio<int16_t>(inputFileName, samplingRate);

		Audio<int16_t> audio = audioFile.normalizeSound(r1);

		audio.saveAudioFile(outputFileName);

	}

}

void normalStereo(int samplingRate, int bCount, int numChannels,
		string inputFileName, string outputFileName, pair<float, float> p) {

	if (bCount == 8) {

		Audio<pair<int8_t, int8_t>> audioFile = Audio<pair<int8_t, int8_t>>(
				inputFileName, samplingRate);

		Audio<pair<int8_t, int8_t>> audio = audioFile.normalizeSound(p);

		audio.saveAudioFile(outputFileName);

	} else {

		Audio<pair<int16_t, int16_t>> audioFile = Audio<pair<int16_t, int16_t>>(
				inputFileName, samplingRate);

		Audio<pair<int16_t, int16_t>> audio = audioFile.normalizeSound(p);

		audio.saveAudioFile(outputFileName);

	}

}

void volumeFactorMono(int samplingRate, int bCount, int numChannels,
		string inputFileName, string outputFileName, float r1) {

	if (bCount == 8) {

		Audio<int8_t> audioFile = Audio<int8_t>(inputFileName, samplingRate);

		Audio<int8_t> audio = audioFile * r1;

		audio.saveAudioFile(outputFileName);

	} else {

		Audio<int16_t> audioFile = Audio<int16_t>(inputFileName, samplingRate);

		Audio<int16_t> audio = audioFile * r1;

		audio.saveAudioFile(outputFileName);

	}

}

void volumeFactorStereo(int samplingRate, int bCount, int numChannels,
		string inputFileName, string outputFileName, pair<float, float> p) {

	if (bCount == 8) {

		Audio<pair<int8_t, int8_t>> audioFile = Audio<pair<int8_t, int8_t>>(
				inputFileName, samplingRate);

		Audio<pair<int8_t, int8_t>> audio = audioFile * p;

		audio.saveAudioFile(outputFileName);

	} else {

		Audio<pair<int16_t, int16_t>> audioFile = Audio<pair<int16_t, int16_t>>(
				inputFileName, samplingRate);

		Audio<pair<int16_t, int16_t>> audio = audioFile * p;

		audio.saveAudioFile(outputFileName);

	}

}

void rms(int samplingRate, int bCount, int numChannels, string inputFileName) {

	if (bCount == 8) {

		if (numChannels == 1) {

			Audio<int8_t> audioFile = Audio<int8_t>(inputFileName,
					samplingRate);

			cout << "Audio file RMS: " << audioFile.computeRMS() << endl;

		} else {

			Audio<pair<int8_t, int8_t>> audioFile = Audio<pair<int8_t, int8_t>>(
					inputFileName, samplingRate);

			cout << "Audio file left channel RMS: " << audioFile.computeRMS().first
					<< endl;

			cout << "Audio file right channel RMS: " << audioFile.computeRMS().second
					<< endl;

		}

	} else {

		if (numChannels == 1) {

			Audio<int16_t> audioFile = Audio<int16_t>(inputFileName,
					samplingRate);

			cout << "Audio file RMS: " << audioFile.computeRMS() << endl;

		} else {

			Audio<pair<int16_t, int16_t>> audioFile = Audio<
					pair<int16_t, int16_t>>(inputFileName, samplingRate);

			cout << "Audio file left channel RMS: " << audioFile.computeRMS().first
					<< endl;

			cout << "Audio file right channel RMS: " << audioFile.computeRMS().second
					<< endl;

		}

	}

}

int processIntVal(char* val) {

	stringstream ss(val);

	int value;

	ss >> value;

	return value;

}

float processFloatVal(char* val) {

	stringstream ss(val);

	float value;

	ss >> value;

	return value;

}

}

#endif
