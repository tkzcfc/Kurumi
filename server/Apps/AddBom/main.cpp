#include "GLibBase.h"

int removeBom(const std::string& file)
{
	int ret = 0;
	FILE* fp = fopen(file.c_str(), "rb");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		auto len = ftell(fp);
		if (len > 3)
		{
			unsigned char buf[3] = { 0 };
			fseek(fp, 0, SEEK_SET);
			fread(buf, 3, 1, fp);

			if (buf[0] == 0xef && buf[1] == 0xbb && buf[2] == 0xbf)
			{
				//printf("remove bom : %s\n", file.c_str());
				unsigned char* buf = new unsigned char[len];
				fseek(fp, 0, SEEK_SET);
				fread(buf, len, 1, fp);
				fclose(fp);

				FILE* fp = fopen(file.c_str(), "wb");
				if (fp)
				{
					fwrite(buf + 3, len - 3, 1, fp);
				}
				delete[]buf;
				ret = 1;
			}
		}

		if (fp)
			fclose(fp);
	}
	return ret;
}

int addBom(const std::string& file)
{
	int ret = 0;
	FILE* fp = fopen(file.c_str(), "rb");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		auto len = ftell(fp);
		if (len > 3)
		{
			unsigned char buf[3] = { 0 };
			fseek(fp, 0, SEEK_SET);
			fread(buf, 3, 1, fp);

			if (buf[0] == 0xef && buf[1] == 0xbb && buf[2] == 0xbf)
			{
			}
			else
			{
				//printf("add bom : %s\n", file.c_str());
				unsigned char* buf = new unsigned char[len + 3];
				fseek(fp, 0, SEEK_SET);
				fread(buf + 3, len, 1, fp);
				fclose(fp);

				buf[0] = 0xef;
				buf[1] = 0xbb;
				buf[2] = 0xbf;
				//printf("buf   %d  %d  %d\n", buf[0], buf[1], buf[2]);

				fp = fopen(file.c_str(), "wb");
				if (fp)
				{
					fwrite(buf, len + 3, 1, fp);
				}
				delete[]buf;
				ret = 1;
			}
		}

		if (fp)
			fclose(fp);
	}
	return ret;
}


int main(int argc, char** argv)
{
	if (argc == 3)
	{
		if (strcmp(argv[1], "-a") == 0)
		{
			return addBom(argv[2]);
		}
		else if (strcmp(argv[1], "-r") == 0)
		{
			return removeBom(argv[2]);
		}
	}
	printf("add bom: addBOM -a file\n");
	printf("remove bom: addBOM -r file\n");
	system("pause");
	return EXIT_SUCCESS;
}
