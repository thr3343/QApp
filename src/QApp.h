#pragma once

#include <QPushButton>
//#include <fstream>
#include <QtCore>
#include <QSplitter>
#include <QCheckBox>
#include <QPainter>
#include <QFile>
#include <QProgressBar>
#include <qevent.h>

#include "CustomItemListModelv2.h"
#include "CustomListView.h"

#include "mItemListv2.h"
#include "ParseImg.h"
#include "UnitTest.h"




//class QAPP : public QSplitter, public QPainter/*, public QTabWidget*//*, private QThread*/
class QAPP : public QSplitter, public QPainter/*, public QTabWidget*//*, public QTabWidget*//*, private QThread*/
{
	Q_OBJECT
public:
	explicit QAPP(int argc, char** argv, QWidget* parent = 0/*, QTabWidget* TabParent = 0*/);

	//ParseImg PI; //may cause berakakge

	void SetupView(); //* Crude member function to allow the File Dialog to recieve signals and access slot from the mian QAPP class *//
	void SetupViewPort();
	//void paintEvent(QPaintEvent*, QEvent* QE); /** Should this be a slot */
	//void paintEvent(QPaintEvent*); /** Should this be a slot */
	//void paintEvent(QEvent* QE); /** Should this be a slot */
	//void eventHandler(QEvent* QVE);
	bool holdLeft = false;
	bool HoldCtrl = false;
	//void 
	void mouseMoveEvent(QMouseEvent* evt) override; //Cannot combine a handler that hanles both MousePressa nd move events so must be done seperatly as they is currently not a known method of combining teh functionalities/capabilities of both
	void keyPressEvent(QKeyEvent* QKE) override;
	void mousePressEvent(QMouseEvent* evt) override;
	//void mousePressEvent(QEvent::MouseButtonPress ) override;
	//void mousePressEvent(Qt::MouseButtons* QtM) override;
	//bool QMevent(QMouseEvent* QME);
	//bool QMevent(Qt::MouseButton* QA);
	bool event(QEvent* QVE/*, QMouseEvent* QME*//*, QRegion* QRE*/) override; //is Override even nessacery in this case...
	//void paintEvent(QPaintEvent* pvt) override;
	//void eventHandler(QMouseEvent* QVE);	
	void instantiateTree();
	void OpenedDir();
	void ClassPicker();

	void ThreadHelper(); //Do not do this: is a terrible, lazy way of allowing the ParseImg Function to be spawned as a seperate thread as they does nto see to be an easy way to do this by default witha a QT event-driven-based connector

	//void run() override; //Override
	//QMutex mutex;
	//QString GetPath(QModelIndex Index);
	QString SetPath(QString a) { return a; };

	QEvent* QE;
	//void ObjectHandler();
	//void DebugMode();

	bool isbusy = true; //* test to allow for the ability to prevent process termination : could be used as a experimental feature to allow other signals to hook into (e.g. to prevent data corruption during operations e.g.)*//

	/*const*/ int Sel = 0;

	//->std::ofstream OutFile;
	//__argc
	int Iargc;
	char** Iargv;
	int xx = 0;
	int yy = 0;
	int axx;
	int ayy;
	QPoint xy;
	QRectF rectangle;
	int i = 0;
	int v = 0;
	//float Prcnt;// = 0;
	float Prcnt = 0;
	bool setThresh = false;

	//QString* V;
	//QString* V = NULL;
	QString V;

	const QString OutPath = QDir::currentPath() + "/Results/"; //* can be set as const as may not need to be changed *//


	//QPixmap* Qimg = nullptr;
	//QPixmap Qimg;// = nullptr;
	//QPainter QP;

