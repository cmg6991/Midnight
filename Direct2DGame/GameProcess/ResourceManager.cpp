#include "GameProcessPCH.h"
#include "ResourceManager.h"
#include "PathManager.h"
#include "FileManager.h"
#include "SoundManager.h"


ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::Initalize(PathManager* _pathManager, D2DRenderer* _d2DRenderer)
{
	PathManager* pathManager = _pathManager;

	wstring parentFilePath = pathManager->GetRelativPath();

	const wstring imageFilePath = parentFilePath + L"\\Resource\\Texture";
	const wstring soundFilePathBGM = parentFilePath + L"\\Resource\\Sound";
	const wstring soundFilePathSFX = parentFilePath + L"\\Resource\\Sound\\SFX";

	// 이미지를 로드 
	LoadImageResources(_d2DRenderer, imageFilePath);

	// 사운드를 로드
	LoadSoundResources(soundFilePathBGM, soundFilePathSFX);
}


void ResourceManager::Finalize()
{
	// 리소스 매니져가 직접적으로 리소를 들고있지않는다.
}

void ResourceManager::LoadImageResources(D2DRenderer* _d2DRenderer, const wstring& _filePath)
{
	/// 리소스 파일로 경로를 연결한다
	vector<wstring> filesPath{}, fileName{};

	/// 파일내부의 이름과 경로값으로 백터를 채운다
	FileManager::GetFileMemberPath(filesPath, _filePath, true);
	FileManager::GetFileMemberName(fileName, _filePath, true);

	assert(filesPath.size() == fileName.size());

	/// 확장자명 제거하고 Key값으로 만들기  ex) apple.png -> apple
	for (int i = 0; i < static_cast<int>(fileName.size()); ++i)
	{
		while (true)
		{
			wchar_t tmp = fileName[i].back();
			fileName[i].pop_back();

			if (tmp == L'.') break;

			/// 확장자명을 확인해야할 필요가 있을듯
			assert(fileName.size() != 0 || !L"파일의 확장자 키워드가 없습니다.");
		}
	}

	for (int i = 0; i < static_cast<int>(fileName.size()); ++i)
	{
		/// 파일 이름을 key값으로 사용한다
		_d2DRenderer->LoadBitmap(fileName[i], filesPath[i].c_str());
	}
}


void ResourceManager::LoadSoundResources(const wstring& _filePath, const wstring& _filePathSFX)
{
	/// 사운드매지져를 사용해서 사운들를 로드하는 지점

	/// 리소스 파일로 경로를 연결한다
	vector<wstring> filesPath{}, fileName{};//bgm
	vector<wstring> filesPathSFX{}, fileNameSFX{};//sfx

	/// 파일내부의 이름과 경로값으로 백터를 채운다
	FileManager::GetFileMemberPath(filesPath, _filePath, true);	//bgm
	FileManager::GetFileMemberName(fileName, _filePath, true);	//bgm
	
	FileManager::GetFileMemberPath(filesPathSFX, _filePathSFX, true);	//sfx
	FileManager::GetFileMemberName(fileNameSFX, _filePathSFX, true);	//sfx

	assert(filesPath.size() == fileName.size());
	assert(filesPathSFX.size() == fileNameSFX.size());

	/// 확장자명 제거하고 Key값으로 만들기  ex) apple.png -> apple
	/// BGM-----------------------------------------------------
	for (int i = 0; i < static_cast<int>(fileName.size()); ++i)
	{
		while (true)
		{
			wchar_t tmp = fileName[i].back();
			fileName[i].pop_back();

			if (tmp == L'.') break;

			/// 확장자명을 확인해야할 필요가 있을듯
			assert(fileName.size() != 0 || !L"파일의 확장자 키워드가 없습니다.");
		}
	}

	for (int i = 0; i < static_cast<int>(fileName.size()); ++i)
	{
		/// 파일 이름을 key값으로 사용한다
		SoundManager::GetInstance()->LoadSound(fileName[i], filesPath[i], SoundType::BGM);

	}
	/// --------------------------------------------------------

	/// SFX-----------------------------------------------------
	for (int i = 0; i < static_cast<int>(fileNameSFX.size()); ++i)
	{
		while (true)
		{
			wchar_t tmp = fileNameSFX[i].back();
			fileNameSFX[i].pop_back();

			if (tmp == L'.') break;

			/// 확장자명을 확인해야할 필요가 있을듯
			assert(fileNameSFX.size() != 0 || !L"파일의 확장자 키워드가 없습니다.");
		}
	}

	for (int i = 0; i < static_cast<int>(fileNameSFX.size()); ++i)
	{
		/// 파일 이름을 key값으로 사용한다
		SoundManager::GetInstance()->LoadSound(fileNameSFX[i], filesPathSFX[i], SoundType::SFX);
	}
	/// --------------------------------------------------------
}
