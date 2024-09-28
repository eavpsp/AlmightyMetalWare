#ifndef CUSTOMLIST_H
#define CUSTOMLIST_H

#include <string>
#include <vector>
class CustomList
{
    private:
      
        std::vector<std::string> listNames;
        std::vector<void *> listData;
    public:
        void* GetData(std::string name);
        void AddData(std::string name, void *data);
        void RemoveData(std::string name);
        void *first;
        void *last;
    };

#endif //CUSTOMLIST_H