	QUrl Url;
	QFile FileHandler;
	//QImage* QI = nullptr;
	QPixmap Qimg = nullptr;
	//* Base path for Working Image Directory (In unix style formmating as default with Qt)
	const QString Path2 = QDir::currentPath(); //* can be set as const as may not need to be changed *//
	const QString ImgPath = QDir::currentPath() + "/Imgs/"; //* can be set as const as may not need to be changed *//
	//const QString OutPath = QDir::currentPath() + "/Results/"; //* can be set as const as may not need to be changed *//
	const QString AnotPath = QDir::currentPath() + "/Annotations/"; //* can be set as const as may not need to be changed *//
	//QList<QString> ImgNames;
	//QMap<QString, qint64> ImgSets;
	QString xFile;
	//std::ofstream OutFile;// = nullptr;
	//std::string* NameFile = nullptr;
	std::string NameFile;
	std::string SavePath;
	QString SavePath2;
	QList<QString> aClass;

	QWidget* TestWidget = nullptr;
	//QTabWidget* TestWidget = nullptr;
	QWidget* TestWidget3 = nullptr;
	QPainter* QP = nullptr;

	QProgressBar* QB = nullptr;

	QWidget* OptionSet = nullptr; //experimental attempt to add dynamically/user specifiable options and/or features

	QTabWidget* TestWidgetTabSet = nullptr; //abomination seisgned to act as the 'parent' or 'dummy Qobject' for the subsequent 'child' tabs with the 'actual' utilised QWidgets comtaimng the aditonal QObjecs

	//QString V;

	//mItemListv2<QString> InputImages/*(Qt::ItemIsEditable)*/; /**Lazy linkedList **/
	//mItemListv2<QString> InputImages/*(Qt::ItemIsEditable)*/; /**Lazy linkedList **/
	mItemListv2<qint64> FileSizes;
	QList<QString> InputImages;/*(Qt::ItemIsEditable)*/; /**Lazy linkedList **/
	QString FileFile;
	QString AsFile;

	//_mm256_maskz_shufflelo_epi16
	float ScaleFactor = 1.;

	//QModelIndexList InputImages; /*https://doc.qt.io/qt-5/qmodelindex.html#QModelIndexList-typedef
	QList<QImage> InputThumb;
	QList<QString> ImgNames;
	QFile/*<QImage>*/ Imgs;
	QPushButton* AddImgs = nullptr;
	QPushButton* Exit = nullptr;

	//QPushButton* Add = nullptr;
	QPushButton* Close = nullptr;
	QPushButton* OpenRoot = nullptr;

	QPushButton* Sort = nullptr;
	QPushButton* AnalyseImg = nullptr;
	
	QPushButton* AddObj = nullptr;

	QPushButton* SaveFile = nullptr;

	//No Sort by FileSize due to the considerable compleity involved with hanlding more than one column 
	QCheckBox* ThreshOpt = nullptr;
	QCheckBox* SortAsc = nullptr;
	QCheckBox* SortDesc = nullptr;


	QPoint QM;
	QAbstractItemModel* A = nullptr;
	QAbstractItemModel* B = nullptr;

	QCursor QC;// = nullptr;

	QSlider* QS = nullptr;

	

	~QAPP();
signals:
	//void on_opened_state(/*const bool a*/);

//public slots:
//	void UpdateBar(float Stat);

private slots:

	//void init();
	/*void OpenedDir();*/
	//void ClosedDir();
	void Filehandler(QModelIndex Index/*QMouseEvent::*//*QFileSystemModel::fileInfo*/);
	void RefreshTree(/*QModelIndex Index*/);
	void SortSet();
	//void ParseImg();
	void SetShape(QModelIndex index);
	void updateSet();
	//->void CloseFileStream(std::ofstream OutFile);
	void AddRowObject();
	void CloseMain();
private:
	//QFileSystemModel* FileSystem = nullptr;

	//QListView* FileTree = nullptr;
	//QTableView* FileTree = nullptr;
	CustomListView* FileTree = nullptr;
	CustomListView* ClassList = nullptr;
	//QTreeView* FileTree = nullptr;
	//QAbstractItemView* FileView = nullptr;

	int SortType = 1;

};
//#endif // !QAPP
