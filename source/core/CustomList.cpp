#include <CustomList.h>
#include <streambuf>
#include <algorithm>
#include "../debug/debug.h"
void *CustomList::GetData(std::string name)
{
    auto it = std::find(listNames.begin(), listNames.end(), name);
    if (it != listNames.end())
    {
        debugLog("Data found in list");
        return listData[std::distance(listNames.begin(), it)];
    }
    debugLog("Data not found in list");
    return nullptr;
}


void CustomList::AddData(std::string name, void *data)
{
    //check if data is already in the list
    if (GetData(name) != nullptr)
    {
        debugLog("Data already exists in list");
        return;
    }
    //check if list is empty
    if (first == nullptr)
    {
        first = data;
        debugLog("Added new Item to list");
        
    }
    listNames.push_back(name);
    listData.push_back(data);
    last = data;
    debugLog("item added");

}


void CustomList::RemoveData(std::string name)
{
    auto it = std::find(listNames.begin(), listNames.end(), name);
    int index = 0;
    if (it != listNames.end())
    {
        index = std::distance(listNames.begin(), it);
        listNames.erase(it);
        listData.erase(listData.begin() + index);
    }
}
