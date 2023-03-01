//#include <QApplication>

//#include "ParseImg.h"

//#include <stddef.h>
//#include <cstddef>
//#include <windows.h>

//#include "CustomItemListModel.h"
//#include "CustomItemGridModel.h"
//#include <QtTest/QtTest>
//#include "UnitTest.h"
//#include "mItemList.h"
//#include "ImageHandler.h"

//#include <opencv2/core/mat.hpp>
//#include <opencv2/core/cuda.inl.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/objdetect.hpp>
//#include <opencv2/core/utility.hpp>

//#include <qplugin.h>
//#include <opencv2/c>
//#include <iostream>

#include "QApp.h"


//#include <thread>

//#include "UnitTest.cpp"
//using namespace UnitTest;


/** Ignore the identification errors with the QVERIFY macro as the QTest header does not need to be included manually to be accessible and still compiles correctly with MSVC*/

/**the Mian QAPP header is also increadibly large due to the limitaions of Qt Signals and Slots, 
preventing the ability to update variables and GUI elements from another seperate class without extensive workarounds, 
forcing much of the Application logic and handling into one file*/

//namespaces seem to be very inconsistant with the MOC implemented by Qt when 'sharing' variables of a namespace in separate functions
//using namespace cv;


//using std::cout;
//using std::endl;



UnitTest UT;


QCursor QC;

ParseImg PI;

QThread Thr;

//std::ofstream OutFile("test.txt", std::ofstream::out);
//std::ofstream OutFile;
/** Initial Method to Instantiate the Main Application Widget */
QAPP::QAPP(int argc, char** argv, QWidget* parent/*, QTabWidget TabParent*/) : QSplitter(parent)/* , QThread(parent)*/
{
	//std::ios_base::sync_with_stdio(false);
	//TestWidget = new QWidget(this); /** Imbedded widget to allow more precision over Button and object placement */
	//not sure if additional Widget types inheriting fro QWidget>QObject should have and additional contructor argument (may not be optinal to initalse addiitonal QWidget type without adiitonal Conrtuctor argument...., alugth teh conrtuctor sued the rpeset/default parent vraible for the mian encasulating Qwidget class fpr thall addiitonal Qidhetsg to be tarted theerfore as 'chi;dren; of teh absolute overaching QSplitter clas obejct or '[arent'
	TestWidgetTabSet = new QTabWidget(this);
	TestWidget = new QTabWidget(this); /** Imbedded widget to allow more precision over Button and object placement */
	//setFixedSize(1280, 720);
	//TestWidget->setFixedSize(500, 500);
	TestWidget->setMinimumSize(500, 500);
	//QPainter QP(this); //Apparently Begin does not need to be called if the QPainter is already initialised to a specific/given context....
	QImage QI;

	//ParseImg PI;

	//PI = new QThread(this);
	//PI = new ParseImg(this);

	OptionSet = new QWidget(this);

	/*TestWidgetTabSet->addTab(TestWidget, "TestWidgetMain");
	TestWidgetTabSet->addTab(OptionSet, "OptionSets");*/

	/** Placeed button within the "Parent" QWidget 
	Must include this to ensure Button is placed correctly within the QWidget and not as a seperate QObject!*/
	Iargc = argc;
	Iargv = argv;
	Exit = new QPushButton(TestWidget);

	Exit->setGeometry(50, 100, 300, 30);
	{
		Exit->setText("Exit");
		//connect(QAPP::Exit, &QPushButton::clicked, this->isActive(), &QAPP::CloseMain);
		connect(QAPP::Exit, &QPushButton::clicked, this, &QAPP::CloseMain);
	}
	QB = new QProgressBar(TestWidget);

	QB->setGeometry(200, 200, 100, 20);
	QB->setMinimum(0.f);
	QB->setMaximum(100.f);

	//QTabBar

	//QFileInfoList
	ThreshOpt = new QCheckBox("Use Adaptive Thresholding", TestWidget);
	ThreshOpt->setGeometry(200, 300, 160, 16);
	//ThreshOpt->setText("Add User Toggles!");
	ThreshOpt->text();
	//ThreshOpt->graphicsEffect();

	//use soecial shader efefcts to frflect the variable chnages (e.g. change colour as the dial is adhusted and based on teh variable size/value
	QS = new QSlider(Qt::Horizontal, OptionSet);
	QS->setGeometry(100, 200, 100, 50);
	//QS->moveToThread
	

	insertWidget(2, TestWidget);
	//QAPP::show();
}

/** Experiment to setup TreeView As a child widget as a workaround/bypass for the connection problem where Signals/Slots cannot be made between different classes of QObject**/
/** Slots may not be able to call other Objects **/
/** This should be its own class and not as a member function of the main QAPP class: but allows full Connection functionality to be achieved in this way **/
void QAPP::SetupView()
{
	/* Use pointer trick with push buttons to allow Widgets to be embedded: **/
	isbusy = true;
	FileTree = new CustomListView(TestWidget); /** currently considering to refactor this into a QListView for simplistity and poentially improved interfacing with the QList */
	FileTree->setMinimumSize(300, 400);
	FileTree->setGeometry(100, 200, 10, 20);
	
	/* Allows the QPushButton to be added to the TreeView even though it technically belongs to the Main QAPP header */
	AnalyseImg = new QPushButton(TestWidget);

	Sort = new QPushButton(TestWidget);
	
	AddObj = new QPushButton(TestWidget);
	
	SaveFile = new QPushButton(SaveFile);
	
	SaveFile->setGeometry(10, 10, 380, 50);
	Sort->setGeometry(10, 400, 190, 50);
	Sort->setText("Sort This");
	
	AnalyseImg->setGeometry(210, 400, 190, 50);

	AnalyseImg->setText("Parse Image");

	AddObj->setGeometry(210, 200, 190, 50);

	AddObj->setText("Add Object");
	
	SaveFile->setText("Save File"); //->+ObjectTemplateSet
	
	/*Newer syntax of Pointers required to access inherited slots from QAbstractItemModel
	Don't need to pass parameters to the called signal/slot with this special pointer.reference method */
	/**Must have QObjects as pointers otherwise connection methods cannot be accessed correctly**/

	/**Get index of ItemModel to return Filename*/
	connect(FileTree, &CustomListView::doubleClicked, this, &QAPP::Filehandler); /**https://doc.qt.io/qt-5/qabstractitemview.html#mouseDoubleClickEvent*/
	connect(Sort, &QPushButton::clicked, this, &QAPP::RefreshTree);
	connect(ThreshOpt, &QCheckBox::stateChanged, this, &QAPP::updateSet);
	//connect(AnalyseImg, &QPushButton::clicked, this, &QAPP::ParseImg);
	connect(AnalyseImg, &QPushButton::clicked, this, &QAPP::ThreadHelper);
	connect(AddObj, &QPushButton::clicked, this, &QAPP::AddRowObject);
	//emit on_opened_state();
	//connect(QC, &QCursor::, this, &QAPP::MouseHandler);

	/* Could be its own Function in theory for better degree of refactoring */
	/* error handling here if QList length and actual Directory contents do not match/Desync */

	//Possible problems here as these methods are likely not been called in a very clean/stable/optimal way
	ClassList = new CustomListView(this);

	ClassPicker();
	instantiateTree();
	OpenedDir();
	//SetupViewPort();
	
	qDebug() << A->rowCount();
	qDebug() << A->columnCount();
	//addWidget(FileTree);
	//addWidget(TestWidget3);
	//Must be nstanciated added later to teh Qtab widget otherwise teh QObejct will not be opulated proeprly as they have not themslevs been initialised fully yet e.....
	TestWidgetTabSet->addTab(TestWidget, "TestWidgetMain");
	TestWidgetTabSet->addTab(OptionSet, "OptionSets");
	//QPainter QP(this);
	QAPP::show();

	//FileTree->show();
	isbusy = false;
}

