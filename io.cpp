#include "lib.h"

void AudioHandler::set_rate(int rate)
{
	QAudioDeviceInfo ainf = QAudioDeviceInfo::defaultInputDevice();
	afmt.setByteOrder(QAudioFormat::LittleEndian);
	afmt.setChannelCount(1);
	afmt.setCodec("audio/pcm");
	afmt.setSampleRate(rate);
	afmt.setSampleSize(8);
	afmt.setSampleType(QAudioFormat::UnSignedInt);
	if (!ainf.isFormatSupported(afmt)) {
		printf("WARNING: Audio config not supported, trying nearest config.\n");
		afmt = ainf.nearestFormat(afmt);
		printf( "Byte order:\t%d\nCh count:\t%d\nCodec:\t%s\n"
			"Samp rate:\t%d\nSamp size:\t%d\nSamp type:\t%d\n",
			afmt.byteOrder(),  afmt.channelCount(), afmt.codec().toStdString().c_str(),
			afmt.sampleRate(), afmt.sampleSize(),   afmt.sampleType());
	} else printf("Audio config OK\n");
}

//Receive data and write to file
void AudioHandler::rx()
{
	audio.frx.open(QIODevice::WriteOnly | QIODevice::Truncate);
	audio.rx = new QAudioInput(afmt);
	connect(audio.rx, SIGNAL(stateChanged(QAudio::State)), this, SLOT(rx_cb(QAudio::State)));
	audio.rx->start(&audio.frx);
}

//Transmit data from source file
void AudioHandler::tx()
{
	audio.ftx.open(QIODevice::ReadOnly);
	audio.tx = new QAudioOutput(afmt);
	connect(audio.tx, SIGNAL(stateChanged(QAudio::State)), this, SLOT(tx_cb(QAudio::State)));
	audio.tx->start(&audio.ftx);
}

void AudioHandler::rx_cb(QAudio::State st)
{
	switch (st) {
	case QAudio::StoppedState:
		if (audio.rx->error() != QAudio::NoError) printf("Stopped because of error\n");
		else printf("Stopped, no error\n");
		rx_stop();
		break;
	case QAudio::ActiveState:
		break;
	default:break;
	}
}

void AudioHandler::tx_cb(QAudio::State st)
{
	switch (st) {
	case QAudio::StoppedState:
		if (audio.tx->error() != QAudio::NoError) printf("Stopped because of error\n");
		else printf("Stopped, no error\n");
		tx_stop();
		break;
	case QAudio::ActiveState:
		break;
	default:break;
	}
}

AudioWrapper::AudioWrapper()
{
	tm.setInterval(3000);
	tm.setSingleShot(true);
	connect(&tm, SIGNAL(timeout()), &hdl, SLOT(rx_stop()));
	connect(&tm, SIGNAL(timeout()), &hdl, SLOT(tx_stop()));
}

