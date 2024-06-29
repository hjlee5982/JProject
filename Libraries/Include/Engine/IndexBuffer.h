#pragma once

class IndexBuffer
{
public:
	 IndexBuffer() {}
	~IndexBuffer() {}
public:
	ComPtr<ID3D11Buffer> GetBuffer()
	{
		return _indexBuffer;
	}
public:
	u32 GetStride()
	{
		return _stride;
	}
	u32 GetIndexCount()
	{
		return _indexCount;
	}
	u32 GetOffset()
	{
		return _offset;
	}
public:
	void Create(const vector<u32>& indices)
	{
		_stride     = sizeof(u32);
		_indexCount = static_cast<u32>(indices.size());

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		{
			desc.Usage     = D3D11_USAGE_IMMUTABLE;
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			desc.ByteWidth = (u32)(_stride * _indexCount);
		}

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = indices.data();

		HRESULT hr = DEVICE->CreateBuffer(&desc, &data, _indexBuffer.GetAddressOf());
		CHECK(hr);
	}
public:
	void PushData()
	{
		CONTEXT->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}
private:
	ComPtr<ID3D11Buffer> _indexBuffer;
private:
	u32 _stride     = 0;
	u32 _offset     = 0;
	u32 _indexCount = 0;
};

