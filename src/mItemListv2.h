#pragma once
#include <cstddef>
//#include <stdio.h>
//#include <iostream>

/** Extremely lazy Linked list:
	* Sources: https://www.hackerearth.com/practice/data-structures/linked-list/singly-linked-list/tutorial/
	* :https://www.codesdope.com/blog/article/c-linked-lists-in-c-singly-linked-list/
*/




/** https://www.cplusplus.com/doc/tutorial/templates/ */

//using std::cout;
//using std::endl;


/**Allows greately enhanced versatility when handling multiple data types*/
template <class type2>


/**This modified Linked List structure was originally intended as a Multi-Dimensional Linked List of Linked Lists to allow the CustomItemModel 
to support multiple columns, but was cut from developemnt due to the complexity and unwieldiness of such a Data Structure 
becoming too great to handle adequately during development */

/**Was also intended as a subsitute for vectors, but was also unimplemented due to problems with sorting and indexing pointers properly without overwriting or corrupting the member variables*/

class mItemListv2
{
private:

	//type2 value;

	int Len = 0;

	int DH = 0;

	struct Node
	{
		//QString Item;
		type2 xItm;

		int Key;

		Node* xnext;
	};

	Node* xh, * xt;
	enum SortTypes
	{
		ASC = 1,
		DESC = 2
	};

private:

/** This method is private due to fatal bugs with the indexing system where index values are not updated after Insertions/Removals 
	due to perfomance reasons, which causes certain indexes to fail/become unusable/Invalid or case instability/Crashes*/
	void dropNode(int x)
	{
		Node* Xtmp;
		//x - DH;
		x += DH;
		Xtmp = xh;
		//if(x%)
		//printf("Dropping");
		//if (x != 0)
		if (x > DH)
		{
			while (Xtmp->Key != x - 1)
			{
				Xtmp = Xtmp->xnext;
			}
			Node* Prior = Xtmp->xnext;
			//xh = xh->xnext;
			Xtmp->xnext = Prior->xnext;
			//Xtmp->xnext->xnext;

			delete Prior;
			Len--;
			//->DH++;

		}
		else
		{
			xh = xh->xnext; //Must move the head forward or else the "Beginning" of the Structure will point to NULL or break horribly (Point to odd values such as MAX_INT 
			delete Xtmp;
			Len--;
			DH++;

		}




	}

public:
	//mItemList()
	mItemListv2<type2>()
	{
		xh = NULL;
		xt = NULL;
	}

	Node* GetHead() { return xh; }
	Node* GetTail() { return xt; }

	//type2 getlength()
	int getlength()
	{
		return Len;
	}

	type2 mCreateItem(type2 x)
	{
		Node* tmp = new Node; //allocate new instance of Node
		tmp->xItm = x; //init Itm of this new 
		tmp->xnext = NULL; //last node is always referencing NULL
		tmp->Key = Len;
		Len++;

		if (!xh) //h!= NULL
		{
			xh = tmp;
			xt = tmp;
		}
		else
		{
			xt->xnext = tmp;
			xt = xt->xnext;
		}
		return x;

	}

	type2 mAddrItem(int x)
	{
		Node* CurIdx;
		CurIdx = xh;
		//x += DH;
		
			//==##-->QVERIFY()
		
		while (CurIdx->Key != x)
		{
			CurIdx = CurIdx->xnext;
		}
		//x = CurIdx->xItm;
		/*if (CurIdx->xItm == NULL)
		{
			return NAN;
		}*/
		//type a = CurIdx->xItm;
		return CurIdx->xItm;
	}

	type2 mOverWriteItem(int x, type2 a)
	{
		Node* CurIdx;
		CurIdx = xh;
		//x += DH;

			//QVERIFY()

		while (CurIdx->Key != x)
		{
			CurIdx = CurIdx->xnext;
		}
		//x = CurIdx->xItm;
		/*if (CurIdx->xItm == NULL)
		{
			return NAN;
		}*/
		//type a = CurIdx->xItm;
		CurIdx->xItm = a; 
		return CurIdx->xItm;
	}

	/**cout is bugged with this kind of pointer and messes up the operators: 
	possibly an issue with Qt as it does not occur in a 'Vanilla' solution with no external dependencies*/
	
	void showAll()
	{
		Node* Xtmp;

		Xtmp = xh;
		//type a = xtmp->xItm;
		while (Xtmp)
		{
			//printf("%d", Xtmp->xItm);
			//cout << Xtmp->xItm << endl;
			//qDebug() << Xtmp->xItm;
			//qDebug(Xtmp->xItm);
			//std::cout << a << std::endl;
			qDebug() << Xtmp->xItm;

			Xtmp = Xtmp->xnext;
		}

	}

	void mItemSort(/*SortTypes*//*int s*/)
	{
		Node* Xtmp;

		Xtmp = xh; //Start at Base Node
		int EndPoint = Len;
		int CurId = 0;// =
		//type a = xtmp->xItm;
		while (Xtmp)
		{
			
			/*mCreateItem(Xtmp);
			dropNode(0);*/



			//-->mAddrItem to 'override' members.......
			//int CurId = Xtmp->Key; //Get key of current node

			//printf("%d", Xtmp->xItm);
			//cout << Xtmp->xItm << endl;
			//cout << CurId << endl;
			//Len--;
			Xtmp->Key = Len -CurId;
			//qDebug(Xtmp->xItm);
			//cout << Xtmp->xItm << endl;
			//std::cout << a << std::endl;
			Xtmp = Xtmp->xnext;
		}
	}

	

	void dropAll()
	{
		/*Node* Xtmp;
		Xtmp = xh;*/
		//int Cur = 0;
		qDebug() << "Deleting Node Set";
		while (Len > 0)
		{

			dropNode(0);
			//xh = xh->xnext;
			//delete Xtmp;
			////Xtmp = Xtmp->xnext;
			cout << "Drop" << endl;
			//printf("\n", "Drop");
			//Cur++;
		}
		DH = 0;
		qDebug() << "Deleted Node Set";
	}


};



// };
