#pragma once

class Renderer;

class GameDevice
{
public:
	static void initialize();
	static void update();
	static void shutdown();

	static Renderer* getRenderer();

private:
	GameDevice();
	~GameDevice();

	//�R�s�[�֎~
	GameDevice(const GameDevice& other);
	GameDevice& operator = (const GameDevice& other);

private:
	static GameDevice* instance;

	Renderer* m_pRenderer;
};