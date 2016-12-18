#pragma once

#include <vector>

class CVideoInfo
{
public:
	CVideoInfo() = default;
	virtual ~CVideoInfo() = default;

	long idVideo;
	CString title;
	CString fileLoc;
	int date;
	CString director;
	CString fileSize;
	CString cooperation;
	long volume;
	CString series;
	CString PosterLoc;
	CString actors;
	CString tags;
	std::vector<CString>actor;
	std::vector<CString>tag;
};