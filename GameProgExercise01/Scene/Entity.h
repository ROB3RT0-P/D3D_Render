#pragma once

namespace scene
{

	struct Vertex
	{
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT4 color;
	};

// Base class for all entities in the scene - handles setting of world matrix etc..
class Entity abstract
{
public:
	Entity();
	~Entity();

	virtual void					Initialise();
	virtual void					Shutdown();

	virtual void					Update();
	virtual void					Render();

	void					SetPosition(const DirectX::XMVECTOR position);
	void					SetOrientation( const DirectX::XMMATRIX& orientation );
	void					SetScale(const float scale);

protected:
	ID3D11InputLayout*		m_inputLayout;
	ID3D11VertexShader*		m_vertexShader;
	ID3D11PixelShader*		m_pixelShader;
	ID3D11Buffer*			m_vertexBuffer;
	ID3D11Buffer*			m_constantBuffer;

	DirectX::XMVECTORF32	m_position;
	DirectX::XMMATRIX		m_orientation;
	float					m_scale;
};

} // namespace scene
