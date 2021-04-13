#ifndef _MAIN_LIB_H_
#define _MAIN_LIB_H_

#include <stdlib.h>

#include <QAudioInput>
#include <QAudioOutput>
#include <QCoreApplication>
#include <QDateTime>
#include <QFile>
#include <QIODevice>
#include <QThread>
#include <QTimer>

typedef struct AudioInOut {
	QAudioInput  *rx = 0;
	QAudioOutput *tx = 0;
	QFile frx, ftx;
} AudioIO;

class AudioHandler : public QObject
{
	Q_OBJECT
private:
	AudioIO		audio;
	QAudioFormat	afmt;
	QFile		afile;
	QTimer		tm;
private slots:
	void rx_cb(QAudio::State st);
	void tx_cb(QAudio::State st);
public:
	void rx();
	void tx();
	void set_frx(const char *fn) {audio.frx.setFileName(fn);};
	void set_ftx(const char *fn) {audio.ftx.setFileName(fn);};
	void set_rate(int rate);
public slots:
	void rx_stop() {audio.rx->stop(); audio.frx.close(); delete audio.rx;};
	void tx_stop() {audio.tx->stop(); audio.ftx.close(); delete audio.tx;};
};

#endif

