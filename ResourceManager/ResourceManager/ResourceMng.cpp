#include "ResourceMng.h"
#include "test.h"

/*++++++
*モジュール名:		ResourceMngクラス実体
*概要:			ResourceMngクラスの処理を記述
------*/

ResourceMng* ResourceMng::_instance = 0;

ResourceMng::ResourceMng()
{
}


ResourceMng::~ResourceMng()
{
}

/*++++++
*機能概要：		ResoureMngのインスタンス取得
*引数：			なし
*関数値：		ResourceMng	_instance
------*/
ResourceMng* ResourceMng::GetInstance()
{
	if (!_instance)
	{
		_instance = new ResourceMng();
	}
	return _instance;
}

/*++++++
*機能概要：		画像名称を引数に画像データを取得
*引数：			string	imgName:画像名称
*関数値：		QImage
*				画像データ
------*/
QImage ResourceMng::GetImage(string imgName)
{
	QImage img;
	// _resourceTable内を探索
	auto itr = _resourcrTable.find(imgName);
	if (itr != _resourcrTable.end())
	{
		// テーブル内に当該画像がある場合
		img = itr->second;
#ifdef DEBUG
		cout << "Load from Resource Table.\n";
#endif
	}
	else
	{
		// テーブル内に当該画像がない場合
		// テーブルへ新規登録
		img = LoadFileImage(imgName);
		if (!img.isNull())
		{
			// 読み込んだ画像がnull出なければテーブルへ保存
			_resourcrTable[imgName] = img;
		}
	}

	return img;
}

/*++++++
*機能概要：		画像データをファイルから読み込む
*引数：			string	name:画像名称
*関数値：		QImage
*				画像データ
------*/
QImage ResourceMng::LoadFileImage(string name)
{
	QImage img;
	string stdPath = RESOURCE_FILE_PATH;
	stdPath += name;
	stdPath += RESOURCE_FILE_TYPE;

	QString filePath = QString::fromStdString(stdPath);
	filePath = QDir::toNativeSeparators(filePath);

	// 指定したファイルが存在するかどうかチェック
	if (QFile::exists(filePath))
	{
		// 存在する場合は読み込み
		img.load(filePath);
#ifdef DEBUG
		cout << "Load from DB.\n";
#endif
	}
	else
	{
		// 無い場合はimgはnullのまま
#ifdef DEBUG
		cout << "The Image is not in DB.\n";
#endif
	}

	return img;
}