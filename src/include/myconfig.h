#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <tr1/unordered_map>

class Config
{
	typedef std::tr1::unordered_map<std::string, std::string> un_map;
public:
	bool open_config();
	static Config& instance();
	bool get_str_conf(const std::string &key, std::string &value);
	bool get_int_conf(const std::string &key, int &value);

private:
	Config();
	virtual ~Config();

	un_map conf;

	void trim(std::string& s);

};

#endif
