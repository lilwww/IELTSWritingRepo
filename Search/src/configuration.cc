
#include "../include/configuration.h"


namespace search_engine {

Configuration* Configuration::pInstance = nullptr; // 饱汉模式，因为是离线部分不用考虑多线程安全

/* string Configuration::_config_file_path = "conf/server.conf";       // 配置文件路径 */

Configuration* Configuration::getInstance() { // 静态成员函数
    if (!pInstance) {
        pInstance = new Configuration("conf/word.conf");          
    }
    return pInstance;
}


Configuration::Configuration(const string& file_path) {
    // 初始化配置文件部分
    ifstream ifs;
    ifs.open(file_path);
    if (!ifs.good()) { std::cerr << "open word.conf fail" << endl; }

    string line, key, val;
        while (getline(ifs, line), !ifs.eof()) {
            istringstream iss(line); 
            iss >> key;
            iss >> val;
            pair<string, string> record (key, val);
            _configs.insert(record);
        }
        ifs.close();
}

map<string, string>& Configuration::get_configs() {
    return _configs;
}


} // namespace search_engine
