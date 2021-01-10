//#pragma once
//
//#include "GVirtualCamera.h"
//
//enum EMapLayerType
//{
//	BACKGROUND_NODE,
//	STAGE_NODE,
//	FOREGROUND_NODE,
//	COUNT
//};
//
//class GGameLayer : public Node
//{
//public:
//	GGameLayer();
//
//	virtual ~GGameLayer();
//
//	static GGameLayer * create();
//
//public:
//
//	void initMap();
//
//	Node* getMapNode(EMapLayerType type);
//
//	void setMapNode(EMapLayerType type, Node* node);
//
//	inline float getMapWidth() { return m_mapSize.width; }
//
//	inline float getMapHeight() { return m_mapSize.height; }
//	
//	void setViewSize(const Size& size);
//
//	void setVisionSize(const Size& visionSize);
//
//	inline GVirtualCamera* getVirtualCamera() { return m_camera; }
//
//public:
//
//	virtual void onExit()override;
//
//protected:
//
//	void initMapLua();
//
//	void clear();
//
//protected:
//
//	struct MapLayerInfo
//	{
//		Node* node;
//		Size size;
//
//		float sub_node_x;
//		float sub_node_y;
//	};
//	MapLayerInfo m_mapLayerInfoArr[EMapLayerType::COUNT];
//	Size m_mapSize;
//	Size m_visionSize;
//
//	Node* m_rootNode;
//	GVirtualCamera* m_camera;
//
//	float m_subMapX;
//	float m_subMapY;
//};
