#pragma once
//#include "QApp.h" //Failed attempt to allow QAPP to be incldued/inherited/as depdency to allow the Percent QB Prograss Bar to be updated
#include <QThread>
//#include <QtCore\qmutex.h>

//#include "QApp.h"
#include <opencv2/core/mat.hpp>
//#include <opencv2/core/cuda.inl.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
//#include <opencv2/objdetect.hpp>
#include <opencv2/core/utility.hpp>
#include "UnitTest.h"
#include <iostream>


class ParseImg : public QThread
{
	Q_OBJECT
public:
	ParseImg(QObject* parent = 0);

	bool setThresh;

	//void ParseImg2(QString V2, bool setThresh);
	void ParseImg2();

	void run() override;

	void getParams(QString V2, bool setT);

	//void getCoord(int ax, int ay);
	int getCoord(int ax, int ay, int lx, int ly);
	
	//float Prcnt;
	float Prcnt2;

	int getProgression()
	{
		return Prcnt2;
	}

	//QMutex mutex;

	QString V;

	const QString OutPath = QDir::currentPath() + "/Results/"; //* can be set as const as may not need to be changed *//

	int v, i;

	//uint32_t tx, ty = 0;
	int tx, ty, lx, ly = 0;

};
