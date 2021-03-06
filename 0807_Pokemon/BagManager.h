#pragma once
#include "Item.h"

struct ItemData
{
	int m_itemNumber;
	int m_count;
};

class BagManager
{

private:
	std::vector<ItemData> m_toolList;
	std::vector<ItemData> m_specialList;
	std::vector<ItemData> m_ballList;
	Item m_selectedItem;

private:
	BagManager();
	~BagManager();

	void SaveBag();
	void LoadBag();

public:
	static BagManager& GetInstance()
	{
		static BagManager Instance;
		return Instance;
	}

	void Init();
	std::vector<ItemData> GetItemList();
	Item GetSelectedItem();
	void SetSelectedItem(int _index);
};

#define BAG_MANAGER BagManager::GetInstance()