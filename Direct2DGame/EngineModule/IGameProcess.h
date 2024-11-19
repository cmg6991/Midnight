#pragma once


/// <summary>
/// 게임 프로세스의 인터페이스 
///  
/// 2023.7.19 19:13 gitae
/// </summary>
class IGameProcess abstract
{
public:
	IGameProcess();
	~IGameProcess();

	virtual void Initalize(D2DRenderer* _renderer, HWND _main)=0;
	virtual void Process() =0;
	virtual void Finalize() = 0;

	virtual bool IsGameRunning() = 0;
};