/** Constructs the Image File list to be Represented in the ItemListModel*/
void QAPP::instantiateTree()
{
	qDebug("Appending Index List");
	QDirIterator It(ImgPath, /*QList<QString>(),*/ QDirIterator::NoIteratorFlags); //https://doc.qt.io/qt-5/qdiriterator.html#next
	/**Skip/Remove the Garbage null entries/FolderNames QDirIterater adds when Recursing the Specified/target Directory*/

	It.next();
	It.next();

	while (It.hasNext())
	{
		
		//InputImages.append(QString(It.next()));
		It.next();
		InputImages.append(QString(It.fileName()));
		
		//*Usage of Custom linked List Object here, may not behave as expected
		//InputImages.mCreateItem(QString(It.fileName()));
		

		qDebug() << It.fileName();// << It.fileInfo().size();

		//https://doc.qt.io/qt-5/qfileinfo.html#size
		//https://doc.qt.io/qt-5/qmap.html#insert-1
		
	}

	SortSet();
	
	//A = new CustomItemListModel(ImgNames);
	//A = new CustomItemListModelv2(ImgNames);

	//QVERIFY(UT.nullCheck(InputImages.size()));

	A = new CustomItemListModelv2(InputImages, QString("Items"));

	qDebug() << "Role:" << A->roleNames();
	FileTree->setModel(A);

}

/**
	This cannot be called a true sort by any means:
	as it only provides the illusion of sorting by exploiting windows file explorer's default Asc sort,
	and instead of actually sorting the provided List only reverses the order to provide Asc/Desc Functionality

*/

void QAPP::SortSet()
{

	switch (SortType) //may have slightly improved performance overhead compaired to If control structure/statement
	{
		default: 1;
		{

			//retain default orientation method, which is Asc based on how the NTFS table is oriented for the Img Working Directory
			qDebug("No Sort Alteration: Retain current List as unmodified");
			SortType = 2;
			break;
		}
		case 2:
		{
			for (int i = 0; i < InputImages.size() - 1; i++)
			{
				//InputImages.swap(i + 1, i);
				InputImages.move(InputImages.size() - 1, i);
			}
			SortType = 1;
		
			break;
		
		}
	}
}

/**
	Crude method of deleting the list before rebuilding it again as an easy method of allowing updates;
	will likley have a large performance overhead compared to more efficent methods such as only reading
	to the list during updates and sorts instead of needless deletions/
*/
void QAPP::RefreshTree(/*QModelIndex Index*/)
{

	
	InputImages.clear();

	//InputImages.dropNode(InputImages.GetHead()->xnext);
	//InputImages.dropAll();
	//InputImages.showAll();
	//ImgNames.clear();
	//SortType = 4;

	/*SortSet();*/
	instantiateTree();
	FileTree->update();
}

void QAPP::updateSet()
{
	if (ThreshOpt->checkState() == Qt::Checked)
	{
		setThresh = true;
		qDebug() << "Set" << setThresh;
	}
	if (ThreshOpt->checkState() == Qt::Unchecked)
	{
		setThresh = false;
		qDebug() << "Set" << setThresh;
	}
}

void QAPP::ClassPicker()
{
	//ClassList = new CustomListView(this);

	//connect(ClassList, &QListView::doubleClicked, this, QModelIndex::internalId);
	//Sel = 0;
	//Must be Positioned Here as otherwise the Shape type/Mode isn't updated properly
	connect(ClassList, &CustomListView::doubleClicked, this, &QAPP::SetShape);

	//Template here....*/
	//B = new CustomItemListModelv2(aClass, QString("ShapeSets"));
	/** *Adding a dedicated Widget for handling Obejct renaming may involved too compelx hadling so instead opeted for editable ItemListModel instead*/
	B = new QStringListModel(aClass);
	ClassList->setModel(B);
	ClassList->setFixedSize(150, 200);
	insertWidget(3, ClassList);
	ClassList->show();


}

//void QAPP::run()
//{
//	ParseImg();
//	qDebug("Finishing Thread");
//}


void QAPP::SetShape(QModelIndex index)
{
	Sel = index.row();
	aClass[Sel] = index.data().toString();
	qDebug() << "Set" << Sel;
	qDebug() << "Set" << aClass[Sel];
	AnalyseImg->setText("Parse Image (" + aClass[Sel] + ")");
	//->** Coudl save the vector list here - OAnd.or Replace it with LL but that is likely for later....*/
	//eventHandler(QE);
	 xFile = aClass.at(Sel);// +".txt";
	//xFile + ".txt";
	//SavePath = QDir::currentPath() + "/Annotations/" + xFile + "/Test.txt";
	//NameFile = (SavePath);
	//qDebug() << SavePath;
	/*SavePath2 = QDir::toNativeSeparators(QDir::currentPath() + "/Annotations/" + xFile + "/Test.txt");
	qDebug() << SavePath2;
	SavePath = SavePath2.toStdString();*/
	//SavePath = xFile.toStdString()+ ".txt";
	//cout << SavePath << endl;
	//std::ofstream OutFile("test.txt", std::ofstream::out);
	//std::ofstream OutFile(SavePath, std::ofstream::out);
	//OutFile.open(NameFile);
	
}

