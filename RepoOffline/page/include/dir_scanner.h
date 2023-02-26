#ifndef __SE_DIRSCANNER_H__
#define __SE_DIRSCANNER_H__

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace search_engine {

class DirScanner{
public:
    DirScanner();
    ~DirScanner();
    void operator()(const string& dirname);
    vector<string>& files() ;
    void traverse(const string& dirname);
private:
    vector<string> _files;
};

} // namespace search_engine

#endif // __SE_DIRSCANNER_H__
