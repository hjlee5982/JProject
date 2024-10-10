#pragma once

#include "Component.h"

class BoxCollider final : public Component
{
public:
	BoxCollider();
	virtual ~BoxCollider() = default;
public:
	virtual void Render() override;
public:
	bool RayIntersectsOBB(vec3 dir, vec3 origin);
public:
	vec3 GetPosition() { return _transform->GetPosition(); }
	vec3 GetScale   () { return _transform->GetScale();    }
	vec3 GetRotation() { return _transform->GetRotation(); }
public:
	void SetPosition(const vec3& position) { _transform->SetPosition(position); UpdateOBB(); }
	void SetScale   (const vec3& scale)    { _transform->SetScale   (scale);    UpdateOBB(); }
	void SetRotation(const vec3& roation)  { _transform->SetRotation(roation);  UpdateOBB(); }
private:
	void UpdateOBB();
private:
	// ·»´õ¿ë ¸Å½Ã, ½¦ÀÌ´õ, Æ®·£½ºÆû
	sptr<Mesh>      _mesh;
	sptr<Shader>    _shader;
	sptr<Transform> _transform;
private:
	vec3 _center;
	vec3 _halfSize;
};

