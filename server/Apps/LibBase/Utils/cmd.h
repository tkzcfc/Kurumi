#pragma once

#include <string>
#include <vector>

namespace cmd
{
	std::vector<std::string>& init_cmd_params(int argc, char** argv);

	std::vector<std::string> parse_cmd_params(int argc, char** argv);

	std::vector<std::string> parse_cmd_params(const std::string& cmd);

	std::string try_get(const std::string& name, const std::string& defaultValue = "");

	std::string try_get(std::vector<std::string>& params, const std::string& name, const std::string& defaultValue = "");

	bool check_cmd_is_number(const std::string& cmd);
}