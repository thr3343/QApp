#pragma once

#include <QAbstractItemModel>
//#include "mItemListv2.h"
//-->#include "UnitTest.h"
//#include "UnitTest.h"

/** https://www.hardcoded.net/articles/using_qtreeview_with_qabstractitemmodel */


/**Qt by default does not provide a Listmodel that is read-Only, hence why the 
default QAbstractListModel Class need to be subclassed instead to provide the required functionality 
which is also recommended by the Qt Documentation for Custom ItemModels*/

class CustomItemListModelv2 : public QAbstractListModel
{
	Q_OBJECT
public:
	enum Cols
	{
		ActiveCol = 0,
		FileName,
		FileSize
	};

	//->CustomItemListModelv2(QMap<QString, qint64>& strings, QObject* parent = 0) : QAbstractListModel(parent), Map(strings) {} /** Refrences needed */
	CustomItemListModelv2(QList<QString>& strings, QString& Items, QObject* parent = 0) : QAbstractListModel(parent), List(strings), Items(QString(Items)) {}  /** Refrences needed */
	//CustomItemListModelv2(mItemListv2<QString>& strings, QObject* parent = 0) : QAbstractListModel(parent), List(strings) {} /** Refrences needed */

	Qt::ItemFlags flags(const QModelIndex& index) const override
	{
		return Qt::FontRole, Qt::ItemIsDragEnabled, Qt::ItemIsEnabled;
	}
	/** returns List Count */
	int rowCount(const QModelIndex& parent) const override /** Must be const With Pointer*/
	{
		//QVERIFY(checkIndex(parent));
		//qDebug("rC: Invalid Parent");
		/*if (!parent.isValid())
		{
			qDebug("rC: Invalid Parent");
			return 0;
		}
		else*/
		return List.count();
	}

	/** Must be const With Pointer: https://doc.qt.io/qt-5/qmodelindex.html#data */
	/**retruns and handles column and row based information within the AbstractItemModel*/
	/*QList<QVariant>*/
	QVariant data(const QModelIndex& index, int role) const override /** these methods are set as override as they need to directly override that of QALM to act as a true Custom/Alternate instance if it */
	{
		//if (!index.isValid())
		//Q_ASSERT(index.isValid()); /** Special macro to abort the Overridden method if Index Invalid: https://www.kdab.com/new-in-qt-5-11-improvements-to-the-model-view-apis-part-1/ */
		//QVERIFY(index.isValid()); /** Special macro to abort the Overridden method if Index Invalid: https://www.kdab.com/new-in-qt-5-11-improvements-to-the-model-view-apis-part-1/ */


		//if (index.row() >= Map.size())
		if (index.row() >= List.size())
		//if (index.row() >= List.getlength())
		{
			qDebug("Row Greater than Size");
			return this;
		}
		if (role == Qt::DisplayRole) /** can be used to change/handle/manipulate the retunred Filenames/Represented Objects in the ViewModel */
		{
		/**Discovered that if the List used for construction is used to provide filenames if the index row is returned as the specified row of the QList */

		//->return List.value(index.row()); //* Could replace this with FileName or even another object such as a thumbnail */
			return List.at(index.row()); //* Could replace this with FileName or even another object such as a thumbnail */
			//return List.mAddrItem(index.row()); //* Could replace this with FileName or even another object such as a thumbnail */
		}
		else
			return QVariant();

	}
	


		/** https://doc.qt.io/qt-5/qabstractitemmodel.html#headerData */
	/** Overridden method that provides orientation and Column Name parameters*/
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override
	{

		if (role != Qt::DisplayRole)
		{
			//qDebug("Bad Role");
			//qDebug() <<role;
			//qDebug() << Qt::DisplayRole;
			return QVariant();
		}
		//orientation == Qt::Vertical;
		if (orientation == Qt::Horizontal)
		{
			//qDebug("Horizontal"); //qDebug() <<section;
			//return QStringLiteral("Items").arg(section);
			return Items;
		}
		else
		{
			qDebug("Vertical");
			return QStringLiteral("Row %1").arg(section);
		}
		//return role;

	}

		//int rowCount(const QModelIndex &) const override
		//{
		//	return Map.size(); //may break horribly
		//}

/** Functions as the Argument list for this Overriding class: it is also possible to use mroe than one accepted/Specified argment with accompanying constructors*/
private: 

	//const QList<QString> ImgList; 
	//const QList<qint64> ImgSize; 
	//const QMap<QString, qint64> Map; 

	//const QList<int> List; 
	const QList<QString> List; /**This must match the Argument(s) provided to this class otherwise the Object will not be constructed properly */
	const QString Items;

	//Warning: -> May break!
	 //mItemListv2<QString> List ; 
};
