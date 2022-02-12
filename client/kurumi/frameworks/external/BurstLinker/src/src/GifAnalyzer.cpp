//
// Created by succlz123 on 2017/11/4.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <cassert>
#include "GifAnalyzer.h"
#include "Logger.h"

using namespace blk;

static const size_t BUF_SIZE = 1024;
static const std::string analyzeError = "Parse failed\n";
static std::string result;

static void readNbytes(std::stringstream& file, uint8_t *buf, size_t nbytes) {
	size_t retCode = file.readsome((char*)buf, nbytes);
	if (retCode == nbytes) {
		buf[nbytes] = 0;
	}
	else {
		result += analyzeError;
	}
}

void print_result(const char* format, ...)
{
	constexpr auto BUFFER_LENGTH = 512;
	va_list args;
	std::string buffer(BUFFER_LENGTH, '\0');
	va_start(args, format);
	int nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
	va_end(args);
	if (nret >= 0) {
		if ((unsigned int)nret < buffer.length()) {
			buffer.resize(nret);
		}
		else if ((unsigned int)nret > buffer.length()) {
			buffer.resize(nret);
			va_start(args, format);
			nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
			va_end(args);
			assert(nret == buffer.length());
		}
	}
	else {
		do {
			buffer.resize(buffer.length() * 3 / 2);
			va_start(args, format);
			nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
			va_end(args);
		} while (nret < 0);
		buffer.resize(nret);
	}
	result += buffer;
}

static void analyzeColorTable(std::stringstream& file, unsigned table_size) {
	uint8_t buf[BUF_SIZE] = { 0 };
	print_result("%8s%8s%8s%8s\n", "INDEX", "RED", "GREEN", "BLUE");
	print_result("--------------------------------\n");
	for (unsigned index = 0; index < table_size; ++index) {
		readNbytes(file, buf, 3);
		print_result("%8u%8u%8u%8u\n", index, buf[0], buf[1], buf[2]);
	}
}

static unsigned analyzeDataBlock(std::stringstream& file) {
	unsigned totalSize = 0;
	uint8_t buf[BUF_SIZE] = { 0 };
	for (;;) {
		readNbytes(file, buf, 1);
		unsigned blockSize = *buf;
		if (blockSize) {
			readNbytes(file, buf, blockSize);
			totalSize += blockSize;
		}
		else {
			break;
		}
	}
	if (totalSize) {
		print_result("Data Block Size: %u (%.2fKB)\n", totalSize, (float)totalSize / 1024);
	}
	return totalSize;
}

static void analyzeApplicationExtension(std::stringstream& file) {
	uint8_t buf[BUF_SIZE] = { 0 };

	readNbytes(file, buf, 1);
	unsigned blockSize = *buf;
	if (blockSize != 11) {
		result += analyzeError;
		return;
	}

	readNbytes(file, buf, 8);
	const char *applicationIdentifier = (const char *)buf;
	print_result("Application Identifier: %s\n", applicationIdentifier);
	int isNetscapeExtension = memcmp(applicationIdentifier, "NETSCAPE", strlen(applicationIdentifier)) == 0;

	readNbytes(file, buf, 3);
	print_result("Application Authentication Code: 0x%02X%02X%02X\n", buf[0], buf[1], buf[2]);

	if (isNetscapeExtension) {
		memset(buf, 0, BUF_SIZE);
		readNbytes(file, buf, 1);
		blockSize = *buf;
		if (blockSize != 3) {
			result += analyzeError;
			return;
		}

		readNbytes(file, buf, 1);
		unsigned loopEnabled = *buf;
		print_result("Loop Enabled: %u\n", loopEnabled);

		readNbytes(file, buf, 2);
		unsigned loopCount = buf[0] + (buf[1] << 8);
		print_result("Loop Count: %u\n", loopCount);
	}
	analyzeDataBlock(file);
}