void QAPP::AddRowObject()
{
	
	//Set Update trigger to chave changed Index name permiently
	//v++;
	//aClass.push_back(QString(v));

	/**https://stackoverflow.com/questions/37412712/how-to-update-a-qstringlistmodel */
	//B->dataChanged(aClass.length()-1, aClass[v]);
	if (B->insertRow(B->rowCount())) 
	{
		QModelIndex index = B->index(B->rowCount() - 1, 0);
		B->setData(index, "Add Object");
		aClass.push_back(QString("Add Object"));
	}
	//B->setData()
	//ClassPicker();
}

/** Triggered when ListView is Opened*/
void QAPP::OpenedDir()
{
	qDebug() << "Opened: " << ImgPath << endl;
	//addWidget(FileTree);
	insertWidget(1, FileTree);
	FileTree->show();
	//isbusy = true;
	//setMinimumSize(1000, 800); /** overridden by QSplitterClass as it only resizes for a split second*//
	//AddImgs->setText("Opened");
	//Add->setText("Close");
	SetupViewPort();
	//hide();
}


/** Experimental Slot for handling and passing information derived from the ModelIndex:
	this may be a good option for a future method of handling/passing file information to external methods */
void QAPP::Filehandler(QModelIndex Index)
{
	//AddImgs->setText("Clicked Item");
	qDebug() << Index.column();
	qDebug() << Index.data();
	qDebug() << "Row" << Index.row();
	/** hacky method to get the Current Index passed to this specific slot where the Selected File now becomes the corrisponding Index of the InputImages QList */

	//V = InputImages.at(Index.row());
	//V = ImgPath + InputImages.mAddrItem(Index.row());
	
	//Appending the File name to the Working Img Folder path effectively bypasses the need to use/synchronise an additional list 
	FileFile = InputImages.at(Index.row());
	AsFile = AnotPath + FileFile;
	//AsFile = AnotPath + FileFile.toStdString();
	//std::string FileFile = InputImages.at(Index.row())

	//e.g.: todo: Might be possible to setup a profiling set heer to show ten to,e taken to initialise/render the Bitmap.....
	V = ImgPath + InputImages.at(Index.row());
	/*Moving the QPixmap Definitial/Declaration/Initialisation to a member method/function that is only fised/troggered/called 
	occasionally. such as when the suer lciks/interatcs with the ItemListModel,  
	solves/ resolves/fixes the perfoamnce issue with QPIxmap Large resolutions as the QPixmap is not being redelcaired 
	continuously/constantly every time the QPiant Event is called/ handled by teh veent handler, 
	whcih gerately Reduces the CPu overhead when darwing/Rednering the Image/QPIxmap through.Via QPainter*/
	Qimg = V;
	//additional potential optimisation to move the Image Sclaing heer as it shoudl also only be called/handled once when the ItemVuewModel entry representing the Bitmap file is (via user-Based Interaction) clicked
	/*if (Qimg.size().height() > 1440. || Qimg.size().width() > 2560.)
	{
		ScaleFactor = 4.;
		TestWidget3->setFixedSize(Qimg.size() / ScaleFactor);
	}

	/*else *///if (Qimg.size().height() > 720. || Qimg.size().width() > 1280.)
	//{*/
		//TestWidget3->updateGeometry();
		/** setup is flawed as cannot select subPixel/Pixel-Based precision beloew the scale factor, so rects that are not divisible by the scale sactor cannot be selected
		May be posible to fix this my using floats for Enhanced Sub)facle fatcor precision (e.g. inclrementing by 0.5 instead of 1 for Scale factor of 2 or 1/ ScaleFactor*/
		//ScaleFactor = 2.;
		//Discovered/relaised that it could be posisble to dicirn teh Scalefactor by only dividing the Pixmap Res by the desired 'base' canvas/ resolution size to scale to the desired size on the ViewPort - (alss erves as potential optimistaion by reducing teh redired condition(Als) or seperate distinct if Statements to check for as it is no longer nessacery to utilsie multiple IF statements to check for all/any posisble resolutions to Scale to/From)
		//This also ahs teh ability to potentially /Dynamically scale to any ossibel resolution as long as it does nto exceed the pixmapUint16_t limits of 32384 * 32384 
			/*Suggetsions: allow Qpainter to be 'scrollable' so teh rendered bitmap can be scrolled to ensure that thin or narow[er] images do not become too small (wheras they fit in the Horizontal res but not the Vertical res and has to be scaled just because it does not fit into the aspect ratio properly)
				Allow the image to be 'Zoomed' into witha htkey or mosue button rpess to allow high resolution images to be zoomed into and to allow crop regions to be selected with fukl per pixel rpecision without losing precision due to teh Scalefactor (e.g. ScaleFatcor 3 canses crop regions to only be selected per 3 Pixels/or must be divisable by 3)
					(Similar to the Zoom  Function With FastStone ImageViewer*/
		ScaleFactor = ((Qimg.width()/1280.)+(Qimg.height()/720.))/2.;
		//ScaleFactor = roundf(ScaleFactor); //Round SclaFatcor float to nearest Value/Int to rpevent awkward scaling with Non-integer scales (uneven pixellation0 and the Crop-Select region being evaluated/inistalised as floats/Non_integers which may cause issues with precision loss/Invalid valeus with the crop selection/Region
		qDebug() << "Actual ScaleFactor" << ScaleFactor;
		ScaleFactor = ceil(ScaleFactor); //Round SclaFatcor float to nearest Value/Int to rpevent awkward scaling with Non-integer scales (uneven pixellation0 and the Crop-Select region being evaluated/inistalised as floats/Non_integers which may cause issues with precision loss/Invalid valeus with the crop selection/Region
		TestWidget3->setFixedSize(Qimg.size() / ScaleFactor);
		qDebug() << "Set Scalefactor: " << ScaleFactor;
		qDebug() << Qimg.size();
	/*}
	else
	{*/
		/**Reset Sclae Factor to Default */
		/*ScaleFactor = 1.;
		TestWidget3->setFixedSize(Qimg.size());*/
	//}
	//V = GetPath();
	qDebug("Updating Main Widget!");

	//Dont't seem to ned to update the Qpainter Qidget manually anymroe as due to the new Scafatco handling for the Qpainer  and.or the Qpainter initialisation/Handling now being ots own event handler rather tahn being handling within the initial genral Event hanlder
	//this->update(); //* Updates the Main widget so the paintevent for the image is triggered properly to help fix image distortion/placemnt bugs/issues */

}

