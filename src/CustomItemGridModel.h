#pragma once

#include <QAbstractItemModel>
//#include <QAbstractTableModel>
//#include <QtGlobal>
/**https://doc.qt.io/qt-5/model-view-programming.html#a-read-only-example-model*/
/** This directly Overides the ABtractItemModel to allow for the ability to act as a special Read-Only Version/Alternative*/
/** Could use this as an array of Qimages for thumbnails */
/** This does not support images at the moment */
/** Experimental support for multiDimensional Models beyond that of One dimensional ItemModels */

/** https://www.hardcoded.net/articles/using_qtreeview_with_qabstractitemmodel */

class CustomItemGridModel : public QAbstractTableModel
{
	Q_OBJECT
		//Q_PROPERTY(CONSTANT)
public:
	//ItemGridModel(int rows = 0, int columns = 0, QObject* parent = 0) : QAbstractItemModel(parent), List(strings) {} /** Refrences needed */
	
	/* This may have to be done with providing tags as columns instead (e.g. size, Modif, ext e.g......) to enumerate as the number of cols*/
	/* QTableView may also not work as we only want to interact with the main/initial colum with the filename instead of the other columns to prevent bad parameters such as the size/date modified, e.g. being provided instead of the file name/file Dir
		* a workaround may involve selecting all columns at that specific row like Windows Explorer style e.g....
		* this woud also work well with view models that would naturally/inherently benefit from it(e.g. THumbnail viewer */
		
	/* May actually be possible to do this with 1D Abstractlist models with LinkedLists (e.g. row->COlum#No):
		* e.g. QMap or LinkedList with multiple dimenisons so multiple 'columns' can be represented as one */
	CustomItemGridModel(QList<QString> strings, int columns, QObject* parent = 0) : QAbstractTableModel(parent), List(strings) {} /** Refrences needed */
	/** https://www.kdab.com/new-in-qt-5-11-improvements-to-the-model-view-apis-part-1/ *https://www.kdab.com/new-in-qt-5-11-improvements-to-the-model-view-apis-part-2/ */
	
	Qt::ItemFlags flags(const QModelIndex& index) const override
	{
		return Qt::ItemIsEnabled, Qt::ItemIsSelectable;
	}

	int rowCount(const QModelIndex& parent) const override /** Must be const With Pointer*/
	{
		Q_ASSERT(checkIndex(parent));
		if (!parent.isValid())
		{
			qDebug("rC: Invalid Parent");
			return 0;
		}
		else
			return List.count();
	}
	/** https://doc.qt.io/qt-5/qmodelindex.html#data */
	QVariant data(const QModelIndex& index, int role) const override /** these methods are set as override as they need to directly override that of QALM to act as a true Custom/Alternate instance if it */
	{
		Q_ASSERT(checkIndex(index, QAbstractItemModel::CheckIndexOption::IndexIsValid));
		if (!index.isValid())
		{
			qDebug("Data: Bad Index");
			return QVariant();
		}
		if (index.row() >= List.size())
		{
			//if (index.row() >= Image.size())
			qDebug("Row Greater than Size");
			//return this;
			return QVariant();
		}

		if (role == Qt::DisplayRole)
		{
			qDebug("Role Valid");
			//return List.at(index.row()), index.column();
			return List.at(index.row());
		}
		//return Image.at(index.row());
		else
			return QVariant();
	}
	/** https://doc.qt.io/qt-5/qabstractitemmodel.html#headerData */
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override
	{

		if (role != Qt::DisplayRole)
		{
			qDebug("Bad Role");
			return QVariant();
		}

		if (orientation == Qt::Horizontal)
		{
			qDebug("Horizontal");
			return QStringLiteral("Column %1").arg(section);
		}
		else
		{
			qDebug("Vertical");
			return QStringLiteral("Row %1").arg(section);
		}

	}

	int columnCount(const QModelIndex& parent) const override
	{
		////Q_ASSERT(checkIndex(parent, QAbstractItemModel::CheckIndexOption::IndexIsValid));
		//Q_ASSERT(checkIndex(parent, QAbstractItemModel::CheckIndexOption::IndexIsValid));
		//return parent.column();
		Q_ASSERT(checkIndex(parent));
		if (!parent.isValid())
		{
			qDebug("cCount, Invalid Parent");
			return 0;
		}
		else
			//return parent.;
			//return columns;
			return 1;
	}
/**
	// QModelIndex parent(const QModelIndex& index) const override
	// {
		// Q_ASSERT(checkIndex(index));

		// //qDebug("Returned Index");
		// if (!index.data().isValid())
		// {
			// qDebug("Parent:");
			// return QModelIndex();
		// }
		// return index.parent(); //* https://doc.qt.io/qt-5/qabstractitemmodel.html#parent */


	// }
/**
	// QModelIndex index(int row, int column, const QModelIndex& parent) const override
	// {
		// Q_ASSERT(checkIndex(parent));
		// if (!hasIndex(row, column, parent))
		// {
			// qDebug("No Index");
			// return QModelIndex();
		// }
		// if (!parent.isValid())
		// {
			// qDebug("Index: Invalid Parent");
			// if (row < 0)
			// {
				// qDebug("bad/Invalid Row!");
				// return QModelIndex();
			// }
			// if (column < 0)
			// {
				// qDebug("bad/Invalid Column!");
				// return QModelIndex();
			// }
			// //if(!parent.model.isValid())
			// else
			// {
				// qDebug(".Misc, Likely Bad Model");
				// return QModelIndex();

			// }
		// }
		

		// else
		// {
			// qDebug("Creating Index");
			
			
			
			// //Q_ASSERT(hasIndex()
			// //return createIndex(row, column).data(role; /** this OK: https://doc.qt.io/qt-5/qabstractitemmodel.html#createIndex/ */
			// //return createIndex(row, column).data.internalPointer(); /** this OK: https://doc.qt.io/qt-5/qabstractitemmodel.html#createIndex/ */
			// /** https://doc.qt.io/qt-5/qobject.html#Q_INVOKABLE */
			// //Q_INVOKABLE return createIndex(row, column, data//Q_INVOKABLE setData(parent, Qt::DisplayRole)); /** this OK: https://doc.qt.io/qt-5/qabstractitemmodel.html#createIndex/ */
			// //quintptr sub = parent.row();
			// //quintptr sub = parent.internalId();
			// //quintptr sub = 0;
			// //quintptr sub = parent.internalPointer();
			// //quintptr sub = parent.data();
			// //Q_ASSERT(valid)
			// createIndex(row, column, parent.internalPointer());
			// //Q_INVOKABLE return createIndex(row, column, parent.internalPointer());
			// ///*Q_INVOKABLE*/ return createIndex(row, column, &parent.data());
			// //return (row, column, parent.index);
			 // //return createIndex(row, column, index.internalid());
			// return ItemGridModel::index(row, column, parent);
		// }

	// }
/**/

private: /** Functions as the Argument list for this Overriding class: it is also possible to use more than one accepted/Specified argment with accompanying constructors*/
	const QList<QString> List; /**This must match the Argument(s) provided to this class otherwise the Object will not be constructed properly */
	int columns;
};
