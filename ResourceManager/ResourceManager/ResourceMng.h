#pragma once
#include <qimage.h>
#include <qdir.h>
#include <string>
#include <stdint.h>
#include <unordered_map>
using namespace std;

#ifndef RESOURCE_FILE_PATH
// �摜�t�@�C���p�X
#define RESOURCE_FILE_PATH "../Resources/";
#endif
#ifndef RESOURCE_FILE_TYPE
// �摜�t�@�C���g���q
#define RESOURCE_FILE_TYPE ".png";
#endif

/*++++++
*���W���[����:		ResourceMng�N���X
*�T�v:				GUI�ɒ񋟂���摜�f�[�^���Ǘ�����B
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

