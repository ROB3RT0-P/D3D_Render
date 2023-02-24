#pragma once

#include "DX\DeviceResources.h"

class Scene;

namespace DX
{
	class View;
}

class Core final : public DX::IDeviceNotify
{
public:
	Core() noexcept( false );
	~Core();

	static Core*	Get();

	void			Initialise( HWND window, int width, int height );
	void			Shutdown();

	void			Update();
	void			Render();

	virtual void	OnDeviceLost() override;
	virtual void	OnDeviceRestored() override;

	DX::DeviceResources* GetDeviceResources() const
	{
		return m_deviceResources;
	}

private:
	void			Clear(); // Clear the screen

	void			CreateDeviceDependentResources();
	void			CreateWindowSizeDependentResources();

	DX::DeviceResources*	m_deviceResources; // The D3D objects
	DX::View* m_view; // Code relating the the camera

	Scene*			m_scene; // An object that contains all the game world entities
};

