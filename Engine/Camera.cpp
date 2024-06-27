#include "pch.h"
#include "Camera.h"
#include "Viewport.h"

matx Camera::SView = matx::Identity;
matx Camera::SProj = matx::Identity;

Camera::Camera(f32 Near, f32 Far, f32 Fov)
	: Component(EComponentType::CAMERA), _near(Near), _far(Far), _fov(Fov)
{
	_width  = DX->GetViewport().GetWidth();
	_height = DX->GetViewport().GetHeight();

	_proj = SProj = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
}

void Camera::Update()
{
	_view = SView = GetOwnerTransform()->GetWorldInv();
}
