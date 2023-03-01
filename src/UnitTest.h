#pragma once
#include <QTest>

//*Ignore the include errors if they occur as they are a false positive and the QTest header QVERIFY macros can be compiled properly*/


//using std::vector;

class UnitTest: public QObject
{
	Q_OBJECT
private:

	//QAPP testCase;

	const int TestA = 0;

	//QString Path;

	//testCase::x
	
	//void UTcheckIndexIsValid(const QModelIndex& index);
	//int aCheck(int x);
	/*void checkContourSize(int a)
	{
		Q_ASSERT(a > 0);
	}
	bool checkCondition()
	{
		return true;
	}*/

public:

	bool ImageProcessPassed;

	bool FileTypeIsValid;

	bool WorkingEnvironmentSuccess;

	bool CheckDependenciesValid;

	bool checkPaths(QFile x);

	bool checkFileFormats(QFileInfo y);

	bool nullCheck(int l);


private slots:
	
	void initTestCase()
	{
		qDebug("Initialising tests....");
	}
	
	void init();

	
	
	
	//{
	//	//if (Q_ASSERT(x.exists()) == true);
	//	//QVERIFY2(x.exists(), "Bad/Invalid Path!: File Not found");
	//	//if (!x.exists())
	//		/*return false;
	//	else
	//		return true;*/
	//		//printf("Bad or Non-Existant Path!");
	//		
	//}

	void cleanup()
		{
			qDebug("Cleaning up.....");
		}

	void cleanupTestCase()
	{
		qDebug("Tests Completed");
	}

	

	//{
	//	/*return true;*/
	//}
	/*{
		return x;
	}*/

	

};
