#pragma once

#include "Component.h"

class Collider abstract : public Component
{
public:
	Collider();
	virtual ~Collider() = default;
public:
	virtual void Render() override;
public:
	vec3 GetPosition() { return _transform->GetPosition(); }
	vec3 GetScale   () { return _transform->GetScale();    }
	vec3 GetRotation() { return _transform->GetRotation(); }
	bool IsTrigger  () { return _isTrigger; }
public:
	void SetPosition(const vec3& position) { _transform->SetPosition(position); }
	void SetScale   (const vec3& scale)    { _transform->SetScale(scale);       }
	void SetRotation(const vec3& roation)  { _transform->SetRotation(roation);  }
	void SetTrigger (bool isTrigger)       { _isTrigger = isTrigger; }
protected:
	void SetColor();
protected:
	bool _isTrigger = false;
	vec4 _color     = vec4{ 0.f, 1.f, 0.f, 1.f };
protected:
	sptr<Mesh>      _mesh;
	sptr<Shader>    _shader;
	sptr<Transform> _transform;
};

