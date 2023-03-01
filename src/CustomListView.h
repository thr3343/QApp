#pragma once

#include <QTreeView>


class CustomListView : public QTreeView
{
	Q_OBJECT
public:
		CustomListView(QObject* parent = nullptr);

		//void setAlternatingRowColors(bool);
		//void setColumnHidden(int column, bool hide);

	
};

