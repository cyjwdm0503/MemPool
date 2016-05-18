#include "MemPool.h"
#include <cstddef>

CMem::CMem(int storeSize, int maxUnit)
{
	 
	UnitSize = round_up(storeSize);
	MaxUnit = maxUnit;
	StoreSize = storeSize;
	pHead = NULL;
	pCur = NULL;
}


CMem::~CMem(void)
{
}

void CMem::InitMaxUnit()
{
	char* pMaxUnit = new char[UnitSize*MaxUnit+sizeof(Node)];
	pCur  = (Node*)(pMaxUnit);
	pCur->AllocUnit = 0;
	pCur->StoreSize = StoreSize;
	pCur->MaxUnit = MaxUnit;
	pCur->UnitSize = 0;
	pCur->CFlag =  new char[MaxUnit*UnitSize/8];
	
	memset(pCur->CFlag,0,MaxUnit*UnitSize/8);

	pCur->DataAddr = (void*)(pMaxUnit+sizeof(Node));
	
	//构造整个空链表
	pHead = (ListNode*)(pCur->DataAddr);
	pHead->pPrev =   ((char*)pCur->DataAddr+ MaxUnit*pCur->UnitSize/8);

	for(int pos=1; pos<MaxUnit; pos++)
	{
		pHead->pNext = ((char*)pCur->DataAddr+pos*pCur->UnitSize/8);
		pHead->pPrev = ((char*)pCur->DataAddr+ (pos-1)*pCur->UnitSize/8);
		pHead = (ListNode*)((char*)pCur->DataAddr+pos*pCur->UnitSize/8);
		pHead->pNext = NULL;
	}
}


void* CMem::Alloc()
{
	return (void*)((char*)pCur->DataAddr + pCur->AllocUnit* pCur->UnitSize);
	pCur->AllocUnit++;
}

void CMem::Free(void* p)
{
	ptrdiff_t dis = (char*)p-(char*)(pCur->DataAddr);

	pCur->AllocUnit--;
}

 

void* CMem::GetUnused()
{
	if(pCur->AllocUnit< pCur->MaxUnit)
		return NULL;
	else if(pHead != NULL)
		return NULL;
	else
	{
		ListNode* p;
		p = pHead;
		pHead = (ListNode*)(pHead->pNext);
		return p;
	}
}

 

