#include <QApplication>


#include <QtCore>
//#include <type_traits>
//#include "mItemList.h"
#include "QApp.h"
//#include <opencv2/core/utility.hpp>

//using namespace cv;

/** Main function from which all other Interface constructors and objects are called **/
int main(int argc, char** argv)
{
	std::ios_base::sync_with_stdio(false);
	QApplication xapps(argc, argv);

	/**Instanciate the main QAPP class*/
	QAPP QA(argc, argv);
	//cv::CommandLineParser parser(argc, argv,

	/**Instantiate the child QListView widget: 
	This is called from the main function/class as other widgets can't seem to be called reliably from other classes  
	as they are not visible to the QApplictaion constructor
	There is likely a more optimal method of handling this, although this was the only reliable workaround found to handle instantiation properly**/

	QA.SetupView(); 
	//QA.DebugMode();


	return xapps.exec();
}
