//=================================================================================
// Name        : Audio.h
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 07/05/2019
// Description : A simple audio manipulation program to process audio sounds clips
// 				 using various editing operations - written in C++, Ansi-style
//=================================================================================

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <numeric>
#include <cstdint>

#ifndef LIBS_AUDIO_H
#define LIBS_AUDIO_H

using namespace std;

namespace DPLKYL002 {

// 1-channel (mono) Audio class
/*The Audio class should be templated to handle audio signals which use different
bit sizes for samples, depending on the provided audio clips.*/
template<typename BitCount> class Audio {

private:

	vector<BitCount> vectSamples;

	int numChannels, samplingRate, numSamples, lengthAudioClip;

public:

	// THE BIG 6

	// CONSTRUCTORS
	Audio(const string& inputFileName, int& sRate) :
			numChannels(1), samplingRate(sRate) {

		ifstream iFile(inputFileName, ios::binary | ios::in);

		if (iFile.is_open()) {

			long s = getAudioFileSize(inputFileName);

			this->numSamples = s / (sizeof(BitCount));

			this->lengthAudioClip = (int) (numSamples / ((float) sRate));

			vectSamples.resize(numSamples);

			for (int k = 0; k < numSamples; ++k) {

				BitCount b;

				iFile.read((char *) &b, sizeof(BitCount));

				vectSamples[k] = b;
			}

			iFile.close();

		} else {

			cout << "Error: unable to open [.raw] file." << endl;

			exit(1);

		}

	}

	Audio(int nSamples, int lengthAC, vector<BitCount> v, int& nChannels,
			int& sRate) :
			numChannels(nChannels), samplingRate(sRate), numSamples(nSamples), lengthAudioClip(
					lengthAC), vectSamples(v) {
	}

	// DESTRUCTOR
	~Audio() {

		numChannels = 0;

		samplingRate = 0;

		numSamples = 0;

		lengthAudioClip = 0;

		vectSamples.clear();

		vector<BitCount>().swap(vectSamples);

	}

	// MOVE CONTRUCTOR
	Audio(Audio&& oAudio) :
			numChannels(oAudio.numChannels), samplingRate(oAudio.samplingRate), numSamples(
					oAudio.numSamples), lengthAudioClip(oAudio.lengthAudioClip), vectSamples(
					oAudio.vectSamples) {

		oAudio.numChannels = 0;

		oAudio.samplingRate = 0;

		oAudio.numSamples = 0;

		oAudio.lengthAudioClip = 0;

		oAudio.vectSamples.clear();

	}

	// MOVE ASSIGNMENT OPERATOR
	Audio& operator =(Audio&& oAudio) {

		samplingRate = oAudio.samplingRate;

		numSamples = oAudio.numSamples;

		lengthAudioClip = oAudio.lengthAudioClip;

		vectSamples = oAudio.vectSamples;

		oAudio.numChannels = 0;

		oAudio.samplingRate = 0;

		oAudio.numSamples = 0;

		oAudio.lengthAudioClip = 0;

		oAudio.vectSamples.clear();

	}

	// COPY CONTRUCTOR
	Audio(const Audio& oAudio) :
		numChannels(oAudio.numChannels), samplingRate(oAudio.samplingRate), numSamples(
				oAudio.numSamples), lengthAudioClip(oAudio.lengthAudioClip), vectSamples(
				oAudio.vectSamples) {

	}

	// COPY ASSIGNMENT OPERATOR
	Audio& operator =(const Audio& oAudio) {

		samplingRate = oAudio.samplingRate;

		numSamples = oAudio.numSamples;

		lengthAudioClip = oAudio.lengthAudioClip;

		vectSamples = oAudio.vectSamples;

	}

	// UTILITY FUNCTIONS

	// GET SIZE
	long getAudioFileSize(const string& inputFileName) {

		ifstream iFile(inputFileName, ifstream::ate | std::ifstream::binary);

		return (long) iFile.tellg();

	}

	// SAVE
	void saveAudioFile(const string& inputFileName) {

		string newFileName = inputFileName + "_" + to_string(samplingRate) + "_"
				+ to_string(sizeof(BitCount) * 8) + "_mono.raw";

		ofstream oFile(newFileName, ios::binary | ios::out);

		if (oFile.is_open()) {

			for (int k = 0; k < vectSamples.size(); ++k) {

				oFile.write(reinterpret_cast<const char *>(&vectSamples[k]),
						sizeof(BitCount));

			}

		} else {

			cout << "Error: unable to open [.raw] file." << endl;

			exit(1);

		}

	}

	// OPERATORS

	// A | B: concatenate audio file A and B
	Audio operator |(const Audio& oAudio) {

		Audio audio(*this);

		audio.vectSamples.insert(audio.vectSamples.end(),
				oAudio.vectSamples.begin(), oAudio.vectSamples.end());

		audio.lengthAudioClip = audio.lengthAudioClip + oAudio.lengthAudioClip;

		audio.numSamples = audio.numSamples + oAudio.numSamples;

		return audio;

	}

	/*A * F: volume factor A with F; F will be a std::pair<float,float> with each float
	value in range [0.0,1.0]*/
	Audio operator *(float vol) {

		Audio audio(*this);

		transform(this->vectSamples.begin(), this->vectSamples.end(),
				audio.vectSamples.begin(), [vol](BitCount b) {return b*vol;});

		return audio;

	}

	// A+B: add sound file amplitudes together (per sample)
	Audio operator +(const Audio& oAudio) {

		Audio audio(*this);

		for (int k = 0; k < vectSamples.size(); ++k) {

			BitCount b = vectSamples[k] + oAudio.vectSamples[k];

			if (b > numeric_limits < BitCount >::max()) {

				b = numeric_limits < BitCount >::max();

			}

			audio.vectSamples[k] = b;

		}

		return audio;

	}

	/*A^F: F will be a std::pair<int,int> which specifies start and end sample of range
	of samples to be cut from sound file A. This implements a “cut” operation which
	produces a shorter clip (A with a portion removed).*/
	Audio operator ^(pair<int, int> range) {

		int numSamplesCut = numSamples - (range.second - range.first) - 1;

		int newLength = (int) (numSamplesCut / ((float) samplingRate));

		vector<BitCount> b;

		for (int k = 0; k < vectSamples.size(); ++k) {

			if (k < range.first || k > range.second) {

				b.push_back(vectSamples[k]);

			}

		}

		Audio<BitCount> audio(numSamplesCut, newLength, b, numChannels,
				samplingRate);

		return audio;

	}

	// AUDIO TRANSFORMATION

	/*Reverse: reverse all samples (this can be done very quickly with the
	STL)*/
	void revOrdering() {

		reverse(vectSamples.begin(), vectSamples.end());

	}

	/*Sound normalization: Use std::transform with a custom functor to
	normalize the sound files to the specified desired rms value (per channel).*/
	Audio& normalizeSound(float RMSVal) {

		float rms = computeRMS();

		// formula
		transform(vectSamples.begin(), vectSamples.end(),
				vectSamples.begin(), Normalize(RMSVal, rms));

		return *this;

	}

	/*Ranged add: select two (same length) sample ranges from two signals
	and add them together. This differs from the overloaded + which adds
	entire audio clips together.*/
	Audio rangedAdd(const Audio& oAudio, pair<int, int> r) {

		Audio audio(*this);

		Audio audioExtractFirst(*this);

		audioExtractFirst.vectSamples.clear();

		audioExtractFirst.vectSamples.resize(r.second - r.first);

		copy(vectSamples.begin() + r.first, vectSamples.begin() + r.second,
				audioExtractFirst.vectSamples.begin());

		Audio audioExtractSecond(oAudio);

		audioExtractSecond.vectSamples.clear();

		audioExtractSecond.vectSamples.resize(r.second - r.first);

		copy(oAudio.vectSamples.begin() + r.first,
				oAudio.vectSamples.begin() + r.second,
				audioExtractSecond.vectSamples.begin());

		Audio total = audioExtractFirst + audioExtractSecond;

		copy(total.vectSamples.begin(), total.vectSamples.end(),
				audio.vectSamples.begin() + r.first);

		return audio;

	}

	/*Compute RMS: use std::accumulate in <numeric> along with a custom
	lambda to compute the RMS (per channel)*/
	float computeRMS() {

		float val = 0.0;

		// formula
		float totalSum = accumulate(vectSamples.begin(), vectSamples.end(), val,
				[](float total, const BitCount& b) {
					return (total + ( pow(b, 2) ));
				});

		totalSum = (float) sqrt(totalSum / ((float) numSamples));

		return totalSum;

	}

	// Normalize class
	class Normalize {

	private:

		float newValue, value;

	public:

		// CONSTRUCTOR
		Normalize(float n, float v) :
				newValue(n), value(v) {

		}

		// OPERATOR
		BitCount operator()(BitCount b) {

			BitCount bCount = (BitCount) (b * (newValue / value));

			if (bCount > numeric_limits < BitCount >::max()) {

				bCount = numeric_limits < BitCount >::max();

			}

			return bCount;

		}

	};

};

// 2-channel (stereo) Audio class
/*The Audio class should be templated to handle audio signals which use different
bit sizes for samples, depending on the provided audio clips.*/
template<typename BitCount> class Audio<pair<BitCount, BitCount>> {

private:

	vector<pair<BitCount, BitCount>> vectSamples;

	int numChannels, samplingRate, numSamples, lengthAudioClip;

public:

	// THE BIG 6

	// CONSTRUCTORS
	Audio(const string& inputFileName, int& sRate) :
			numChannels(2), samplingRate(sRate) {

		ifstream iFile(inputFileName, ios::binary | ios::in);

		if (iFile.is_open()) {

			long s = getAudioFileSize(inputFileName);

			this->numSamples = s / (sizeof(BitCount) * numChannels);

			this->lengthAudioClip = (int) (numSamples / ((float) sRate));

			vectSamples.resize(numSamples);

			for (int k = 0; k < numSamples; ++k) {

				BitCount b;

				iFile.read((char *) &b, sizeof(BitCount));

				BitCount bS;

				iFile.read((char *) &bS, sizeof(BitCount));

				vectSamples[k] = (make_pair(b, bS));

			}

			iFile.close();

		} else {

			cout << "Error: unable to open [.raw] file." << endl;

			exit(1);

		}
	}


	Audio(int nSamples, int lengthAC, vector<pair<BitCount, BitCount>> vSamples,
			int& nChannels, int& sRate) :
			numChannels(nChannels), samplingRate(sRate), numSamples(nSamples), lengthAudioClip(
					lengthAC), vectSamples(vSamples) {

	}

	// DESTRUCTOR
	~Audio() {

		numChannels = 0;

		samplingRate = 0;

		numSamples = 0;

		lengthAudioClip = 0;

		vectSamples.clear();

		vector<pair<BitCount, BitCount>>().swap(vectSamples);

	}

	// MOVE CONTRUCTOR
	Audio(Audio&& oAudio) :
			numChannels(oAudio.numChannels), samplingRate(oAudio.samplingRate), numSamples(
					oAudio.numSamples), lengthAudioClip(oAudio.lengthAudioClip), vectSamples(
					oAudio.vectSamples) {

		oAudio.numChannels = 0;

		oAudio.samplingRate = 0;

		oAudio.numSamples = 0;

		oAudio.lengthAudioClip = 0;

		oAudio.vectSamples.clear();

	}

	// MOVE ASSIGNMENT OPERATOR
	Audio& operator =(Audio&& oAudio) {

		samplingRate = oAudio.samplingRate;

		numSamples = oAudio.numSamples;

		lengthAudioClip = oAudio.lengthAudioClip;

		vectSamples = oAudio.vectSamples;

		oAudio.numChannels = 0;

		oAudio.samplingRate = 0;

		oAudio.numSamples = 0;

		oAudio.lengthAudioClip = 0;

		oAudio.vectSamples.clear();

	}

	// COPY CONTRUCTOR
	Audio(const Audio& oAudio) :
		numChannels(oAudio.numChannels), samplingRate(oAudio.samplingRate), numSamples(
				oAudio.numSamples), lengthAudioClip(oAudio.lengthAudioClip), vectSamples(
				oAudio.vectSamples) {

	}

	// COPY ASSIGNMENT OPERATOR
	Audio& operator =(const Audio& oAudio) {

		samplingRate = oAudio.samplingRate;

		numSamples = oAudio.numSamples;

		lengthAudioClip = oAudio.lengthAudioClip;

		vectSamples = oAudio.vectSamples;

	}

	// UTILITY FUNCTIONS

	// GET SIZE
	long getAudioFileSize(const string& inputFileName) {

		ifstream iFile(inputFileName, ifstream::ate | ifstream::binary);

		return (long) iFile.tellg();

	}

	// SAVE
	void saveAudioFile(const string& inputFileName) {

		string newFileName = inputFileName + "_" + to_string(samplingRate) + "_"
				+ to_string(sizeof(BitCount) * 8) + "_stereo.raw";

		ofstream oFile(newFileName, ios::binary | ios::out);

		if (oFile.is_open()) {

			for (int k = 0; k < vectSamples.size(); ++k) {

				oFile.write(

						reinterpret_cast<const char *>(&vectSamples[k].first),
						sizeof(BitCount));

				oFile.write(
						reinterpret_cast<const char *>(&vectSamples[k].second),
						sizeof(BitCount));

			}

		} else {

			cout << "Error: unable to open [.raw] file." << endl;

			exit(1);

		}
	}

	// OPERATORS

	// A | B: concatenate audio file A and B
	Audio operator |(const Audio& oAudio) {

		Audio audio(*this);

		audio.vectSamples.insert(audio.vectSamples.end(),
				oAudio.vectSamples.begin(), oAudio.vectSamples.end());

		audio.lengthAudioClip = audio.lengthAudioClip + oAudio.lengthAudioClip;

		audio.numSamples = audio.numSamples + oAudio.numSamples;

		return audio;

	}

	/*A * F: volume factor A with F; F will be a std::pair<float,float> with each float
	value in range [0.0,1.0]*/
	Audio operator *(pair<float, float> vol) {

		Audio audio(*this);

		transform(this->vectSamples.begin(), this->vectSamples.end(),
				audio.vectSamples.begin(), [vol](pair<BitCount,BitCount> b) {

					return make_pair(b.first*vol.first, b.second*vol.second);

				});

		return audio;

	}

	// A+B: add sound file amplitudes together (per sample)
	Audio operator +(const Audio& oAudio) {

		Audio audio(*this);

		for (int k = 0; k < vectSamples.size(); ++k) {

			BitCount totalLeft = vectSamples[k].first
					+ oAudio.vectSamples[k].first;

			if (totalLeft > numeric_limits < BitCount >::max()) {

				totalLeft = numeric_limits < BitCount >::max();

			}

			BitCount totalRight = vectSamples[k].second
					+ oAudio.vectSamples[k].second;

			if (totalRight > numeric_limits < BitCount >::max()) {

				totalRight = numeric_limits < BitCount >::max();

			}

			audio.vectSamples[k].first = totalLeft;

			audio.vectSamples[k].second = totalRight;
		}

		return audio;

	}

	/*A^F: F will be a std::pair<int,int> which specifies start and end sample of range
	of samples to be cut from sound file A. This implements a “cut” operation which
	produces a shorter clip (A with a portion removed).*/
	Audio operator ^(pair<int, int> range) {

		int numSamplesCut = numSamples - (range.second - range.first) - 1;

		int newLength = (int) (numSamplesCut / ((float) samplingRate));

		vector<pair<BitCount, BitCount>> b;

		for (int k = 0; k < vectSamples.size(); ++k) {

			if (k < range.first || k > range.second) {

				b.push_back(vectSamples[k]);

			}

		}

		Audio<pair<BitCount, BitCount>> audio(numSamplesCut, newLength, b,
				numChannels, samplingRate);

		return audio;

	}

	// AUDIO TRANSFORMATION

	/*Reverse: reverse all samples (this can be done very quickly with the
	STL)*/
	void revOrdering() {

		reverse(vectSamples.begin(), vectSamples.end());

	}

	/*Sound normalization: Use std::transform with a custom functor to
	normalize the sound files to the specified desired rms value (per channel).*/
	Audio& normalizeSound(pair<float, float> RMSVal) {

		pair<float, float> rms = computeRMS();

		transform(vectSamples.begin(), vectSamples.end(), vectSamples.begin(),
				Normalize(RMSVal, rms));

		return *this;

	}

	/*Ranged add: select two (same length) sample ranges from two signals
	and add them together. This differs from the overloaded + which adds
	entire audio clips together.*/
	Audio rangedAdd(const Audio& oAudio, pair<int, int> r) {

		Audio audio(*this);

		Audio audioExtractFirst(*this);

		audioExtractFirst.vectSamples.clear();

		audioExtractFirst.vectSamples.resize(r.second - r.first);

		copy(vectSamples.begin() + r.first, vectSamples.begin() + r.second,
				audioExtractFirst.vectSamples.begin());

		Audio audioExtractSecond(oAudio);

		audioExtractSecond.vectSamples.clear();

		audioExtractSecond.vectSamples.resize(r.second - r.first);

		copy(oAudio.vectSamples.begin() + r.first,
				oAudio.vectSamples.begin() + r.second,
				audioExtractSecond.vectSamples.begin());

		Audio total = audioExtractFirst + audioExtractSecond;

		copy(total.vectSamples.begin(), total.vectSamples.end(),
				audio.vectSamples.begin() + r.first);

		return audio;

	}

	/*Compute RMS: use std::accumulate in <numeric> along with a custom
	lambda to compute the RMS (per channel)*/
	pair<float, float> computeRMS() {

		pair<float, float> val = { 0.0, 0.0 };

		pair<float, float> totalSum = accumulate(vectSamples.begin(),
				vectSamples.end(), val,
				[](pair<float,float> total, pair<BitCount,BitCount> b) {

					total.first = total.first + pow(b.first,2);

					total.second = total.second + pow(b.second,2);

					return total;

				});

		totalSum.first = (float) sqrt(totalSum.first / ((float) numSamples));

		totalSum.second = (float) sqrt(totalSum.second / ((float) numSamples));

		return totalSum;

	}

	// Normalize class
	class Normalize {

	private:

		pair<float, float> newValue, value;

	public:

		// CONSTRUCTOR
		Normalize(pair<float, float> d, pair<float, float> c) :
				newValue(d), value(c) {

		}

		// OPERATOR
		pair<BitCount, BitCount> operator()(pair<BitCount, BitCount> b) {

			BitCount bLeft = (BitCount) (b.first
					* (newValue.first / value.first));

			BitCount bRight = (BitCount) (b.second
					* (newValue.second / value.second));

			if (bLeft > numeric_limits < BitCount >::max()) {

				bLeft = numeric_limits < BitCount >::max();

			}

			if (bRight > numeric_limits < BitCount >::max()) {

				bRight = numeric_limits < BitCount >::max();

			}

			return {bLeft, bRight};

		}

	};

};

}

#endif
