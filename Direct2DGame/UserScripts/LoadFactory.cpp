#include "UserScriptsPCH.h"
#include "LoadFactory.h"
#include "Factory.h"

LoadFactory::LoadFactory(const ManagerSet* _managerSet)
	:m_managerSet(_managerSet)
	,m_player(nullptr)
	,m_rabbit(nullptr)
{

}

LoadFactory::~LoadFactory()
{

}

void LoadFactory::Load(const wstring& _filePath)
{
	std::wifstream file(_filePath);
	if (!file.is_open())	
	{
		assert(nullptr);
	}

	wstring line;
	while (std::getline(file, line))
	{
		std::wistringstream iss(line);
		int index;
		float x, y;
		static int clickedImageIndex = -1;

		if (iss >> index >> x >> y)
		{
			CreateObject(index, Vector2(x, y));
		}
	}
	file.close();
}

void LoadFactory::CreateObject(int _index, Vector2 _position)
{
	GameObject* object = nullptr;
	
	// 팩토리 생성
	Factory factory(m_managerSet);
	factory.m_player = m_player;
	factory.m_rabbit = m_rabbit;
	factory.m_PlayerLife = m_hp;
	factory.m_clearCheck = m_clearCheck;

	Vector2 position = m_managerSet->GetCameraManager()->ScreenToCamera(_position);

	if (_index == 0) // 배경화면 생략
	{
		return;
	}
	else if (_index == 1)// 플레이어
	{
		m_player->GetComponent<Transform>()->SetPosition(position);
	
		return;
	}
	else if (_index == 2) // 잘린 나무
	{
		object =  factory.CreateStamp(position);
	}
	else if (_index == 3)// 나뭇가지
	{
		object = factory.CreateBranch(position);
	}
	else if (_index == 4)// 나뭇잎
	{
		object = factory.CreateLeaf(position);
	}
	else if (_index == 5)// 버섯
	{
		object = factory.CreateMushroom(position);
	}
	else if (_index == 6) // 안개 커튼 창문
	{
		vector<GameObject*> fogWindow = factory.CreateFogWindow(position);
		for (int i = 0; i < static_cast<int>(fogWindow.size()); ++i)
		{
			m_objectContainer.push_back(fogWindow[i]);
			
		}
		return;
	}
 	else if (_index == 7) // 하녀
 	{
 		object = factory.CreateChaser(position);
 	}
	else if (_index == 8) // 깃털
	{
		object = factory.CreateFeather(position);
	}
	else if (_index == 9) // 일반 나무 발판 
	{
		object = factory.CreateNomalPlatform(position, false);
	}
	else if (_index == 10) // 뒤집은 나무 발판
	{
		object = factory.CreateNomalPlatform(position, true);
	}
	else if (_index == 11)
	{
		object = factory.CreateNomalPassPlatform(position);
	}
	else if (_index == 12) // 잎사귀 더미
	{
		object = factory.CreateLeafDummy(position);
	}
	else if (_index == 13) // 양초
	{
		object = factory.CreateCandle(position);
	}
	else if (_index == 14) // 빙판
	{
		object = factory.CreateSlideTile(position);
	}
	else if (_index == 15) // 고드름
	{
		object = factory.CreateIcicle(position, false);
	}
	else if (_index == 16) // 역고드름
	{
		object = factory.CreateIcicle(position, true);
	}
	else if (_index == 17) // 큰 고드름
	{
		object = factory.CreateBigIcicle(position, false);
	}
	else if (_index == 18) // 역 큰 고드름
	{
		object = factory.CreateBigIcicle(position, true);
	}
	else if (_index == 19) // 책
	{
		object = factory.CreateBook(position);
	}
	else if (_index == 20)  //쿠션
	{
		object = factory.CreateCushion(position);
	}
	else if (_index == 21) // 탁자
	{
		object = factory.CreateTable(position);
	}
	else if (_index == 22) // 실
	{
		vector<GameObject*> fogWindow = factory.CreateThread(position);
		for (int i = 0; i < static_cast<int>(fogWindow.size()); ++i)
		{
			m_objectContainer.push_back(fogWindow[i]);
		}
		return;
	}
	else if (_index == 23) // 반딧불이
	{
		object = factory.CreateFireFly(position);
	}
	else if (_index == 24) //창문틀
	{
		object = factory.CreateWindowFrame(position);
	}
	else if (_index == 25) //창문
	{
		object = factory.CreateDecoWindow(position);
	}
	else if (_index == 26) //토끼굴
	{
		object = factory.CreateRabbitTunnel(position);
	}
	else if (_index == 27) //의자
	{
		object = factory.CreateChair(position);
	}
	else if (_index == 28) //소리방석
	{
		object = factory.CreateSoundCushion(position);
	}
	else if (_index == 29) //inverse chaser
	{
		object = factory.CreateInverseChaser(position);
	}
	else if (_index == 30) // 샹들리에
	{
		object = factory.CreateChandelier(position);
	}
	else if (_index == 31) // 스탠트
	{
		object = factory.CreateStandLight(position);
	}
	else if (_index == 32) // 스탠트 스위치 발판
	{
		object = factory.CreateStandLightFootSwitch(position);
	}
	else if (_index == 33) // 아무것도 없는 스탠드
	{
		object = factory.CreateNomalStandLight(position);
	}
	else if (_index == 34) // 그냥 보이는 샹들리에 스위치
	{
		object = factory.CreateChandelierSwitch(position);
	}
	else if (_index == 35) //대문
	{
		object = factory.CreateMainDoor(position);
	}

	if (object != nullptr)
		m_objectContainer.push_back(object);
}
