#pragma once
#include <qimage.h>
#include <qdir.h>
#include <string>
#include <stdint.h>
#include <unordered_map>
using namespace std;

#ifndef RESOURCE_FILE_PATH
// 画像ファイルパス
#define RESOURCE_FILE_PATH "../Resources/";
#endif
#ifndef RESOURCE_FILE_TYPE
// 画像ファイル拡張子
#define RESOURCE_FILE_TYPE ".png";
#endif

/*++++++
*モジュール名:		ResourceMngクラス
*概要:				GUIに提供する画像データを管理する。
------*/
class ResourceMng
{
public:
	static ResourceMng* GetInstance();
	QImage GetImage(string imageName);

private:
	static ResourceMng* _instance;
	unordered_map<string, QImage> _resourcrTable;
	ResourceMng();
	~ResourceMng();
	QImage LoadFileImage(string name);
};

