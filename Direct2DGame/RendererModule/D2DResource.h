#pragma once

/// <summary>
/// D2D 리소스의 인터페이스
/// </summary>
class D2DResource
{
public:
	void SetKey(const wstring& _key) { m_key = _key; }
	void SetFilePath(const wstring& _filePath) { m_filePath = _filePath; }

	const wstring& GetFilePath() { return m_filePath; }
	const wstring& GetKey() { return m_key; }

public:
	D2DResource();
  virtual ~D2DResource();

private:
	wstring m_key; // 리소스 키값
	wstring m_filePath; // 파일 경로
};

