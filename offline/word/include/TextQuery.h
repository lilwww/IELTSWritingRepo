#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::map;
using std::set;
using std::string;
using std::vector;
namespace search_engine
{
    class TextQuery
    {
    public:
        // 构造函数先分配一定空间的大小
        TextQuery();
        void readFile(const string &filename);
        void query(const string &word);

    private:
        void preProceccLine(string &line);

    private:
        // 每次获取一行并存起来
        vector<string> _file;
        // 单词以及词频
        map<string, int> _dict;
        // 单词以及所在行号(注意：同一个单词在相同行出现，只记录一次)
        map<string, set<int>> _word2line;
    };
}