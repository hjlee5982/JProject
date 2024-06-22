#include "pch.h"
#include "Camera.h"
#include "Viewport.h"

Camera::Camera(f32 Near, f32 Far, f32 Fov)
	: Component(EComponentType::CAMERA), _near(Near), _far(Far), _fov(Fov)
{
	_width  = DX->GetViewport().GetWidth();
	_height = DX->GetViewport().GetWidth();
}

void Camera::Update()
{
	_view = SView = GetOwnerTransform()->GetWorldInv();
	_proj = SProj = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
}
