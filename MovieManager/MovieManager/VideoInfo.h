#pragma once

#include <vector>

class CVideoInfo
{
public:
	CVideoInfo() = default;
	virtual ~CVideoInfo() = default;

	CString title;
	std::vector<CString>actor;
	std::vector<CString>tag;
	CString director;
	CString cooperation;
	CString date;
	CString fileSize;
};