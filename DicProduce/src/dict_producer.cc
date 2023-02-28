#include "../include/dict_producer.h"

#include <fstream>

using std::cin;
using std::ifstream;
using std::ofstream;
namespace search_engine
{

    DictProducer::DictProducer()
        : _jieba(), _dir(), _lineNum(0)
    {
        _dir("../data/EN");
        for (auto &fileName : _dir.files())
        {
            _file.push_back(fileName);
        }

        // create_Cn_Dict();
        create_En_Dict();
        queryLoop();
        store();
    }

    DictProducer::~DictProducer()
    {
    }


    void DictProducer::insert_Index(const string &elem, size_t id)
    {
        vector<string> results;
        _jieba.CutSmall(elem, results, 1);
        for (string &it : results)
        {
            _index[it].insert(id);
        }
    }

    void DictProducer::store()
    {
        ofstream ofs_dict;
        input_File(ofs_dict, "../data/dict.dat");
        for (auto it = _dict.begin(); it != _dict.end(); ++it)
        {
            ofs_dict << it->first << " " << it->second << endl;
        }

        ofstream ofs_index;
        input_File(ofs_index, "../data/index.dat");
        for (auto it = _index.begin(); it != _index.end(); ++it)
        {
            ofs_index << it->first << " ";
            for (auto &set : it->second)
            {
                ofs_index << set << " ";
            }
            ofs_index << endl;
        }
#if 1
        ofstream ofs_idMap;
        input_File(ofs_idMap, "../data/idMap.dat");
        for (auto it = _idMap.begin(); it != _idMap.end(); ++it)
        {
            ofs_idMap << it->first << " " << it->second << endl;
        }
        ofs_idMap.close();
#endif
        ofs_dict.close();
        ofs_index.close();
    }

    void DictProducer::create_En_Dict()
    {
        for (string &fileName : _file)
        {
            ifstream ifs;
            open_File(ifs, fileName);
            string line;
            while (getline(ifs, line))
            {

                _lineContent.push_back(line);

                processLine(line);
                istringstream iss(line);
                string word;
                while (iss >> word)
                {
                    int &isExist = _dict[word];
                    if (isExist)
                    {
                        ++isExist;
                        _lineIndex[word].insert(_lineNum);
                    }
                    else
                    {
                        isExist = 1;
                        size_t id = _dict.size();
                        _idMap[id] = word;
                        insert_En_index(word, id);
                        _lineIndex[word].insert(_lineNum);
                    }
                }
                ++_lineNum;
            }
            ifs.close();
        }
    }

    void DictProducer::insert_En_index(const string &word, size_t id)
    {
        for (size_t i = 0; i < word.size(); ++i)
        {
            string ch(1, word[i]);
            _index[ch].insert(id);
        }
    }

    void DictProducer::processLine(string &line)
    {
        for (auto &elem : line)
        {
            if (!isalpha(elem))
            {
                elem = ' ';
            }
            else if (isupper(elem))
            {
                elem = tolower(elem);
            }
        }
    }

    void DictProducer::open_File(ifstream &ifs, const string &fileName)
    {
        ifs.open(fileName);
        cout << "open >>>" << fileName << endl;
        if (!ifs)
        {
            perror("open file failed in Dict ifs");
        }
    }

    void DictProducer::input_File(ofstream &ofs, const string &fileName)
    {
        ofs.open(fileName);
        if (!ofs)
        {
            perror("open file failed in Dict ifs");
        }
    }
    void DictProducer::textQuery(const string &word)
    {

        int count = _dict[word];                                                                  // 获取单词出现的次数
        cout << "[" << word << "] occurs " << count << (count > 1 ? " times" : " time.") << endl; // 打印单词次数

        auto lines = _lineIndex[word]; // 对同一个单词出现的行进行遍历，输出单词以及行号
        int prtCnt = 0;
        for (auto &number : lines)
        {
            cout << "    (line " << number << ") " << _lineContent[number] << endl;
            if (++prtCnt > 10 && prtCnt < lines.size())
            {
                cout << "$$$$ Press M to see more\n";
                char c;
                cin >> c;
                if (c != 'M' && c != 'm')
                {
                    break;
                }
                prtCnt = 0;
                cout << "\n";
            }
        }
    }
    void DictProducer::queryLoop()
    {
        cout << "$$$$ enter the word to query: ";
        string word;
        cin >> word;
        while (word != "q")
        {
            textQuery(word);
            cout << "\n $$$$ Press q to quit or enter another word: ";
            cin >> word;
        }
    }
}; // end of namespace search_engine
