#include "ResourceMng.h"
#include "test.h"

/*++++++
*���W���[����:		ResourceMng�N���X����
*�T�v:			ResourceMng�N���X�̏������L�q
------*/

ResourceMng* ResourceMng::_instance = 0;

ResourceMng::ResourceMng()
{
}


ResourceMng::~ResourceMng()
{
}

/*++++++
*�@�\�T�v�F		ResoureMng�̃C���X�^���X�擾
*�����F			�Ȃ�
*�֐��l�F		ResourceMng	_instance
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
*�@�\�T�v�F		�摜���̂������ɉ摜�f�[�^���擾
*�����F			string	imgName:�摜����
*�֐��l�F		QImage
*				�摜�f�[�^
------*/
QImage ResourceMng::GetImage(string imgName)
{
	QImage img;
	// _resourceTable����T��
	auto itr = _resourcrTable.find(imgName);
	if (itr != _resourcrTable.end())
	{
		// �e�[�u�����ɓ��Y�摜������ꍇ
		img = itr->second;
#ifdef DEBUG
		cout << "Load from Resource Table.\n";
#endif
	}
	else
	{
		// �e�[�u�����ɓ��Y�摜���Ȃ��ꍇ
		// �e�[�u���֐V�K�o�^
		img = LoadFileImage(imgName);
		if (!img.isNull())
		{
			// �ǂݍ��񂾉摜��null�o�Ȃ���΃e�[�u���֕ۑ�
			_resourcrTable[imgName] = img;
		}
	}

	return img;
}

/*++++++
*�@�\�T�v�F		�摜�f�[�^���t�@�C������ǂݍ���
*�����F			string	name:�摜����
*�֐��l�F		QImage
*				�摜�f�[�^
------*/
QImage ResourceMng::LoadFileImage(string name)
{
	QImage img;
	string stdPath = RESOURCE_FILE_PATH;
	stdPath += name;
	stdPath += RESOURCE_FILE_TYPE;

	QString filePath = QString::fromStdString(stdPath);
	filePath = QDir::toNativeSeparators(filePath);

	// �w�肵���t�@�C�������݂��邩�ǂ����`�F�b�N
	if (QFile::exists(filePath))
	{
		// ���݂���ꍇ�͓ǂݍ���
		img.load(filePath);
#ifdef DEBUG
		cout << "Load from DB.\n";
#endif
	}
	else
	{
		// �����ꍇ��img��null�̂܂�
#ifdef DEBUG
		cout << "The Image is not in DB.\n";
#endif
	}

	return img;
}