static void analyzeGraphicControlExtension(std::stringstream& file) {
	uint8_t buf[BUF_SIZE] = { 0 };

	readNbytes(file, buf, 1);
	unsigned blockSize = *buf;
	if (blockSize != 4) {
		result += analyzeError;
		return;
	}

	readNbytes(file, buf, 1);
	unsigned disposalMethod = (*buf & 0b00011100) >> 2;
	print_result("Disposal Method: %u\n", disposalMethod);
	unsigned userInputFlag = (*buf & 0b00000010) >> 1;
	print_result("User Input Flag: %u\n", userInputFlag);
	unsigned transparentColorFlag = *buf & 0b00000001;
	print_result("Transparent Color Flag: %u\n", transparentColorFlag);

	readNbytes(file, buf, 2);
	unsigned delayTime = buf[0] + (buf[1] << 8);
	print_result("Delay Time: %u (%.2fs)\n", delayTime, (float)delayTime / 100);

	readNbytes(file, buf, 1);
	unsigned transparencyIndex = *buf;
	print_result("Transparency Index: %u\n", transparencyIndex);

	analyzeDataBlock(file);
}

static void analyzeCommentExtension(std::stringstream& file) {
	analyzeDataBlock(file);
}

static void analyzeImage(std::stringstream& file, unsigned rawImageWidth, unsigned rawImageHeight) {
	std::string ret;
	uint8_t buf[BUF_SIZE] = { 0 };

	readNbytes(file, buf, 2);
	unsigned imageLeftPosition = buf[0] + (buf[1] << 8);
	print_result("Image left Position: %u\n", imageLeftPosition);

	readNbytes(file, buf, 2);
	unsigned imageTopPosition = buf[0] + (buf[1] << 8);
	print_result("Image Top Position: %u\n", imageTopPosition);

	readNbytes(file, buf, 2);
	unsigned imageWidth = buf[0] + (buf[1] << 8);
	print_result("Image Width: %u\n", imageWidth);

	readNbytes(file, buf, 2);
	unsigned imageHeight = buf[0] + (buf[1] << 8);
	print_result("Image Height: %u\n", imageHeight);

	readNbytes(file, buf, 1);
	unsigned localColorTableFlag = (*buf & 0b10000000) >> 7;
	print_result("Local Color Table Flag: %u\n", localColorTableFlag);
	unsigned interlaceFlag = (*buf & 0b01000000) >> 6;
	print_result("Interlace Flag: %u\n", interlaceFlag);
	unsigned sortFlag = (*buf & 0b00100000) >> 5;
	print_result("Sort Flag: %u\n", sortFlag);
	unsigned sizeOfLocalColorTable = *buf & 0b00000111;
	unsigned realSizeOfLocalColorTable = 2 << sizeOfLocalColorTable;
	print_result("Size of Local Color Table: %u (%u)\n", sizeOfLocalColorTable, realSizeOfLocalColorTable);

	if (localColorTableFlag) {
		print_result("Local Color Table:\n");
		print_result("\n");
		analyzeColorTable(file, realSizeOfLocalColorTable);
		print_result("\n");
	}

	readNbytes(file, buf, 1);
	unsigned lzwMinimumCodeSize = *buf;
	print_result("LZW Minimum Code Size: %u\n", lzwMinimumCodeSize);

	unsigned rawSizeImageDataLength = rawImageWidth * rawImageHeight * lzwMinimumCodeSize / 8;
	unsigned uncompressedImageDataLength = imageWidth * imageHeight * lzwMinimumCodeSize / 8;
	unsigned compressedImageDataLength = analyzeDataBlock(file);
	print_result("Compression Rate: %.2f (%.2f)\n",
		(float)uncompressedImageDataLength / compressedImageDataLength,
		(float)rawSizeImageDataLength / compressedImageDataLength);
}

