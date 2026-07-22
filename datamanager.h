#include <iostream>
#include <vector>
#include <string>

using namespace std;

class DataManager
{
private:
    static const string filePath;

    // متدها را به این شکل ساده کن:
    static string joinVector(const vector<int>& vec);
    static vector<int> splitVector(const string& str);
public:
    static void saveAll();
    static void loadAll();
};
