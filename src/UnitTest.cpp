#include "UnitTest.h"

//**Ignore the False positive errors as this compiles correctly with the UnitTest header included in this way*/


void UnitTest::init()
{
	qDebug("Testing....");
}


/**Check file path of image bitmap file actually exists */
bool UnitTest::checkPaths(QFile x)
{
	//testCase.x = testCase.SetPath("E:\Project\SOFT20091 - SDI\Imgs\AntiAliasTest1.png");
	//TestA = 5;
	//testCase.SetTest(TestA);
	
	//QVERIFY2(x.exists(), "Bad/Invalid Path!: File Not found");

	if (x.exists())
		return true;
	else
	{
		printf("Bad/Invalid Path!: File Not found \n");
		return false;
	}
		


	 
}

/**Check that File format is a valid Bitmap: may not handle some more obscure/Specialised extensions 
so OpenCV may likley be handle to handle more than this*/
bool UnitTest::checkFileFormats(QFileInfo y)
{
	
	
	if (y.suffix() == "png" || 
		y.suffix() == "jpg" || 
		y.suffix() == "tga" || 
		y.suffix() == "tiff"|| 
		y.suffix() == "bmp" || 
		y.suffix() == "arw" ||
		y.suffix() == "webp")
	{
		return true;
	}
	else
	{
		printf("Bad, Unknown, or Invalid File! ");
		qDebug() << y.suffix();
		return false;
	}
}

/** Very simple Null check for Vector and lists*/
bool UnitTest::nullCheck(int l)
{
	if (l > 0)
		return true;
	else
	{
		printf("Provided Structure is NULL or too short! ");
		printf("%i", l);
		printf("\n");
		return false;
	}
}