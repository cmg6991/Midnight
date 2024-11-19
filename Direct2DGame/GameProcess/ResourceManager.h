#pragma once

class PathManager;

/// <summary>
/// 이미지, 사운드를 로드하는 매니져 
/// 하지만 리소스 매니져가 직접적으로 리소스들을 관리하지 않는다.
/// 
/// </summary>
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void Initalize(PathManager* _pathManager, D2DRenderer* _d2DRenderer);	
	void Finalize();
private:
	// 이미지를 로드한다.
	void LoadImageResources(D2DRenderer* _d2DRenderer, const wstring& _filePath);

	// 사운드를 로드한다. 
	void LoadSoundResources(const wstring& _filePath, const wstring& _filePathSFX);

private:
	
};