void QAPP::ThreadHelper()
{
	//std::thread Thr (&QAPP::ParseImg);
	//std::thread Thr (&ParseImg);
	//std::thread Thr;
	//Thr (&QAPP::ParseImg)
	//std::thread Thr (&QAPP::ParseImg, this);
	//QThread Thr(&QAPP::ParseImg)
	//PI.run();
	//PI.ParseImg2(*V); //More ponetial berakage; usinga pointer to allocate/reserve a memeory adress(es) to allow the Paramater/argument to be defined later
	//PI.ParseImg2(V, setThresh); //More ponetial berakage; usinga pointer to allocate/reserve a memeory adress(es) to allow the Paramater/argument to be defined later
	PI.getParams(V, setThresh); //proive/Set teh image Path anf the Thersh methdo to the ParseImg Thread: likely mroe ffective to simply construct the ParseImg Therad-based clas with tehse isnetad but this work suprisingly reliable for now.....
	//PI.getCoord(xx * ScaleFactor, yy * ScaleFactor);
	//PI.getCoord(xx * ScaleFactor, xy.y());

	//Pass SpecificRange coords pased on the Reagon /crop selected with MouseMove
	PI.getCoord(xy.x()*ScaleFactor, xx * ScaleFactor, xy.y()*ScaleFactor, yy * ScaleFactor);
	PI.start(); //Start Image Parsing Thread: thi sshoudl eb called isnetad of dierctlya ccesing the ParseImg function fro here as it will be executed by the mian Ui thread instead!
	//Also if this fuctions si not usitilsied it cannot be considered as atrue.seperate therad att alla nd will not use any of the i herited Qtherad based functionality an dtheerfor will still stall the Ui thread!

	Prcnt = PI.getProgression();

	QB->setValue(Prcnt);

	qDebug() << "--------->*]" << Prcnt;
		
		/*Will nto update properly as there is not currentl knwon methdo to update this/poll this in 
		either an event driven/; or efficent way which avoids stilling this thread again 
		e.g. using a lazy crappy fro loop to pool this methd t update it which will likley stall this thread 
		unless don on another which is likley excesive ad reducenta s there is likely a mroe elegant/simple/effetcive.effcient method instead*/
	//this.Sawa
	//connect(AnalyseImg, &QPushButton::clicked, this, PI.ParseImg2(V, setThresh));
	//connect(AnalyseImg, &QPushButton::clicked, &PI.ParseImg2(V, setThresh));
	//connect(AnalyseImg, &QPushButton::clicked, &ParseImg::ParseImg2);
	//connect(AnalyseImg, &QPushButton::clicked, &ParseImg::ParseImg2(V, setThresh));
	//Thr.create(&ParseImg::ParseImg2);
	
	/*Thr.create(PI.ParseImg2(V, setThresh));
	Thr.start();*/
	
	//connect(AnalyseImg, &QPushButton::clicked, Thr.start());
	//this
	//this->start();
	qDebug("Finishing Thread");
	//delete &Thr;
	//Thr.~thread();
	//ParseImg();
}




/** Instantiates the experimental image viewer for the selected image
The Widget containing the Image viewer FrameBuffer must be active immediately before the Qpainter is called 
as otherwise the QPainter cannot detect the Widget object properly and will therefore lose control of its placement directly in the QSplitter */
void QAPP::SetupViewPort()
{
	TestWidget3 = new QWidget(this);

	TestWidget3->setMouseTracking(true);
	//TestWidget3->setMinimumSize(720, 360);
	//TestWidget3->setMaximumSize(720, 360);
	TestWidget3->setMinimumSize(0, 0);

	//connect(TestWidget3, &QWidget::update, this, &QAPP::MouseHandler);
	//addWidget(TestWidget3);
	//https://doc.qt.io/qt-5.12/qsplitter.html#insertWidget
	insertWidget(0, TestWidget3); //BUG: Cropregion is not caculated repective to the actual pos of the QPainter canvass so if this widgets order is rearrage in the QSplitter (e.g. a higher index so further to teh right, it will still draw the crop region from the left left of the Main/Entire QSPlitter widget instead of the corretc location from the actual mosuepos from the QPainter Canvass
	
	//qDebug() << V;
	//QP->end(); /**calling end here crashes the process */
	qDebug("UpdateViewPort!");
	TestWidget3->show();
}

//void QAPP::eventHandler(QMouseEvent *QVE)
//void TestWidget3
//void QAPP::eventHandler(QEvent* QVE)
//bool QAPP::QMevent(QMouseEvent* QME)