static void analyzeGif(std::stringstream& file) {
	std::string ret;
	uint8_t buf[BUF_SIZE] = { 0 };

	// fixed-length header

	print_result("================================\n");
	print_result("Header\n");
	print_result("================================\n");
	print_result("\n");

	readNbytes(file, buf, 3);
	print_result("Signature: %s\n", buf);

	readNbytes(file, buf, 3);
	print_result("Version: %s\n", buf);

	print_result("\n");

	// fixed-length Logical Screen Descriptor

	print_result("================================\n");
	print_result("Logical Screen Descriptor\n");
	print_result("================================\n");
	print_result("\n");

	readNbytes(file, buf, 2);
	unsigned logicalScreenWidth = buf[0] + (buf[1] << 8);
	print_result("Logical Screen Width: %u\n", logicalScreenWidth);

	readNbytes(file, buf, 2);
	unsigned logicalScreenHeight = buf[0] + (buf[1] << 8);
	print_result("Logical Screen Height: %u\n", logicalScreenHeight);

	readNbytes(file, buf, 1);
	unsigned globalColorTableFlag = (*buf & 0b10000000) >> 7;
	print_result("Global Color Table Flag: %u\n", globalColorTableFlag);
	unsigned colorResolution = (*buf & 0b01110000) >> 4;
	unsigned realColorResolution = colorResolution + 1;
	print_result("Color Resolution: %u (%u)\n", colorResolution, realColorResolution);
	unsigned sortFlag = (*buf & 0b00001000) >> 3;
	print_result("Sort Flag: %u\n", sortFlag);
	unsigned sizeOfGlobalColorTable = *buf & 0b00000111;
	unsigned realSizeOfGlobalColorTable = 2 << sizeOfGlobalColorTable;
	print_result("Size of Global Color Table: %u (%u)\n", sizeOfGlobalColorTable, realSizeOfGlobalColorTable);

	readNbytes(file, buf, 1);
	unsigned backgroundColorIndex = *buf;
	print_result("Background Color Index: %u\n", backgroundColorIndex);

	readNbytes(file, buf, 1);
	unsigned pixelAspectRatio = *buf;
	double realPixelAspectRatio = pixelAspectRatio ? ((double)pixelAspectRatio + 15.0) / 64.0 : 1.0;
	print_result("RGB Aspect Ratio: %u (%lf)\n", pixelAspectRatio, realPixelAspectRatio);

	unsigned rawImageDataLength = realColorResolution * logicalScreenWidth * logicalScreenHeight / 8;
	print_result("Raw Image Size: %u (%.2fKB)\n", rawImageDataLength, (float)rawImageDataLength / 1024);

	if (globalColorTableFlag) {
		print_result("Local Color Table:\n");
		print_result("\n");
		analyzeColorTable(file, realSizeOfGlobalColorTable);
		print_result("\n");
	}

	print_result("\n");

	// Data Stream

	print_result("================================\n");
	print_result("Data Stream\n");
	print_result("================================\n");
	print_result("\n");

	for (;;) {
		readNbytes(file, buf, 1);
		unsigned identifier = *buf;
		switch (identifier) {
		case 0x21: {
			readNbytes(file, buf, 1);
			unsigned extensionLabel = *buf;
			switch (extensionLabel) {
			case 0xFF:
				print_result("# Application Extension\n");
				analyzeApplicationExtension(file);
				print_result("\n");
				break;
			case 0xF9:
				print_result("# Graphic Control Extension\n");
				analyzeGraphicControlExtension(file);
				print_result("\n");
				break;
			case 0xFE:
				print_result("# Comment Extension\n");
				analyzeCommentExtension(file);
				print_result("\n");
				break;
			default:
				print_result("# Unknown Extension: 0x%02X\n", extensionLabel);
				break;
			}
			break;
		}
		case 0x2C: {
			print_result("# Image\n");
			analyzeImage(file, logicalScreenWidth, logicalScreenHeight);
			print_result("\n");
			break;
		}
		case 0x3B:
			print_result("# Trailer\n");
			return;
		default:
			print_result("# Unknown Block: 0x%02X\n", identifier);
			break;
		}
	}
}

std::string GifAnalyzer::showGifInfo(std::stringstream& file) {
	result = "";
	analyzeGif(file);
	return result;
}
