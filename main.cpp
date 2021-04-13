#include "lib.h"

//Note: recommended sample rate is 100 to 5000
int main(int argc, char **argv)
{
	QCoreApplication app(argc, argv);
	AudioHandler hdl;

	switch (argc) {
	case 2: hdl.set_rate(atoi(argv[1])); hdl.set_frx("out.raw"); hdl.rx(); break;
	case 3: hdl.set_rate(atoi(argv[1])); hdl.set_ftx(argv[2]);   hdl.tx(); break;
	default:printf("Usage: %s data_rate [input_file]\n", argv[0]); break;
	}

	return app.exec();
}

