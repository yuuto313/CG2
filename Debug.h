#pragma once
#include <string>

namespace Debug{
	void Log(const std::string& message);
	/// <summary>
	/// std::wstringからstd::stringにそれぞれ変更する関数
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	std::wstring ConvertString(const std::string& str);

	std::string ConvertString(const std::wstring& str);

}

