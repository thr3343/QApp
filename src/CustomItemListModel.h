#pragma once

#include <QAbstractItemModel>
//#include "UnitTest.h"
/** https://doc.qt.io/qt-5/model-view-programming.html#a-read-only-example-model*/
/** This directly Overides QALM to allow for the ability to act as a special Read-Only Version/Alternative*/
/** Could use this as an array of Qimages for thumbnails */
/** This does not support images at the moment */
/** Only supports One dimensional ItemModels */

/** https://www.hardcoded.net/articles/using_qtreeview_with_qabstractitemmodel */

class CustomItemListModel : public QAbstractListModel/*QAbstractItemModel*/
{
	Q_OBJECT
		//Q_OVERRIDE
		//Q_PROPERTY(CONSTANT)
public:
	CustomItemListModel(QList<QString>& strings, QObject* parent = 0) : QAbstractListModel(parent), List(strings) {} /** Refrences needed */

	/*void*/ Qt::ItemFlags flags(const QModelIndex& index) const override
	{
		return Qt::FontRole, Qt::ItemIsDragEnabled, Qt::ItemIsEnabled /*,Qt::ItemIsDropEnabled, Qt::ItemIsEditable */; // , /*Qt::IBeamCursor;*/// , Qt::FontRole = fsize;
	}
	int rowCount(const QModelIndex& parent) const override
	{
		//qDebug("Returned Rows");
		//qDebug() << parent.row();
		return List.count();
	}
	
	/** Must be const With Pointer: https://doc.qt.io/qt-5/qmodelindex.html#data */
	/*QList<QVariant>*/
	QVariant data(const QModelIndex& index, int role) const override /** these methdos are set as override as they need to dierctly override that of QALM to act as a true Custom/Alternate instance if it */
	{
		//if (!index.isValid())
		Q_ASSERT(index.isValid()); /** Special macro to abort the Overriden method if Index Invalid: https://www.kdab.com/new-in-qt-5-11-improvements-to-the-model-view-apis-part-1/ */
		

		if (index.row() >= List.size())
		{
			qDebug("Row Greater than Size");
			return this;
		}
		if (role == Qt::DisplayRole) /** can be used to change/handle/manipulate the retunred Filenames/Represented Obejcts in the ViewModel */
		{
			/**Discovered that if the List used for construction is used to provide filenames if the idnex row is returned as the specified row of the QList */
			return List.at(index.row()); //* Could replace this with FileName ot even another object such as a thumbnail */

		}
		else
			return QVariant();
			
	}
	/** https://doc.qt.io/qt-5/qabstractitemmodel.html#headerData */


private: /** Functions as the Argument list for this Overriding class: It is also possible to use more than one accepted/Specified argument with accompanying constructors*/
	 const QList<QString> List; /**This must match the Argument(s) provided to this class otherwise the Object will not be constructed properly */
};
