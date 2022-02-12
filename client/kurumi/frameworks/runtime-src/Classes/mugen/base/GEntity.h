#pragma once

#include "GComponent.h"

NS_G_BEGIN

class GEntity : public GObject
{
public:

	GEntity();

	virtual ~GEntity();

	void addComponent(GComponent* component);

	void removeComponent(const std::string& name);

	GComponent* getComponent(const std::string& name);

public:

	void update();

	//void lastUpdate();

private:

	void removeAllComponents();

private:

	G_SYNTHESIZE(uint32_t, m_id, Id);

	std::vector<GComponent*> m_components;
	std::unordered_map<std::string, GComponent*> m_componentMap;

	G_SYNTHESIZE(fixedPoint, m_timeScale, TimeScale);
	G_SYNTHESIZE(fixedPoint, m_elapsed, Elapsed);
};


NS_G_END
