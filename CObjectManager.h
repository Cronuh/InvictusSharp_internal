#pragma once
#include "Utils.h"
#include "CObject.h"
#include "Offsets.h"

class CObjectManager
{
public:

	static CObjectManager* GetObjectManager()
	{
		return (CObjectManager*)(*(DWORD*)((DWORD)GetModuleHandleA(NULL) + oObjManager));
	}

	static short GetHighestIndex()
	{
		short idx = 0;
		auto objectList = *(CObject***)(*(DWORD*)((DWORD)GetModuleHandleA(NULL) + oObjManager) + objectArray);

		void* c = objectList[idx];
		while ((uintptr_t)c != 0x1)
		{
			c = objectList[++idx];
		}
		return idx;
	}


	static CObject* GetObjByIndex(int index)
	{
		__try
		{
			auto objectList = *(CObject***)(*(DWORD*)((DWORD)GetModuleHandleA(NULL) + oObjManager) + objectArray);
			if (objectList)
			{
				//ENGINE_MSG("ObjectList : %p firstobj %p", objectList, objectList[0]);

				if (index > GetHighestIndex())
					return nullptr;
				auto obj = objectList[index];
				if (obj == nullptr)
					return nullptr;

				if (obj)
					return obj;

			}
		}
		__except (1) {}

		return nullptr;
	}



};

extern CObjectManager* ObjManager;