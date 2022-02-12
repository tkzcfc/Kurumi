//
// Created by succlz123 on 2018/1/30.
//

#include "BurstLinker.h"
#include "GifAnalyzer.h"

using namespace blk;

bool BurstLinker::init(std::stringstream& out, uint16_t width, uint16_t height, uint32_t loopCount, uint32_t threadNum) {
    gifEncoder = std::unique_ptr<GifEncoder>(new GifEncoder());
    return gifEncoder->init(out, width, height, loopCount, threadNum);
}

bool BurstLinker::connect(std::vector<uint32_t> &image, uint32_t delay,
                          QuantizerType quantizerType, DitherType ditherType, int32_t transparencyOption,
                          uint16_t left, uint16_t top) {
    if (gifEncoder == nullptr) {
        return false;
    }
    std::vector<uint8_t> content;
    gifEncoder->addImage(image, delay, quantizerType, ditherType, transparencyOption, left, top, content);
    gifEncoder->flush(content);
    return true;
}

bool BurstLinker::connect(std::vector<std::vector<uint32_t>> &images, uint32_t delay,
                          QuantizerType quantizerType, DitherType ditherType, int32_t transparencyOption,
                          uint16_t left, uint16_t top) {
    if (gifEncoder == nullptr) {
        return false;
    }
    if (gifEncoder->threadPool)
    {
	    size_t size = images.size();
	    std::vector<std::future<std::vector<uint8_t>>> tasks;
	    for (int k = 0; k < size; ++k) {
	        auto result = gifEncoder->threadPool->enqueue([=, &images]() {
	            std::vector<uint8_t> content;
	            auto image = images[k];
	            gifEncoder->addImage(image, delay, quantizerType, ditherType, transparencyOption, left, top, content);
	            return content;
	        });
	        tasks.emplace_back(std::move(result));
	    }
	    for (auto &task : tasks) {
	        std::vector<uint8_t> result = task.get();
	        gifEncoder->flush(result);
	    }
    }
    else
    {
	    for (auto& image : images)
	    {
			std::vector<uint8_t> content;
			gifEncoder->addImage(image, delay, quantizerType, ditherType, transparencyOption, left, top, content);
			gifEncoder->flush(content);
	    }
    }
    return true;
}

void BurstLinker::release() {
    if (gifEncoder != nullptr) {
        gifEncoder->finishEncoding();
    }
}

std::string BurstLinker::analyzeGifInfo(std::stringstream& file) {
    return GifAnalyzer::showGifInfo(file);
}
