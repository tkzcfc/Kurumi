#include "cmd.h"

namespace cmd
{
	std::vector<std::string> parse_cmd_params(int argc, char** argv)
	{
		std::vector<std::string> out;
		for (int i = 0; i < argc; ++i)
		{
			out.push_back(argv[i]);
		}
		return out;
	}

	std::vector<std::string> parse_cmd_params(const std::string& cmd)
	{
		std::vector<std::string> out;

		bool begin_res = false;
		int begin_pos = 0;
		for (auto i = 0; i < cmd.size(); ++i)
		{
			if (!begin_res)
			{
				if (cmd[i] != ' ')
				{
					begin_res = true;
					begin_pos = i;
				}
			}
			else
			{
				if (cmd[i] == ' ')
				{
					out.push_back(cmd.substr(begin_pos, i - begin_pos));
					begin_res = false;
				}
			}
		}

		if (begin_res)
		{
			out.push_back(cmd.substr(begin_pos, cmd.size() - begin_pos));
		}

		return out;
	}

	std::string try_get(std::vector<std::string>& params, const std::string& name, const std::string& defaultValue)
	{
		std::string key = "-" + name;
		for (auto i = 0; i < params.size() - 1; ++i)
		{
			if (params[i] == key)
			{
				return params[i + 1];
			}
		}
		return defaultValue;
	}


	bool check_cmd_is_number(const std::string& cmd)
	{
		for (int i = 0; i < cmd.size(); ++i)
		{
			if (cmd[i] < '0' || cmd[i] > '9')
				return false;
		}
		return true;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	static std::vector<std::string> g_cmd_params;

	std::vector<std::string>& init_cmd_params(int argc, char** argv)
	{
		g_cmd_params = parse_cmd_params(argc, argv);
		return g_cmd_params;
	}

	std::string try_get(const std::string& name, const std::string& defaultValue)
	{
		return try_get(g_cmd_params, name, defaultValue);
	}
}



