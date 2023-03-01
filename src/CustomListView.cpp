#include "CustomListView.h"

CustomListView::CustomListView(QObject* parent)
{
	//CustomListView;
	
		CustomListView::setAlternatingRowColors(true);
		CustomListView::setColumnHidden(1, false);
		setExpandsOnDoubleClick(false);
		//setCursor
		setSortingEnabled(false); //We don't need dedicated sorting support as we are using our own hacky sorting implementation
		setGeometry(QRect(430, 70, 520, 450));
		setMinimumSize(600, 300);
		setMaximumWidth(600);
		//autoExpandDelay();
		hide();

		//setFont;
		////setFrameShadow(QFrame();
		//CustomListView::
	
}