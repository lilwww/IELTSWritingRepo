#ifndef __SE_DICTPRODUCER_H__
#define __SE_DICTPRODUCER_H__

#include <fstream>
#include <unordered_map>
#include <set>
#include <sstream>

#include "dir_scanner.h"
#include "word_segmentation.h"

#define CHSIZE 3
using std::ifstream;
using std::istringstream;
using std::ofstream;
using std::pair;
using std::set;
using std::unordered_map;
namespace search_engine
{

    class DictProducer
    {
    public:
        DictProducer();
        ~DictProducer();
        void create_En_Dict();
        void store();
        void queryLoop();

    private:
        void insert_En_index(const string &elem, size_t id);
        void processLine(string &line);
        void textQuery(const string &word);
        void insert_Index(const string &elem, size_t id);
        void open_File(ifstream &ifs, const string &fileName);
        void input_File(ofstream &ofs, const string &fileName);

    private:
        int _lineNum;
        vector<string> _file;
        vector<string> _lineContent;
        unordered_map<string, int> _dict;
        unordered_map<string, set<int>> _lineIndex; // string: word+docid
        unordered_map<string, set<int>> _index;
        unordered_map<int, string> _idMap;
        WordSegmentation _jieba;
        DirScanner _dir;
    };

};     // end of namespace set_exception_at_thread_exit
#endif //__SE_DICTPRODUCER_H__
