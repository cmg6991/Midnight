#pragma once


/// <summary>
/// 인스턴스를 생성하지 않고 네임스페이스로 접근하는 매니져이다
///
/// 역할 : 파일에 데이터를 읽는 기능을 제공한다. 
/// </summary>
namespace FileManager
{
	/// <summary>
	/// 파일경로 내부에 모든 파일의 경로를 벡터에 반환 
	/// </summary>
	/// <param name="_files">파일이름을 저장할 벡터</param>
	/// <param name="_filePath">파일경로</param>
	/// <param name="_allDirectories">하위 디텍토리에 있는 파일까지 읽는지</param>
	void GetFileMemberPath(vector<wstring>& _files, const wstring& _filePath, bool _allDirectories);
	
	/// <summary>
	///  파일 경로 내부에 모든 파일의 이름을 벡터에 반환
	/// </summary>
	/// <param name="_files"></param>
	/// <param name="_filePath"></param>
	/// <param name="_allDirectories"></param>
	void GetFileMemberName(vector<wstring>& _files, const wstring& _filePath, bool _allDirectories);
};

