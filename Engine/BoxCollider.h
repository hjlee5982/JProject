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
	vec3 GetPosition() { return _transform->GetScale(); }
	vec3 GetScale   () { return _transform->GetScale(); }
	vec3 GetRotation() { return _transform->GetScale(); }
public:
	void SetPosition(const vec3& position) { _transform->SetScale(position); }
	void SetScale   (const vec3& scale)    { _transform->SetScale(scale);    }
	void SetRotation(const vec3& roation)  { _transform->SetScale(roation);  }
private:
	void ColliderRender();
private:
	// ·»´õ¿ë ¸Å½Ã, ½¦ÀÌ´õ, Æ®·£½ºÆû
	sptr<Mesh>      _mesh;
	sptr<Shader>    _shader;
	sptr<Transform> _transform;
};

