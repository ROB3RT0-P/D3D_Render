#include "GameProgExercise01.h"
#include "Core.h"
#include "Bee.h"
#include "Scene\Scene.h"
#include "Scene\Entities\Flower.h"


namespace scene
{

    void Bee::Initialise()
    {
        Entity::Initialise();
        SetScale(0.2f);

        float zPos = static_cast<float>(utils::Rand() % 5);
        DirectX::XMVECTOR startPos = DirectX::XMVECTOR{ -1.0f, 3.0f, zPos };
        SetPosition( startPos );

        Core* const core = Core::Get();

        const DX::DeviceResources* const deviceResources = core->GetDeviceResources();

        HRESULT hr = 0;

        const float scale = 0.1f;

        auto device = deviceResources->GetD3DDevice();

        // Create vertex buffer.
        static const Vertex s_vertexData[NumVertices] =
        {
            //Body
            { { 0.0f, 0.0f,  0.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //1
            { { 0.0f, 1.0f,  0.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //2
            { { 1.0f, 0.0f,  0.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //3
            { { 1.0f, 1.0f,  0.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //4
            { { 1.0f, 0.0f,  1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //5
            { { 1.0f, 1.0f,  1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //6
            { { 0.0f, 0.0f,  1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //7
            { { 0.0f, 1.0f,  1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //8
            { { 0.0f, 0.0f,  0.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //9
            { { 0.0f, 1.0f,  0.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //10
            { { 1.0f, 1.0f,  0.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //11
            { { 0.0f, 1.0f,  1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //12
            { { 1.0f, 1.0f,  1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //13

            //Stripe
            { { 1.01f, 0.0f,  0.4f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },    //1
            { { 1.01f, 0.0f,  0.6f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },    //2
            { { 1.01f, 1.01f,  0.4f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },   //3
            { { 1.01f, 1.01f,  0.6f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },   //4
            { { -0.01f, 1.01f,  0.4f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },  //5
            { { -0.01f, 1.01f,  0.6f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },  //6
            { { -0.01f, 0.0f,  0.4f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },   //7
            { { -0.01f, 0.0f,  0.6f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } }    //8
        };

        D3D11_SUBRESOURCE_DATA initialData = {};
        initialData.pSysMem = s_vertexData;

        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.ByteWidth = sizeof(s_vertexData);
        bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.StructureByteStride = sizeof(Vertex);


        hr = device->CreateBuffer(&bufferDesc, &initialData,
            &m_vertexBuffer);
        ASSERT_HANDLE(hr);
    }

    DirectX::XMVECTORF32 newPos = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f };
    
    void Bee::PosIter()
    {
        const Core* const core = Core::Get();
        Scene* scene = core->GetScene();
        Flower* const flower = scene->GetFlower();
        DirectX::XMVECTOR flowerPosition = flower->GetPosition();

        float timeStep = utils::Timers::GetFrameTime();
        
        //S = 1.0f
        //D = P2 - P1
        //Normalise(D) = Dn
        //Dn * S
        DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(flowerPosition, m_position);
        DirectX::XMVECTOR normalisedDir = DirectX::XMVector3Normalize(direction);
        DirectX::XMVECTOR flowerVelocity = DirectX::XMVectorScale(normalisedDir, speed);

        //S1 = S0 + V * T
        DirectX::XMVECTORF32 NewPos = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f };
        //NewPos = DirectX::XMVectorScale( Velocity , timeStep );
        NewPos.v = DirectX::XMVectorScale( flowerVelocity, timeStep );
        NewPos.v += m_position;
        SetPosition(NewPos);

        DirectX::XMVECTORF32 curPos = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f };
        curPos.v = NewPos;

        DirectX::XMVECTORF32 checkPosMin = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f };
        checkPosMin.v = flowerPosition;
        checkPosMin.f[0] -= 0.01f;
        checkPosMin.f[1] -= 0.01f;
        checkPosMin.f[2] -= 0.01f;

        DirectX::XMVECTORF32 checkPosMax = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f };
        checkPosMax.v = flowerPosition;
        checkPosMax.f[0] += 0.01f;
        checkPosMax.f[1] += 0.01f;
        checkPosMax.f[2] += 0.01f;

        if (curPos.f[0] > checkPosMin.f[0] && curPos.f[0] < checkPosMax.f[0] && curPos.f[1] > checkPosMin.f[1] 
            && curPos.f[1] < checkPosMax.f[1] && curPos.f[2] > checkPosMin.f[2] && curPos.f[2] < checkPosMax.f[2])
        {
            m_outOfBounds = true;
        }
    }
 
    void Bee::Update()
    {
        PosIter();
    }
    
    bool Bee::OutOfBounds()
    {
        return m_outOfBounds;
    }

    void Bee::Render()
    {
        Entity::Render();

        Core* const core = Core::Get();

        const DX::DeviceResources* const deviceResources = core->GetDeviceResources();

        auto context = deviceResources->GetD3DDeviceContext();


        UINT strides = sizeof(Vertex);
        UINT offsets = 0;
        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
        context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &strides, &offsets);

        // Draw triangle.
        context->Draw(NumVertices, 0);
    }
}