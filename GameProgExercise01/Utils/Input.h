//#pragma comment (lib, "dinput8.lib")
//#pragma comment (lib, "dxguid.lib")
//#include <dinput.h>

class Input
{
	public:
		void Initialise();
		void Update();
		void Shutdown();

	private:
		DirectX::Keyboard* m_keyboard;
};