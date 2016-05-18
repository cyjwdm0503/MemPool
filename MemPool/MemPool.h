#ifndef MEMPOOL_H
#define MEMPOOL_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
typedef struct MEMLinker
{
	void* pHead;
	void* pCurr;
	void* pNext;//下一个chunk
}Link;

typedef struct ListNode
{
	void* pNext;
	void* pPrev;
}; 

typedef struct MEMChunkNode//每个chunk维护的内容
{
	int UnitSize;
	int MaxUnit;
	int StoreSize;
	int AllocUnit;
	char* CFlag;
	void* DataAddr;

}Node;

//16个字节的整数倍,方便建立双向链表
size_t round_up(size_t size)
{
	return ((size+15)& ~15);
}

class CMem
{
public:
	CMem(int unitSize, int maxUnit);
	~CMem(void);

public:
	void InitMaxUnit();

	void* Alloc();
	void Free();
	void Free(void*);
	void*  GetUnused();
	void SetUnused();
private:
	int UnitSize;
	int MaxUnit;
	int StoreSize;
	Node* pCur;
	ListNode* pHead;
};

#endif

