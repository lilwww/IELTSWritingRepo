#include "../include/dictionary.h"
#include "../include/key_recommander.h"

#include <iostream>

void textQuery(const string &word)
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
void queryLoop()
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
int main()
{
    _pdict;
    return 0;
}
