#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <QMainWindow>
using namespace std;

class DataManager
{

public:
    static DataManager* getDataManager();
    void addFile(QString fileName);
    ~DataManager();
    void addDirectoryPath(QString directoryPath);

private:
    DataManager();
    void getFileNameList();
    void getFilePath();

    void updateDataList();
    static DataManager* dataManager;
    vector<string> *fileNameList;
    vector<int> fileIndex;
};

#endif // DATAMANAGER_H
