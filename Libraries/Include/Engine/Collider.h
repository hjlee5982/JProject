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
	virtual bool Raycast(Ray ray) = 0;
public:
	vec3 GetPosition() { return _transform->GetPosition(); }
	vec3 GetScale   () { return _transform->GetScale();    }
	vec3 GetRotation() { return _transform->GetRotation(); }
public:
	void SetPosition(const vec3& position) { _transform->SetPosition(position); }
	void SetScale   (const vec3& scale)    { _transform->SetScale(scale);       }
	void SetRotation(const vec3& roation)  { _transform->SetRotation(roation);  }
protected:
	sptr<Mesh>      _mesh;
	sptr<Shader>    _shader;
	sptr<Transform> _transform;
};