//Added suppot for unqiue/distinct key handling
void QAPP::keyPressEvent(QKeyEvent* QKE)
{
	qDebug() << QKE->key();
	qDebug() << ScaleFactor;
	//float ScaleFactorF = ScaleFactor;
	//if (HoldCtrl = true)
	//This Key handling sucks; may have to sesort using an adiitona keyPress release Event handler just to deal witn resetting the SclaeFatcor properly: (as only one or the other if clases are executed/triggered/Invoked/Conditoned/Condition matched properly e.g.)
	if (Qt::Modifier::CTRL)
	{
		HoldCtrl = true;
		ScaleFactor = 1.;
	}
	if (Qt::Modifier::SHIFT)
	{
		HoldCtrl = false;
		ScaleFactor = 2.;
	}
	//qDebug() << Qt::Modifier()
	/*else
	{
		ScaleFactor = 2.;
		HoldCtrl = false;
	}*/

	//switch (QKE->key())
	//{
	//	case(Qt::CTRL):
	//	{
	//		HoldCtrl = true;

	//		ScaleFactor = 1.;
	//		//TestWidget3->update();
	//		break;
	//	}
	//	default:
	//	{
	//		qDebug() << "Released: " << QKE->key();
	//		break;
	//	}
	//}
	
	//if (Qt::Modifier::SHIFT)
	//{
	//	//attempt to allow teh Cropregion to be slected via 1-1 precision insteapd of per ScaleFatcor precision (allows regiosn nto divasible by ScaleFatcor to be made: intended ot be most usefull for masive Res Bitmaps where regions can only be selected in increments of 4 or even worse e.g.
	//	HoldCtrl = false;
	//	ScaleFactor = ((Qimg.width() / 1280.) + (Qimg.height() / 720.)) / 2.;
	//	ScaleFactor = ScaleFactorF;
	//	//ScaleFactor = 4.f;
	//	//xx = NULL;
	//	//blame my alck of pointerf kowleagde.udnerstanding for this abomination(as it would likley be mroe effeicent/effetcive to use a pointer to store the i nitial Scalefatcpr value to ensure it is reset roperly when teh Ctrl Key is lfted e.g.
	//	//in addiiton this implementation is horibly bugged and does not rset proeprly when teh CTrl key is relased and only when the Bitmap is 'Re-Loaded' either via clicking a VieModel Index/Memebr again to 'relaod' the image or to laod  anew image entirerly: (this causes various issues such a sthe CropSelection rpecision not being reset proeprly and nto atcually refecting the 1-1 pixel precision region and only whenat the intial ScaleFactor precision was anyway
	//	//TestWidget3->repaint();
	//}
	TestWidget3->update();
	qDebug() << "Ctrl: " << HoldCtrl;
	//had to remove the KeyPress handle in the main event hanlder method as it has priority/overrides this event handler. which prevents this event from being called for all events of type WKeypress/QKeyEvent Event

}

void QAPP::mouseMoveEvent(QMouseEvent* evt)
{
	if (QMouseEvent::MouseMove /*&& holdLeft == true*/)
	{
		//qDebug() << "Moved Mou: " << evt->pos();
		xx = evt->pos().x();
		yy = evt->pos().y();
		if (holdLeft == true)
			TestWidget3->repaint();
			//TestWidget3->childrenRegion();
	}
}

//https://doc.qt.io/qt-5/qwidget.html#mousePressEvent
void QAPP::mousePressEvent(QMouseEvent* evt)
{
	qDebug() << evt;
	//qDebug() << this->mousePressEvent(evt);
	/*For some reason must import/include Event header manually */
	//if (evt->button() == Qt::LeftButton)
	/*https://stackoverflow.com/questions/12027656/pointer-to-incomplete-class-type-is-not-allowed*/
	//qDebug() << "Mouse: " << evt->button();
	//evt
	/*xy = evt->pos();*/ //Fixed bug qt event handler where the mouseeent handler would only be truggered if a doube click occured; this was actually due to the QEvent::Mousebuttonpress given priorety over mosueevent which menat it caught the first mousePress every time, with the second being left over to be caught by the mousEvent handler instead: this also rpevented the mousePos fro beign redefined here as the definition in the mian event handler was used instead
	/*Failes to refesh/send an event to the Qpainter to resize the Cropping region; the double Right click actually works in resetting the crop Region but is not reflected in the drawned Rect on the Qpainter canvass/Bitmap As represented */ 
	//Edit* found a ethod call repaint which seems to help as the Qpainter atcually updates teh crop[region now but the region pos is not being calculated corertcltly as it still seems to 'find'the curretnt mosue pos when dblRightClicking  (as teh mosuebuttonclic eent is still being fired/triggered which sets the pos vraibel to teh curerct mosue pos))
	//qDebug() << "QMouseEvent Pos: " << xy;
	/*qDebug() << "------------QMouseEvent Pos: " << evt->pos();*/
	//qDebug() << evt->type();
	//qDebug() << "Local pos: " << evt->localPos();
	//switch (evt->button()) //For some reson if left clik is caught by the mosuEventhanlder and teh Parde Image buton.option is selected, (While a crop region is selected) and a critcial exception will occur.....
	//switch (evt->type()) 
	switch (evt->button())
	{
	case(Qt::LeftButton):
	{
		qDebug() << "Left";
		xy = evt->pos();
		qDebug() << xy;
		holdLeft = true;
		break;
	}
	case(Qt::RightButton): //can't update the main widget parent/Qpainter on its own... not currently posisbel to easily 
	{
		qDebug() << "Right";
		xy = QPoint(NULL, NULL);
		xx = NULL; yy = NULL;
		//emit QEvent::Paint;
		//emit QEvent::UpdateRequest;
		TestWidget3->update();
		//delete xy;
		break;
	}
	/*case(QMouseEvent::MouseMove):
		xx = this->mapFromGlobal(QCursor::pos()).x();
		yy = this->mapFromGlobal(QCursor::pos()).y();
		break;*/
	default:
	{
		//return QSplitter::mousePressEvent(evt);
		qDebug() << "DefaultMouseEvent: No handle";
		break;
	}
	/*switch (evt->localPos())
	{
		case(QMouseEvent::MouseMove):
		{
			qDebug() << "Moved Mou: " << evt->pos();
			break;
		}
	default:
		break;
	}*/
	}
	//if (QMouseEvent::MouseMove)
	/*if (Qt::mous)
	{
		qDebug() << "Moved Mou: " << evt->pos();
		xx = evt->pos().x();
		yy = evt->pos().y();
	}*/
}
//void QAPP::paintEvent(QPaintEvent* pvt)
//{
//	//if(pvt->type() == QEvent::Paint)
//	Qimg = V; //Pixmap seems to have significnatly better performance during reSizes than QImage 
//		//Qimg = V; //Pixmap seems to have significnatly better performance during reSizes than QImage 
//		//Msay be redunant to call /create mu;tpl/redeclaire this Qpainter object which may be adding additional overhead (simialt to teh Qpixmap lag bug where the Qpixamp was being re-initialised multle times in the main event handler
//	QPainter QP(this); //Apparently Begin does not need to be called if the QPainter is already initialised to a specific/given context....
//	qDebug() << pvt;
//	//TestWidget3->setFixedSize(Qimg.size());
//	//Bug: Lag if over certain dimensions
//
//	//-->Perhapes uses a gargBage. lazy hack where ann alternate path could be used based on if  abool has been toggled (Based on key inout) to allow the QPainter to have differently (e.g. Chnage Zoom?ScaleFatcor, Selection?Cropregion SelectioN precision e.g.
//
//	/*Edit: even with Scaling set to 4 for very large images over 1440P the performance issue still persists,
//	even if image scaling is diabled entriely, so is not entriely due to teh phsicla dims/ssize of the Bitmap itself
//	Potentially may be an issue with Pixmap and/or the Qpainter itself
//		Edit: eprfoamnce isue fixed by moving the Qimg declaration to the FileHandler Method which prevents the Qimpg from ebing re-Declaired constantly several tiems a second onetia;ly ever time teh QPaint Event is caucght/handled/Called by teh Main Ui thread (is it actuall the Ui therad that Calles/Hanles the QEvents, at elast Ponetially outside the EvenThandler used/utilsied here...))*/
//		//if (Qimg.size().height() > 1440. || Qimg.size().width() > 2560.)
//		//{
//		//	ScaleFactor = 4.;
//		//	TestWidget3->setFixedSize(Qimg.size() / ScaleFactor);
//		//}
//
//		//else if (Qimg.size().height() > 720. || Qimg.size().width() > 1280.)
//		//{
//		//	//TestWidget3->updateGeometry();
//		//	/** setup is flawed as cannot select subPixel/Pixel-Based precision beloew the scale factor, so rects that are not divisible by the scale sactor cannot be selected
//		//	May be posible to fix this my using floats for Enhanced Sub)facle fatcor precision (e.g. inclrementing by 0.5 instead of 1 for Scale factor of 2 or 1/ ScaleFactor*/
//		//	ScaleFactor = 2.;
//		//	TestWidget3->setFixedSize(Qimg.size() / ScaleFactor);
//		//}
//		//else
//		//{
//		//	/**Reset Sclae Factor to Default */
//		//	ScaleFactor = 1.;
//		//	TestWidget3->setFixedSize(Qimg.size());
//		//}
//		//vertexarray
//		///*QRectF*/ rectangle(xy.x(), xy.y(), xx - xy.x(), yy - xy.y());
//		//Qimg = QPixmap(TestWidget3->geometry(), Qimg);
//		//Qimg.size() /= 2.;
//		//QPixmap qpa = (720., 1280., Qimg);
//		//QPixmap qpa = (Qimg.scaled(1280., 720.));
//		//QP->drawPixmap(TestWidget3->geometry(), Qimg);
//	QP.drawPixmap(TestWidget3->geometry(), Qimg);
//	//QP.drawPixmap(TestWidget3->geometry(), qpa);
//	//QP.drawPixmap(720., 1280., Qimg);
//	//QP.drawEllipse(rectangle);
//	//QP.drawRect(rectangle);
//	QP.drawRect(xy.x(), xy.y(), xx - xy.x(), yy - xy.y());
//	//corrupted/invalid characters
//	//QP.drawText(xy, QString(xx + yy));
//	//QP.drawText(xy, QString(xy.y()));
//	//char as(xx);
//
//	/** cant sem to format ints as chars properly as they are interpeted as ASCII Values which leads to the distorted character bug*/
//	//QP.drawText(xy, tr(&as));
//
//	//Fixed offsetbug when Dispaly is scaled above 16:9 720P Viewport Size/Scaling */
//
//	QP.drawText(xy, QString::number(xx * ScaleFactor - xy.x() * ScaleFactor) + "x" + QString::number(yy * ScaleFactor - xy.y() * ScaleFactor));
//	//QP.drawText(xy, xx);
//	//Also corrupted/invalid characters
//	//QP.drawText(xy, QString(xx) + QString(yy));
//	//QP.drawText(xy, QChar(xx + yy));
//	//QP.drawText(xy, QString(xx));
//
//	//QWidget::event(QVE);
//	/*return true;
//	break;*/
//}

