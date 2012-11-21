#include <fstream>
#include <iostream>
#include <sstream>

#include "myconfig.h"
#include "log.h"


#define CONF_FILE_NAME "../etc/art_spider.conf"

using namespace std;

Config& Config::instance()
{
	static Config conf;
	return conf;
}

Config::Config()
{
}

Config::~Config()
{
}

void Config::trim(string &s)
{
	s.erase(0, s.find_first_not_of("\r\t\n "));
	s.erase(s.find_last_not_of("\r\t\n ") + 1);
}

bool Config::open_config()
{
	ifstream conf_file(CONF_FILE_NAME);
	if (!conf_file.is_open()) {
		cout << "Can not open config file " << CONF_FILE_NAME << endl;
		return false;
	}
	string line;
	while(getline(conf_file, line)) {
		if (line.empty() || line[0] == '#') {
			continue;
		}
		string::size_type equal_pos = line.find('=');
		if (equal_pos == string::npos || equal_pos == 0 || equal_pos == line.size()) {
			cout << "Config Format Error: " << line << endl;
			continue;
		}
		string key(line.substr(0, equal_pos));
		trim(key);
		string value(line.substr(equal_pos + 1));
		trim(value);
		if (key.empty() || value.empty()) {
			cout << "Config Format Error: " << line << endl;
			continue;
		}
		conf[key] = value;
	}
	return true;
}

bool Config::get_str_conf(const string &key, string &value)
{
	un_map::iterator it = conf.find(key);
	if (it != conf.end()) {
		value = it->second;
		return true;
	} else {
		return false;
	}
}

bool Config::get_int_conf(const string & key, int &value)
{
	un_map::iterator it = conf.find(key);
	if (it != conf.end()) {
		stringstream ss(it->second);
		ss >> value;
		return true;
	} else {
		return false;
	}
}

