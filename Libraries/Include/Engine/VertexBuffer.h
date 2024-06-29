#pragma once

class VertexBuffer
{
public:
	 VertexBuffer() {}
	~VertexBuffer() {}
public:
	ComPtr<ID3D11Buffer> GetBuffer()
	{
		return _vertexBuffer;
	}
public:
	u32 GetStride()
	{
		return _stride;
	}
	u32 GetVertexCount()
	{
		return _vertexCount;
	}
	u32 GetOffset()
	{
		return _offset;
	}
	u32 GetSlot()
	{
		return _slot;
	}
public:
	template<typename T>
	void Create(const vector<T>& vertices, u32 slot = 0, bool cpuWrite = false, bool gpuWrite = false)
	{
		_stride      = sizeof(T);
		_vertexCount = static_cast<u32>(vertices.size());

		_slot     = slot;
		_cpuWrite = cpuWrite;
		_gpuWrite = gpuWrite;

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		{
			desc.ByteWidth = static_cast<u32>(_stride * _vertexCount);
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			if (_cpuWrite == false && _gpuWrite == false)
			{
				desc.Usage = D3D11_USAGE_IMMUTABLE; // CPU Read, GPU Read
			}
			else if (cpuWrite == true && gpuWrite == false)
			{
				desc.Usage = D3D11_USAGE_DYNAMIC;   // CPU Write, GPU Read 
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			}
			else if (cpuWrite == false && gpuWrite == true)
			{
				desc.Usage = D3D11_USAGE_DEFAULT; // CPU Read, GPU Write
			}
			else
			{
				desc.Usage = D3D11_USAGE_STAGING;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
			}
		}

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = vertices.data();

		HRESULT hr = DEVICE->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf());
		CHECK(hr);
	}
	void PushData()
	{
		CONTEXT->IASetVertexBuffers(_slot, 1, _vertexBuffer.GetAddressOf(), &_stride, &_offset);
	}
private:
	ComPtr<ID3D11Buffer> _vertexBuffer;
private:
	u32 _stride       = 0;
	u32 _vertexCount  = 0;
	u32 _offset       = 0;
	u32 _slot         = 0;
private:
	bool _cpuWrite;
	bool _gpuWrite;
};

