#include "ParseImg.h"

UnitTest UT2;

//using std::cout;
//using std::endl;

//tried moving imoprts/includes/dpedencies into the header isnetad of the main class impelemtayion to see if it works as a possible optimisation.....
//Perhapes adding the Img path and the SetThresh method as cimrtuctor arguments may be mroe efeftcive/efficent
ParseImg::ParseImg(QObject* parent) : QThread(parent)
{
	
	

}

void ParseImg::run()
{
	//ParseImg2(V, setThresh);
	ParseImg2();
	this->exit();
}

//int 

void ParseImg::getParams(QString V2, bool setT)
{
	V = V2;
	setThresh = setT;
}

//very lazy/bad getter for the selected Img region
//void ParseImg::getCoord(int ax, int ay)
int ParseImg::getCoord(int ax, int ay, int alx2, int aly2)
{
	
	tx = ax;
	ty = ay;
	lx = alx2;
	ly = aly2;


	return tx, ty, lx, ly;
}

//void ParseImg::ParseImg2(QString V, bool SetT)
void ParseImg::ParseImg2()
{
///*/*/*/
//	qDebug("Parsing");
//	std::string vv = V.toStdString(); //get img folder
//	std::string out = OutPath.toStdString(); //get output folder
//	//emit on_opened_state();
//	QFile file(V);
//	QFileInfo imginfo(V);
//	//qtest::let_error
//
//	//qverify2(file.exists(), "bad/invalid path!: file not found");
//
//	/*https://doc.qt.io/qt-5/qfileinfo.html#completesuffix https://doc.qt.io/qt-5/qfileinfo.html#suffix*/
//
//	//cout << ut.checkpaths(v) << endl;
//	QVERIFY(UT2.checkPaths(V));
//	QVERIFY(UT2.checkFileFormats(V));
//
//
//
//
//
//
//	cv::Mat pic = cv::imread(vv);
//
//	//medianblur(pic, pic, 1);
//	cv::imwrite(out + "unmodif-base.png", pic);
//
//	//*must be converted to a binary bitmap (black and white) as the threshold function cant support full colour bitmaps
//	cv::Mat grey;
//	//cv::cvtcolor(kmeans, grey, cv::color_bgr2gray);
//	cv::cvtColor(pic, grey, cv::COLOR_BGR2GRAY);
//	cv::imwrite(out + "gr.png", grey);
//
//	qDebug() << "depth:" << pic.depth();
//	qDebug() << "rgb channels:" << pic.channels();
//	qDebug() << "type:" << pic.type();
//
//
//
//	//cv::equalizehist(grey, grey);
//
//	//std::vector<cv::Rect> rects;
//	cv::Mat pic2;
//	//cc.detectmultiscale(grey, rects);
//	float max;// = vec4.size();
//	//float at;// = vec4[i][0];
//	//std::vector<cv::Point> points;
//	//v = 0;
//	//qb->reset();
//	//* update progress bar percentage completion*/
//
//	//QB->setValue(100);
//	//qb.setvalue(100);
//
//
//	/** may have to use qpianter isntead of teh annotation too. to draw rects which could be basses as a 'cropped' mat to the actual object detection handling/
//	/ it may also be the acse that the annotation tool only simply provides the numebr of annotation and the coords of the drawn rect to the said annotations file .txt
//		in this acse the paramaters returned in the output file are the number of annnots and the x,y the top lefy and bottom right
//
//		apparent;u thies erect mats are then passe to the opencv_traincascade backend to crarry out teh actual cascade training object detection
//
//	/**consider a conntection here to force the qpainter to update/render the output bitmap.......*/
///*/*/*
	//isbusy = true;
	std::string vv = V.toStdString(); //Get Img Folder
	std::string Out = OutPath.toStdString(); //Get Output Folder
	//emit on_opened_state();
	QFile file(V);
	QFileInfo ImgInfo(V);
	//QTest::LET_Error

	//QVERIFY2(file.exists(), "Bad/Invalid Path!: File Not found");

	/*https://doc.qt.io/qt-5/qfileinfo.html#completeSuffix https://doc.qt.io/qt-5/qfileinfo.html#suffix*/

	//cout << UT.checkPaths(V) << endl;
	QVERIFY(UT2.checkPaths(V));
	QVERIFY(UT2.checkFileFormats(V));
	//UT.qExec();


	/**Using default Vectors here instead of the Custom LinkedList header as the OpenCV functions
	seem to be designed to handle the Vector templates by default and likely can't easily accept other
	data structures normally without extensive backend modification'*/

	std::vector<cv::Vec4i> Vec4;
	std::vector< std::vector<cv::Point2i> > Contour;
	std::vector< std::vector<cv::Point2i> > ContourApx;
	//mItemListv2< mItemListv2<cv::Point2i> > ContourApx;
	//mItemListv2<cv::InputArray> ContourApx;

	//cv::Mat Pic = cv::imread(vv);
	printf("%s %i %i \n", "Selecting Bounds: ", tx, ty);
	//cv::Mat Pic = cv::imread(vv).rowRange(100, 200).colRange(100, 200);
	//cv::Mat Pic = cv::imread(vv).colRange(tx, ty);
	/*crop Inout image at the very beginning seems to be the simplist method to Enable basic image cropping 
	for as it saves only teh cropped version of the inout image instead of the full mat which allows the subsequent method calls 
	to b e 'restricted' to the cropped image instead of wrroyign baout warrying about outogbound/range exceptions  or calling. initialising additional vafiabels to restrict the range to the same coords/Dims as the provided reagon/crop
	One of teh only drawbacks of this is that this cannot be Overlays/Superimposed bakc onto the orignal sized InotuImage/Mat Due to the original image Dims being Effectively ignored
	Inn addition this also prevents an isue with teh Mian for loop for drawing the detected contours as it will still darwn the number of conutors ewual to that found imn the crop with no respect to the crop dims or positions as it cannot be specified to target a specific reagon of the provided mat in its current implementation anyway
	e.g. Full image : 1928 contours, cropped region : 200 contours, will strill draw first 200 contorus found irrepsective if they are ithin the crop region or not*/
	//cv::Mat Pic = cv::imread(vv).colRange(tx, ty).rowRange(lx, ly);

	//ugly check to prevnt/avoid crashes/excpetions due to crop regions eualling 0/NULL if a crop region is not selected via user intervention: Thee ar eliklely far more optimal metods of dding this (e.g.: is lkely more optimal to chnage the crop region to the full Mat/img/Bitmap size e.g.)
	cv::Mat Pic;
	if (tx == 0 || ty == 0)
		Pic = cv::imread(vv);
	else
		Pic = cv::imread(vv).colRange(tx, ty).rowRange(lx, ly);

	//https://docs.opencv.org/3.0-rc1/d7/d45/classcv_1_1UMat.html
	//https://docs.opencv.org/3.0-rc1/dc/d84/group__core__basic.html#ga5681439dda418431eb0a672697135ed2
	//cv::UMat Pic2 = ((ty - tx), (ly - lx), vv, cv::USAGE_ALLOCATE_DEVICE_MEMORY);
	//cv::UMat Pic2 = (cv::imread(vv), cv::USAGE_ALLOCATE_DEVICE_MEMORY);
	//cv::UMat Pic2 = (cv::imread(vv), (ty - tx), (ly - lx), cv::USAGE_ALLOCATE_DEVICE_MEMORY);
	//cv::UMat Pic2 = (cv::imread(vv, cv::IMREAD_UNCHANGED).getUMat(cv::ACCESS_READ), (ty - tx), (ly - lx), cv::USAGE_ALLOCATE_DEVICE_MEMORY);
	//cv::UMat Pic2 = (cv::imread(vv, cv::IMREAD_UNCHANGED).colRange(tx, ty).rowRange(lx, ly), cv::USAGE_ALLOCATE_DEVICE_MEMORY);
	//cv::UMat Pic2 = (cv::imread(vv, cv::IMREAD_UNCHANGED), Pic2.colRange(tx, ty), Pic2.rowRange(lx, ly), cv::USAGE_ALLOCATE_DEVICE_MEMORY);
	//cv::UMat Pic2 = (cv::imread(vv, cv::IMREAD_UNCHANGED).getUMat(cv::ACCESS_READ), 100, 200, cv::USAGE_ALLOCATE_DEVICE_MEMORY);
	//cv::UMat Pic2 = (cv::imread(vv, cv::IMREAD_UNCHANGED).getUMat(cv::ACCESS_READ));

	//Acces Violation When attempting to construct the Umat, may be due to this being ona seperate Thread as the Qpainter is also reading the same Image/BitMap
		//Might acually be an isue with the Intel iGPu as it is detected as a Valid OpenCL devcie depsite being disabled (Via BIOS)
	//cv::UMat Pic2 = (cv::imread(vv, cv::IMREAD_UNCHANGED).getUMat(cv::ACCESS_RW), cv::USAGE_ALLOCATE_DEVICE_MEMORY);
	
//	cv::Range CoordRange(tx, ty);
	
	//cv::Mat CropInput = Pic.rowRange(tx, ty).colRange(tx, ty);


	//medianBlur(Pic, Pic, 1);
	//cv::imwrite(Out + "UnModif-base.png", Pic2);
	cv::imwrite(Out + "UnModif-base.png", Pic);

	//*Must be converted to a Binary Bitmap (black and white) as the threshold function cant support full colour bitmaps
	cv::Mat Grey;
	//cv::UMat Grey2 = (Pic2.rows(), Pic2.cols());
	//cv::UMat Grey2 = 1920,1080;// ((ty - tx), (ly - lx));
	//cv::UMat Grey2 = Pic2;
	//cv::cvtColor(KMeans, Grey, cv::COLOR_BGR2GRAY);
	//cv::Range CoordRange(tx, ty);
	//cv::cvtColor(Pic, Grey.rowRange(tx, ty).colRange(tx, ty), cv::COLOR_BGR2GRAY);
	//cv::cvtColor(Pic2, Grey2, cv::COLOR_BGR2GRAY);

	printf("Set Grey");
	cv::cvtColor(Pic, Grey, cv::COLOR_BGR2GRAY);
	/*cv::cvtColor(Pic2, Grey2, cv::COLOR_YUV2BGR);
	cv::cvtColor(Grey2, Grey2, cv::COLOR_BGR2GRAY);*/
	//cv::cvtColor(Pic2, Grey2, cv::COLOR_BGR2YUV);
	//cv::cvtColor(Pic2, Grey2, cv::COLOR_RGB2GRAY);
	//cv::cvtColor(Pic2, Pic2, cv::COLOR_RGB2GRAY);

	//cv::rang
	/*cv::Range CoordRange(tx, ty);*/
	//cv::imwrite(Out + "Gr.png", Grey2);
	//cv::imwrite(Out + "Gr.png", Grey.colRange(CoordRange));
	//cv::imwrite(Out + "Gr.png", Grey.rowRange(tx, ty).colRange(tx, ty));
	cv::imwrite(Out + "Gr.png", Grey);

	/*qDebug() << "Depth:" << Pic2.depth();
	qDebug() << "RGB Channels:" << Pic2.channels();
	qDebug() << "Type:" << Pic2.type();*/
	qDebug() << "Depth:" << Pic.depth();
	qDebug() << "RGB Channels:" << Pic.channels();
	qDebug() << "Type:" << Pic.type();
	// https://docs.opencv.org/master/d3/d63/classcv_1_1Mat.html#a0b57b6a326c8876d944d188a46e0f556

	cv::Mat ThreshImg;
	//cv::UMat ThreshImg2;


	//** very important for accuracy */
		//https://opencvpython.blogspot.com/2012/06/hi-this-article-is-tutorial-which-try.html


	/*The contour detection is limited and only detects black pixels,
	hense why the associated threshold function is very usefull in crushing a range of gradients into a more distinct colour*/
	/*Perhaps add custom Annotation Objects this way*/
	//setThresh = SetT;
	switch (setThresh)
	{
		/*/Linear threshold is much more consistent with simple shapes but cannot handle complex geometry well*/

	case false:
	{
		qDebug() << "Set" << setThresh;
		threshold(Grey, ThreshImg, 80, 250, cv::THRESH_TRIANGLE);
		//threshold(Grey2, ThreshImg2, 80, 250, cv::THRESH_TRIANGLE);
		//threshold(Pic2, ThreshImg2, 80, 250, cv::THRESH_TRIANGLE);
		//threshold(Pic, ThreshImg2, 80, 250, cv::THRESH_TRIANGLE);
		//threshold(Pic, ThreshImg, 80, 250, cv::THRESH_TRIANGLE);
		break;
	}
	/**Drastically improved Theshold Method Here: https://docs.opencv.org/3.4/d7/d4d/tutorial_py_thresholding.html
	However it seems to be complete overkill for Simple Geometriy and  causes distortions/excessive Detail)
	so it may be worth enabling a user toggle to enable switching between both methods*/
	case true:
	{
		qDebug() << "Set" << setThresh;
		adaptiveThreshold(Grey, ThreshImg, 230, cv::THRESH_BINARY_INV, cv::THRESH_BINARY, 11, 3);
		//adaptiveThreshold(Grey.colRange(tx, ty), ThreshImg, 230, cv::THRESH_BINARY_INV, cv::THRESH_BINARY, 11, 3);
		//adaptiveThreshold(Grey2, ThreshImg2, 230, cv::THRESH_BINARY_INV, cv::THRESH_BINARY, 11, 3);
		//adaptiveThreshold(Pic2, ThreshImg2, 230, cv::THRESH_BINARY_INV, cv::THRESH_BINARY, 11, 3);
		//adaptiveThreshold(Pic, ThreshImg2, 230, cv::THRESH_BINARY_INV, cv::THRESH_BINARY, 11, 3);
		//adaptiveThreshold(Pic, ThreshImg, 230, cv::THRESH_BINARY_INV, cv::THRESH_BINARY, 11, 3);
		break;
	}

	}

	//cv::imwrite(Out + "Thresh6.png", ThreshImg2);
	cv::imwrite(Out + "Thresh6.png", ThreshImg);


	/**https://docs.opencv.org/master/d3/dc0/group__imgproc__shape.html#gadf1ad6a0b82947fa1fe3c3d497f260e0
		https://docs.opencv.org/master/d3/dc0/group__imgproc__shape.html#ga0012a5fdaea70b8a9970165d98722b4c
	/* https://docs.opencv.org/master/d6/d6e/group__imgproc__draw.html#ga746c0625f1781f1ffc9056259103edbc


	/**Usefull for detecting closed contours in a given Bitmap
	Only can reliably find contours with extremely high contrast e.g. Black on White)*/
	//cv::findContours(ThreshImg2, Contour, Vec4, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

	printf("Find Contours");
	cv::findContours(ThreshImg, Contour, Vec4, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);


	cv::Scalar clr = cv::Scalar(std::rand() % 255 + 1, std::rand() % 255 + 1, std::rand() % 255 + 1);
	//for (i = Vec4[i][0]; i < Contour.size(); i++) /* Arc length s usefull for detecting closed contours in a given Bitmap*/
	//cout << "Size:" << Vec4[0][0];

	ContourApx = Contour;
	int cnt = 0;

	QVERIFY(UT2.nullCheck(ContourApx.size()));


	printf("%zi, \n", Vec4.size());
	float Max;// = Vec4.size();
	float at;// = Vec4[i][0];
	v, i = 0;
	//v, i = tx;

	printf("%i \n", Vec4.size());

	/*Potential for concurrency/mutlthreading as the Vec4 vector array can be theoretically split into seperate stacks 
	equal to the number of threads specified/configured: eiher at runtime or via a user=specified/configured config Variable*/

	/*time_t a = _getsystime();
	tm aa = ;*/

	//std::chrono::steady_clock< std::chrono::nanoseconds>  a ;
	//std::chrono::steady_clock a ;
	//std::chrono::high_resolution_clock a ;
	//std::chrono::high_resolution_clock a, b ;
	//std::chrono::high_resolution_clock a;
	////std::chrono::high_resolution_clock b ;
	//std::chrono::nanoseconds  b ;
	////std::chrono::duration < std::chrono::high_resolution_clock, std::chrono::nanoseconds> dr;
	////std::chrono::duration < std::chrono::high_resolution_clock, std::chrono::nanoseconds> dr;
	//std::chrono::duration < std::chrono::high_resolution_clock, std::chrono::nanoseconds> dr;
	//dr.count();
	//dr.
	//a.now();
	/*std::chrono::nanoseconds < std::chrono::time_point > a =
		std::chrono::high_resolution_clock hc;*/

	//cout << "Using: " << Sel << endl;
	for (; i >= 0; i = Vec4[i][0])
	//for (; i >= tx; i = Vec4[i][0])
	{
		//float Prcnt = 100.f / (Vec4.size() / Vec4[i][0]);
		Max = Vec4.size();
		at = Vec4[i][0];
		Prcnt2 = 100.f / (Max / at); //cant be set as ponter/reserved Mem Adderss to allow 2Syncing" with same name variable in the man QApp Class.....

		//qDebug() << "------------->" << Prcnt2;
		printf("%s %f \n", "---------->", Prcnt2);
		printf("%i \n", i);
		/*printf("%i \n", Vec4.size());*/
		//Prc

		//QB->setValue(Prcnt);

		/** this will likley slow down the Contour Draws by calling RNG functions all the time */
		clr = cv::Scalar(std::rand() % 255 + 1, std::rand() % 255 + 1, std::rand() % 255 + 1);
		//clr = cv::Scalar(255, 255, 255);


		/**very important for Edge detection: Approximates via polygonal Approximation, which greately reduces the chance of very small imperfections
		in the geometry being returned as invalid sides */

		cv::approxPolyDP(Contour[i], ContourApx[i], .00625 * cv::arcLength(Contour[i], true), true);
		//cv::approxPolyDP(Contour[i], ContourApx.mAddrItem(i), .00625*cv::arcLength(Contour[i], true), true);
	   //cv::approxPolyDP(Contour[i], ContourApx[i], .0125 * cv::arcLength(Contour[i], true), true);
	   //cv::approxPolyDP(Contour[i], ContourApx[i], .0250*cv::arcLength(Contour[i], true), true);

		
	   /*cout << "Detected: " << v << endl;
		cout << ContourApx[i].size() << endl;
		cout << ContourApx[i] << endl;*/

		
		//qDebug() << "Detected: " << v;
		//qDebug() << ContourApx[i].size();
		////qDebug() << ContourApx[i];

		/** Lots of ugly branching/Cache Misses here: likely main culprit for slow Drawing*/
		/* Should ideally be on its own thread to stop the UI thread stalling*/
		//printf("%i, \n", v);
		/*switch (Sel)
		{
		case 0: {*/
			//cv::drawContours(Pic2, ContourApx, i, clr, 1, 1, Vec4);
			//cv::drawContours(Pic.colRange(100,200), ContourApx, i, clr, 1, 1, Vec4);
			cv::drawContours(Pic, ContourApx, i, clr, 1, 1, Vec4/*[i][0]*/);
			//if (ContourApx[i].size() == 4) {
			//	//cv::drawContours(Pic, ContourApx, i, clr, 1, 1, Vec4/*[i][0]*/);
			//	putText(Pic, "<-Quad" + std::to_string(v), Contour[i][0], cv::FONT_HERSHEY_COMPLEX, 0.5, clr, 1);
				putText(Pic, "Num:->" + std::to_string(ContourApx[i].size()), Contour[i][0], cv::FONT_HERSHEY_COMPLEX, 0.5, clr, 1);

			//}
			//else if (ContourApx[i].size() == 3) {
			//	//cv::drawContours(Pic, ContourApx, i, clr, 1, 1, Vec4/*[i][0]*/);
			//	putText(Pic, "<-Tri" + std::to_string(cnt), Contour[i][0], cv::FONT_HERSHEY_COMPLEX, 0.5, clr, 1);
			//}
			//else if (ContourApx[i].size() == 5) {
			//	//cv::drawContours(Pic, ContourApx, i, clr, 1, 1, Vec4/*[i][0]*/);
			//	putText(Pic, "<-Pentagon" + std::to_string(cnt), Contour[i][0], cv::FONT_HERSHEY_COMPLEX, 0.5, clr, 1);
			//}
			//else if (ContourApx[i].size() == 8) {
			//	//cv::drawContours(Pic, ContourApx, i, clr, 1, 1, Vec4/*[i][0]*/);
			//	putText(Pic, "<-8-Poly" + std::to_string(cnt), Contour[i][0], cv::FONT_HERSHEY_COMPLEX, 0.5, clr, 1);
			//}
			//else {
			//	//cv::drawContours(Pic, ContourApx, i, clr, 1, 1, Vec4/*[i][0]*/);
			//	putText(Pic, "<-------Misc: " + std::to_string(ContourApx[i].size()) + std::to_string(cnt), Contour[i][0], cv::FONT_HERSHEY_COMPLEX, 0.5, clr, 1);
			//} v++;
		//	break;
		//}
		//case 1: {
		//	/*Could use a workaround with Circles to disable ApproxPolyDB just for handling circles to allow the parabolic
		//	geometry to be more easily approximated/Detected with Canny Edge based Algorhythmns*/
		//	v++;
		//	break;
		//}

		//case 2: {
		//	if (ContourApx[i].size() == 3)
		//	{
		//		cv::Point P1(ContourApx[i][0]);
		//		cv::Point P2(ContourApx[i][1]);

		//		double Angle = atan2((P1.y - P2.y), (P1.x - P2.x)) * 180. / CV_PI;
		//		double Angle2 = atan2((P1.x - P2.y), (P1.x - P2.y)) * 180. / CV_PI;

		//		cout << "Width" << P1 << endl;
		//		cout << "Height" << P2 << endl;
		//		cout << "Angle" << Angle << endl;
		//		cout << "Angle2" << Angle2 << endl;

		//		cv::drawContours(Pic, ContourApx, i, clr, 1, 1, Vec4/*[i][0]*/);
		//		putText(Pic, "<-Tri" + std::to_string(cnt), Contour[i][0], cv::FONT_HERSHEY_COMPLEX, 0.5, clr, 1);
		//		v++;
		//	}
		//	break;
		//}
		//case 3: {
		//	if (ContourApx[i].size() == 4)
		//	{

		//		/**Could simplfy this into a method call to tidy this syntax up*/

		//		cv::Point P1(ContourApx[i][0]);
		//		cv::Point P2(ContourApx[i][1]);
		//		cv::Point P3(ContourApx[i][2]);
		//		cv::Point P4(ContourApx[i][3]);

		//		//https://docs.opencv.org/master/db/de0/group__core__utils.html#ga7b356498dd314380a0c386b059852270
		//		double Angle5 = cv::fastAtan2((P1.y - P2.y), (P1.x - P2.x));// *180. / CV_PI;
		//		double Angle6 = cv::fastAtan2((P2.y - P3.y), (P2.x - P3.x));// *180. / CV_PI;
		//		double Angle7 = cv::fastAtan2((P3.y - P4.y), (P3.x - P4.x));// *180. / CV_PI;
		//		double Angle8 = cv::fastAtan2((P4.y - P1.y), (P4.x - P1.x));// *180. / CV_PI;

		//		cout << "Angle5: " << Angle5 << endl;
		//		cout << "Angle6: " << Angle6 << endl;
		//		cout << "Angle7: " << Angle7 << endl;
		//		cout << "Angle8: " << Angle8 << endl;
		//		cout << (Angle6 - Angle5) << endl;
		//		cout << std::fmodl(Angle6, Angle5) << endl;
		//		if ((Angle6 - Angle5) == 90. || std::ceil(std::fmod(Angle6, Angle5)) == 90.)
		//			//if (std::fmodl(Angle6, Angle5) == 90.)
		//		{
		//			cout << "true" << endl;
		//			cv::drawContours(Pic, ContourApx, i, clr, 1, 1, Vec4/*[i][0]*/);
		//			putText(Pic, "<-Quad" + std::to_string(v), Contour[i][0], cv::FONT_HERSHEY_COMPLEX, 0.5, clr, 1);
		//		}

		//		v++;
		//	}
		//	break;
		//}
		//case 4: {
		//	if (ContourApx[i].size() == 5)
		//	{

		//		/**Could simplfy this into a method call to tidy this syntax up*/
		//		cv::drawContours(Pic, ContourApx, i, clr, 1, 1, Vec4/*[i][0]*/);
		//		putText(Pic, "<-Pentagons" + std::to_string(v), Contour[i][0], cv::FONT_HERSHEY_COMPLEX, 0.5, clr, 1);
		//		v++;
		//	}
		//	break;
		//}
		//case 5: {
		//	if (ContourApx[i].size() == Sel + 3)
		//	{
		//		cv::drawContours(Pic, ContourApx, i, clr, 1, 1, Vec4/*[i][0]*/);
		//		putText(Pic, "<-8-Poly" + std::to_string(cnt), Contour[i][0], cv::FONT_HERSHEY_COMPLEX, 0.5, clr, 1);
		//		v++;
		//	}
		//	break;
		//}
		}
		//b.now();

		

		//printf("%zi", dr);
		//b =  b - int(a);
		//uint64_t c = (a, b)
		//uint64_t c = dr(a, b);
		//printf("%s %d, %d","Time: ", a, b);
		//printf("%s %zi, %zi","Time: ", a, b);
		//qDebug() << std::chrono::nanoseconds(a);
		//printf("%s %d," "Time: ", dr);
	
	//QB->reset();
	//* Update Progress Bar percentage completion*/
	//QB->setValue(100);
	//QB.setValue(100);

	/**Consider a conntection here to force the QPainter to update/render the Output Bitmap.......*/
	/*printf("%i %s \n", v, " Contours");
	printf("%i %s \n", cnt, " Convex Contours");*/
	//cv::imwrite(Out + "cvOut.png", Pic2);
	cv::imwrite(Out + "cvOut.png", Pic);

	//isbusy = false;
	//emit(this->isFinished());
	//this->exit();

};