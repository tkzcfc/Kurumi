#include "GLibBase.h"
#include "uchardet.h"



#define BUFFER_SIZE 65536

char buffer[BUFFER_SIZE];

std::string detect(FILE * fp)
{
	uchardet_t handle = uchardet_new();

	while (!feof(fp))
	{
		size_t len = fread(buffer, 1, BUFFER_SIZE, fp);
		int retval = uchardet_handle_data(handle, buffer, len);
		if (retval != 0)
		{
			fprintf(stderr, "Handle data error.\n");
			return "unknown";
		}
	}
	uchardet_data_end(handle);

	std::string out = "unknown";

	const char * charset = uchardet_get_charset(handle);
	if (*charset)
		out = charset;

	uchardet_delete(handle);

	return out;
}

int main(int argc, char ** argv)
{
	if (argc == 1)
		return -1;

	auto filename = argv[1];

	FILE* fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		fprintf(stderr, "Handle error.\n");
		return -1;
	}

	std::string value = detect(fp);
	printf("code:%s\n", value.c_str());

	fclose(fp);
	return 0;
}
