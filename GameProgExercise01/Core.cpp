#include "GameProgExercise01.h"
#include "Core.h"
#include "Scene\Scene.h"

static Core* g_core = nullptr;

Core* Core::Get()
{
	return g_core;
}

Core::Core() noexcept( false ) : 
	m_deviceResources( nullptr ),
	m_scene( nullptr )
{
	// DirectX Tool Kit supports all feature levels
	m_deviceResources = new DX::DeviceResources(
		DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_D24_UNORM_S8_UINT, 2,
		D3D_FEATURE_LEVEL_9_1 );
	m_deviceResources->RegisterDeviceNotify( this );

	ASSERT(g_core == nullptr, "A core object already exists.\n");
	g_core = this;
}

Core::~Core()
{
	delete m_deviceResources;
	g_core = nullptr;
}

// Perform any one-time initialisation
void Core::Initialise( HWND window, int width, int height )
{
	m_deviceResources->SetWindow( window, width, height );

	m_deviceResources->CreateDeviceResources();
	CreateDeviceDependentResources();

	m_deviceResources->CreateWindowSizeDependentResources();
	CreateWindowSizeDependentResources();

	m_scene = new Scene();
	m_scene->Initialise();
}

// Clear up and perform any closing actions
void Core::Shutdown()
{
	if (m_scene != nullptr)
	{
		m_scene->Shutdown();
	}
	delete m_scene;
	m_scene = nullptr;
}

// Each frame update
void Core::Update()
{
	// Update the scene
	if( m_scene != nullptr )
		m_scene->Update();
}

// Render the world
void Core::Render()
{
	Clear();

	// Draw the scene
	if( m_scene != nullptr )
		m_scene->Render();

	// Show the new frame.
	m_deviceResources->Present();
}

void Core::Clear()
{
	// Clear the views
	ID3D11DeviceContext1* const context = m_deviceResources->GetD3DDeviceContext();
	ID3D11RenderTargetView* const renderTarget = m_deviceResources->GetRenderTargetView();
	ID3D11DepthStencilView* const depthStencil = m_deviceResources->GetDepthStencilView();

	context->ClearRenderTargetView( renderTarget, DirectX::Colors::CornflowerBlue );
	context->ClearDepthStencilView( depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0 );

	context->OMSetRenderTargets( 1, &renderTarget, depthStencil );

	// Set the viewport.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports( 1, &viewport );
}

void Core::OnDeviceLost()
{
}

void Core::OnDeviceRestored()
{
}

void Core::CreateDeviceDependentResources()
{
}

void Core::CreateWindowSizeDependentResources()
{
}
