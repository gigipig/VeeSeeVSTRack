#pragma once

#include <jansson.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#include <RtAudio.h>
#pragma GCC diagnostic pop


namespace rack {


struct AudioIO {
	// Stream properties
	int driver = 0;
	int device = -1;
	int offset = 0;
	int sampleRate = 44100;
	int blockSize = 256;
	int numOutputs = 0;
	int numInputs = 0;
	RtAudio *rtAudio = NULL;
	/** Cached */
	RtAudio::DeviceInfo deviceInfo;

	AudioIO();
	virtual ~AudioIO();

	std::vector<int> getDrivers();
	std::string getDriverName(int driver);
	void setDriver(int driver);

	int getDeviceCount();
	bool getDeviceInfo(int device, RtAudio::DeviceInfo *deviceInfo);
	int getDeviceMaxChannels(int device);
	std::string getDeviceName(int device);
	std::string getDeviceDetail(int device, int offset, int maxChannels);
	void setDevice(int device, int offset, int maxChannels);

	void setSampleRate(int sampleRate);
	void setBlockSize(int blockSize);

	/** Must close the stream before opening */
	void openStream();
	void closeStream();
	/** Returns whether the audio stream is open and running */
	bool isActive();

	std::vector<int> getSampleRates();

	virtual void processStream(const float *input, float *output, int length) {}
	virtual void onCloseStream() {}
	virtual void onOpenStream() {}
	json_t *toJson();
	void fromJson(json_t *rootJ);
};


} // namespace rack
