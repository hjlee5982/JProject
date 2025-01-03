#pragma once

class OutlineRenderer
{
public:
	OutlineRenderer();
	~OutlineRenderer();
public:
	void Render(matx ownerWorldMatrix, sptr<Mesh> mesh);
public:
	f32 GetThickness()
	{
		return _thickness;
	}
public:
	void SetThickness(f32 thickness)
	{
		_thickness = thickness;
	}
private:
	f32 _thickness = 0.06;
};

