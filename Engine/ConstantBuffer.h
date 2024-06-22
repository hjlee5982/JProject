#pragma once

template<typename T>
class ConstantBuffer
{
public:
	 ConstantBuffer() { }
	~ConstantBuffer() { }
public:
	ComPtr<ID3D11Buffer> GetComPtr() 
	{
		return mConstantBuffer;
	}
public:
	void Create()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		{
			desc.Usage          = D3D11_USAGE_DYNAMIC; // CPU_Write + GPU_Read
			desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
			desc.ByteWidth      = sizeof(T);
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}

		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, mConstantBuffer.GetAddressOf());
		CHECK(hr);
	}
	void CopyData(const T& data)
	{
		D3D11_MAPPED_SUBRESOURCE subResource;
		ZeroMemory(&subResource, sizeof(subResource));

		CONTEXT->Map(mConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		::memcpy(subResource.pData, &data, sizeof(data));
		CONTEXT->Unmap(mConstantBuffer.Get(), 0);
	}
private:
	ComPtr<ID3D11Buffer> mConstantBuffer;
};
