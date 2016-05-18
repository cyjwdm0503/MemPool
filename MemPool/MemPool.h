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
	void* pNext;//��һ��chunk
}Link;

typedef struct ListNode
{
	void* pNext;
	void* pPrev;
}; 

typedef struct MEMChunkNode//ÿ��chunkά��������
{
	int UnitSize;
	int MaxUnit;
	int StoreSize;
	int AllocUnit;
	char* CFlag;
	void* DataAddr;

}Node;

//16���ֽڵ�������,���㽨��˫������
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

