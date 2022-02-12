#pragma once

#include "GObject.h"

NS_G_BEGIN

#define G_DEFINE_COMPONENT(type) virtual const char* name() override { return #type; };

class GEntity;
class GComponent : public GObject
{
public:

	GComponent();

	virtual ~GComponent();

	virtual void onAdd() {};

	virtual void onRemove() {};

	virtual void onUpdate() {}

	//virtual void onLastUpdate() {}

	virtual const char* name() = 0;

	void addComponent(GComponent* component);

	void removeComponent(const std::string& name);

	GComponent* getComponent(const std::string& name);

	GEntity* getEntity();

public:

	virtual void serialize(GByteBuffer& byteBuffer) override;

	virtual bool deserialize(GByteBuffer& byteBuffer) override;

private:
	friend class GEntity;
	GEntity* m_pEntity;
};

NS_G_END