/** 
	Main event handler for this class: is imperative/crucial to ensure that key elements such as the 
	Mouse Button events and Mouse Movements are handled correctly as it allows for the ability for the Ui to respond to certain 
	polled or Queued events which is normally only possible with either a Connection or a Manual update call
	Can be considered as a good alternative to updating the UI manually with Signals 
	or/is vastly more efficent placing crude unthrottled Update calls in the main Widget method
*/
//bool QAPP::event(QEvent* QVE, QMouseEvent* QME)
bool QAPP::event(QEvent* QVE)
{
	//qDebug() << "QOBject Child: " << QObject::children();
	//qDebug() << "QOBject Child: " << QObject::isWidgetType();
	//qDebug() << "QOBject Child: " << QObject::event(QVE);
	//QMouseEvent* QME(QEvent::MouseButtonPress, Qt::MouseButton);
	//QMouseEvent* QME;
	//Qt::MouseButton QA;
	/*QMevent(QA);*/
	//QVE.mou
	//Qt::MouseButton qmb;
	/*use QRegions to dtetced which 'portion' or :region of teh QSPlitter the Mouse is under even if MouseButtoNpress is Engaged: 
	https://doc.qt.io/qt-5/qregion.html#isEmpty*/
	/* May also be posibel to use a method simailr to teh original unthrottled Qiapin.Update() calls (By taking advanatge of scope limitaions where codewithin aspecific memebr function can only be accesed/executed if the  'parent; meebr function itself is called) 
	where the mouse pos is only updated if mosuemove can be called within the Qpaint region*/

	qDebug() << "Event caught" << QVE->type();
	//qDebug() << QVE->registerEventType();
	qDebug() << QVE; 
	//qDebug() << QME;
	/*Qt::MouseButton QA;
	if (QA == 2)
		qDebug() << 2;*/
	//QVE->
	//qDebug() << QME;
	//qDebug() << "Event caught" << this->timerEvent;
	/*qDebug() << *//*QSplitter::mousePressEvent(QME);*/
	/*switch (QA)
	{
		qDebug() << "-----------" << QA;
	case (Qt::MouseButton::LeftButton):
	{
		qDebug() << "Left Button pressed";
	}
	default:
		break;
	}*/
	switch (QVE->type())
	{
		//if (QVE->type() == QEvent::MouseButtonPress)
		//case (QEvent::operator=()
		//case (QME)
	/*case (Qt::MouseButton::LeftButton):
	{
		qDebug() << "Left Button pressed";
	}*/
	/*case (QEvent::MouseButtonDblClick):
		xy = QPoint(110, 220);
		xx = 0;
		break;*/
	/*case (QEvent::GraphicsSceneHoverLeave):
	{
		xx = 0;
	}*/
	/*case (QEvent::ToolTip):
		qDebug() << QEvent::ToolTip;*/
	//case (QEvent::MouseButtonPress):
	////case ()
	//{
	//	//QVE->GrabMouse();
	//	//MouseButtonPress(static_cast<QMouseEvent *>(QVE));
	//	//if (QMouseEvent::)
	//	//if (Qt::MouseButton::LeftButton)
	//	//if (qmb == 1)
	//	//if (qmb == Qt::MouseButton::LeftButton)
	//	//{
	//	//	qDebug() << "Left Button pressed";
	//	//}
	//	//	
	//	////if (Qt::MouseButton::RightButton)
	//	////if (qmb == 2)
	//	//{
	//	//	qDebug() << "Right Button pressed";
	//	//}
	//		
	//	/** Add new Index Member when LCik pos changes*/
	//	/*xy = TestWidget3->mapFromGlobal(QCursor::pos());*/

	//	/*if (TestWidget3->underMouse())
	//	{
	//		qDebug() << "InRenderedViewPort";
	//	}
	//	else
	//	{
	//		qDebug() << "OutOfRenderedViewPort";
	//	}*/

	//	//QWidget::event(QVE);
	//	return true;
	//	break;
	//}
	//if (QVE->type() == QEvent::MouseMove)
	//case (QEvent::MouseMove /*&& !QEvent::ActivationChange*/):
	//{
	//	//QPixmap QP = QPixmap(V);
	//	//qDebug() << "Move";
	//	//qDebug() << QC.pos();
	//	TestWidget3->update();
	//	//QP->begin(this);

	//	/** SIgnificnatly more effective than generic Unthrottled polling as it only
	//	updates to that equal to the number of pixels moved*/
	//	/** Has the main darwback however of not rpeventing the Rect seletcion frome 
	//	xceesing the Geometry of the viewport due to isues witH drag and Drop hanlding apparently: 
	//	https://doc.qt.io/qt-5/qwidget.html#underMouse */
	//	if (TestWidget3->underMouse())
	//	{
	//		//cv::Point2f xy = (TestWidget3->mapFromGlobal(QCursor::pos()).x(), TestWidget3->mapFromGlobal(QCursor::pos()).y());
	//		//xy = TestWidget3->mapFromGlobal(QCursor::pos());
	//		qDebug("UnderMouse");
	//		//might disbale this as it is causing wierd bugs with the mouse pos being updated without pressing/holding a mouse button (seems to be ocuring synchronously as mosueEvent is called seperately from the mian event handler
	//		xx = this->mapFromGlobal(QCursor::pos()).x();
	//		yy = this->mapFromGlobal(QCursor::pos()).y();
	//		//Wirte this to disk
	//		qDebug() << xx << yy;
	//		qDebug() << "Actual Bounds / Bot-Right" << xx*ScaleFactor << yy*ScaleFactor;
	//		qDebug() << "Actual Coord / Top-Left" << xy.x() << xy.y();
	//		//qDebug() << yy;
	//		//qDebug() << xy.x;
	//		//qDebug() << xy.y;
	//		//qDebug() << xy;
	//		//cout << xy << endl;
	//		qDebug() << i++;
	//	}

	//	return true;
	//	break;
	//}
	//if (QVE->type() == QEvent::Paint)
	case (QEvent::Paint):
	{

		//Qimg = V; //Pixmap seems to have significnatly better performance during reSizes than QImage 
		//Qimg = V; //Pixmap seems to have significnatly better performance during reSizes than QImage 
		//Msay be redunant to call /create mu;tpl/redeclaire this Qpainter object which may be adding additional overhead (simialt to teh Qpixmap lag bug where the Qpixamp was being re-initialised multle times in the main event handler
		QPainter QP(this); //Apparently Begin does not need to be called if the QPainter is already initialised to a specific/given context....

		//TestWidget3->setFixedSize(Qimg.size());
		//Bug: Lag if over certain dimensions

		//-->Perhapes uses a gargBage. lazy hack where ann alternate path could be used based on if  abool has been toggled (Based on key inout) to allow the QPainter to have differently (e.g. Chnage Zoom?ScaleFatcor, Selection?Cropregion SelectioN precision e.g.

		/*Edit: even with Scaling set to 4 for very large images over 1440P the performance issue still persists, 
		even if image scaling is diabled entriely, so is not entriely due to teh phsicla dims/ssize of the Bitmap itself
		Potentially may be an issue with Pixmap and/or the Qpainter itself
			Edit: eprfoamnce isue fixed by moving the Qimg declaration to the FileHandler Method which prevents the Qimpg from ebing re-Declaired constantly several tiems a second onetia;ly ever time teh QPaint Event is caucght/handled/Called by teh Main Ui thread (is it actuall the Ui therad that Calles/Hanles the QEvents, at elast Ponetially outside the EvenThandler used/utilsied here...))*/
		//if (Qimg.size().height() > 1440. || Qimg.size().width() > 2560.)
		//{
		//	ScaleFactor = 4.;
		//	TestWidget3->setFixedSize(Qimg.size() / ScaleFactor);
		//}

		//else if (Qimg.size().height() > 720. || Qimg.size().width() > 1280.)
		//{
		//	//TestWidget3->updateGeometry();
		//	/** setup is flawed as cannot select subPixel/Pixel-Based precision beloew the scale factor, so rects that are not divisible by the scale sactor cannot be selected
		//	May be posible to fix this my using floats for Enhanced Sub)facle fatcor precision (e.g. inclrementing by 0.5 instead of 1 for Scale factor of 2 or 1/ ScaleFactor*/
		//	ScaleFactor = 2.;
		//	TestWidget3->setFixedSize(Qimg.size() / ScaleFactor);
		//}
		//else
		//{
		//	/**Reset Sclae Factor to Default */
		//	ScaleFactor = 1.;
		//	TestWidget3->setFixedSize(Qimg.size());
		//}
		//vertexarray
		///*QRectF*/ rectangle(xy.x(), xy.y(), xx - xy.x(), yy - xy.y());
		//Qimg = QPixmap(TestWidget3->geometry(), Qimg);
		//Qimg.size() /= 2.;
		//QPixmap qpa = (720., 1280., Qimg);
		//QPixmap qpa = (Qimg.scaled(1280., 720.));
		//QP->drawPixmap(TestWidget3->geometry(), Qimg);
		QP.drawPixmap(TestWidget3->geometry(), Qimg);
		//QP.drawPixmap(TestWidget3->geometry(), qpa);
		//QP.drawPixmap(720., 1280., Qimg);
		//QP.drawEllipse(rectangle);
		//QP.drawRect(rectangle);
		QP.drawRect(xy.x(), xy.y(), xx - xy.x(), yy - xy.y());
		//corrupted/invalid characters
		//QP.drawText(xy, QString(xx + yy));
		//QP.drawText(xy, QString(xy.y()));
		//char as(xx);

		/** cant sem to format ints as chars properly as they are interpeted as ASCII Values which leads to the distorted character bug*/
		//QP.drawText(xy, tr(&as));

		//Fixed offsetbug when Dispaly is scaled above 16:9 720P Viewport Size/Scaling */

		QP.drawText(xy, QString::number(xx * ScaleFactor - xy.x() * ScaleFactor) + "x" + QString::number(yy * ScaleFactor - xy.y() * ScaleFactor));
		//QP.drawText(xy, xx);
		//Also corrupted/invalid characters
		//QP.drawText(xy, QString(xx) + QString(yy));
		//QP.drawText(xy, QChar(xx + yy));
		//QP.drawText(xy, QString(xx));

		//QWidget::event(QVE);
		return true;
		break;
	}
	/**check for specific keys*/

	//had to remove the Keypres handle here as it overrides/has prioreity over the keypressevent hander

	//case (QEvent::KeyPress):
	//{
	//	//rectangle.
	//	qDebug() << "Pressed Enter";
	//	qDebug() << xy;
	//	qDebug() << xx << yy;
	//	//std::ofstream OutFile ("OutFile.txt", std::ofstream::out);
	//	//char file = std::to
	//	//std::ofstream OutFile (AsFile.toStdString()+".txt", std::ofstream::out);
	//	//std::ofstream OutFile ("test.txt", std::ofstream::out);
	//	//OutFile << (xy.x() + xy.y() + xx + yy);
	//	//OutFile << (int(xy.x()) + " - ");
	//	//OutFile << (int(xy.x()) + "\n");
	//	//OutFile << (int(xy.x()) + char("\n"));

	//	//QDir Loc = V;
	//	/**Qt by default only format their paths with unix style formatting with "/" and not "\" Thankfully they do provide a native method for windows formatting to avoid the need to regex the file*/
	//	//https://doc.qt.io/qt-5/qdir.html#toNativeSeparators
	//	QString Loc = QDir::toNativeSeparators(V);

	//	//Fixed offsetbug when Dispaly is scaled above 16:9 720P Viewport Size/Scaling */
	//	//char NameName = NameFile.c_str;

	//	//cout << SavePath << endl;
	//	//qDebug() << NameFile;
	//	//qDebug() << SavePath;

	//	//std::ofstream OutFile;

	//	//OutFile.open("test.txt", std::ofstream::app);
	//	//OutFile << V.toStdString() << " " << 1 << " " << (int(xy.x()* ScaleFactor)) << " " << (int(xy.y()* ScaleFactor)) << " " << (xx* ScaleFactor) << " " << (yy* ScaleFactor);
	//	//OutFile << Loc.toStdString() << " " << 1 << " " << (int(xy.x()* ScaleFactor)) << " " << (int(xy.y()* ScaleFactor)) << " " << (xx* ScaleFactor) << " " << (yy* ScaleFactor);
	//	int a = (xx - xy.x()) * ScaleFactor;
	//	int b = (yy - xy.y()) * ScaleFactor;
	//	/**check if negative signed */
	//	/*if ( a < 0 || b < 0 )
	//	{
	//		OutFile << Loc.toStdString() << " " << 1 << " " << (int(xy.x() * ScaleFactor)) << " " << (int(xy.y() * ScaleFactor)) << " " << a * -1 << " " << b * -1;
	//	}
	//	else
	//	{
	//		OutFile << Loc.toStdString() << " " << 1 << " " << (int(xy.x() * ScaleFactor)) << " " << (int(xy.y() * ScaleFactor)) << " " << a << " " << b;
	//	}
	//	OutFile << "\n";*/
	//	//OutFile << Loc.toStdString() << " " << 1 << " " << (int(xy.y() * ScaleFactor)) << " " << (int(xy.x() * ScaleFactor)) << " " << (yy * ScaleFactor) << " " << (xx * ScaleFactor);
	//	
	//	

	//	//OutFile.close();

	//	break;
	//}
	/** Experimental Failsafe Event handle for aborting closes if the isBusy bool is true */
	/*case (QEvent::Closing):
	{
		if (!isbusy)
		{
			qDebug("CLosinG main process.......");
			QAPP::close();
			QAPP::Exit;
			QAPP::~QAPP();

		}
		else
		{
			printf("File Dialog is Open!");
			qWarning() << "File Dialog is Open!";
			Exit->setText("Wait for close");
		}
		break;
	}*/

	/** must be the method of the main 'Parent' clas to return the events properly */
//	else
	default:
	{
		return QSplitter::event(QVE);
		//return QSplitter::event(QVE), true;
		break;
	}
	}
	//return this->event(QVE);
};



//void QAPP::CloseFileStream( OutFile)
//{
//	//qdebug() << this->mapfromglobal(qcursor::pos());
//}
///** Main QAPP Class Destructor */

QAPP::~QAPP()
{
	//std::rename("test.txt", NameFile.c_str());
	//OutFile.close();
	qDebug("Destructed main process");
}


/** Experimental Failsafe Slot for aborting closes if the isBusy bool is true */
void QAPP::CloseMain()
{
	 if (!isbusy)
	 {
		 qDebug("closing main process.......");
		 QAPP::close();
		 //qapp::exit;
		 //qapp::~qapp();

	 }
	 else
	 {
		 //printf("file dialog is open!");
		 qWarning() << "file dialog is open!";
		 Exit->setText("wait for close");
	 }

}
