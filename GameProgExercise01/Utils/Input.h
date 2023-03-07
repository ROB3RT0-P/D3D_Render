class Input
{
	public:
		void Initialise();
		void Update();
		void Shutdown();

	private:
		DirectX::Keyboard* m_keyboard;
};