project(uchardet)

set(
	UCHARDET_HEADERS
	src/uchardet.h
)

set(
	UCHARDET_SOURCES
	src/CharDistribution.cpp
	src/JpCntx.cpp
	src/LangModels/LangBulgarianModel.cpp
	src/LangModels/LangRussianModel.cpp
	src/LangModels/LangEsperantoModel.cpp
	src/LangModels/LangFrenchModel.cpp
	src/LangModels/LangGermanModel.cpp
	src/LangModels/LangGreekModel.cpp
	src/LangModels/LangHungarianModel.cpp
	src/LangModels/LangHebrewModel.cpp
	src/LangModels/LangThaiModel.cpp
	src/LangModels/LangTurkishModel.cpp
	src/nsHebrewProber.cpp
	src/nsCharSetProber.cpp
	src/nsBig5Prober.cpp
	src/nsEUCJPProber.cpp
	src/nsEUCKRProber.cpp
	src/nsEUCTWProber.cpp
	src/nsEscCharsetProber.cpp
	src/nsEscSM.cpp
	src/nsGB2312Prober.cpp
	src/nsMBCSGroupProber.cpp
	src/nsMBCSSM.cpp
	src/nsSBCSGroupProber.cpp
	src/nsSBCharSetProber.cpp
	src/nsSJISProber.cpp
	src/nsUTF8Prober.cpp
	src/nsLatin1Prober.cpp
	src/nsUniversalDetector.cpp
	src/uchardet.cpp
)


set (UCHARDET_STATIC_TARGET uchardet)

add_library(
        ${UCHARDET_STATIC_TARGET}
        STATIC
        ${UCHARDET_SOURCES}
)

include(src/symbols.cmake)


target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

#add_subdirectory(src/tools)
