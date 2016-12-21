#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int		uint32;

typedef struct head
{
	uint32 nLength;
	uint32 nIndex;
}HEAD, *PHEAD;

typedef struct head2
{
	uint32 nLength;
	uint32 nIndex;
	uint32 nCommno;
}HEAD2, *PHEAD2;

struct tagESBHead
{
	uint32 m_iPackType:6;
	uint32 m_iTimeStampFlag:4;
	uint32 m_iMsgOffset:22;

	uint32 m_iPackLen;
	uint32 m_iFuncID;
	uint32 m_iPackID;
	uint32 m_iReturnCode;
	uint32 m_iSenderID;
	uint32 m_iPriority;
	uint32 m_iRmGroupNO;
	uint32 m_iRmNO;
	uint32 m_iQueueNO;
	uint32 m_iQueueTime;
};

//��־�����ҵ��ͷ
typedef struct tgTradeBizHead 
{
	uint32         dwBufLen;            //����
	uint32         dwIndex;
	uint32         dwCommNo;            //ͨ�Ž׶κ�
}TradeBizHead;

#define BIZ_HEAD_LEN   sizeof(TradeBizHead)

int ChangeFile(const char* pSrc, const char* pDest);


int main(int argc, char* argv[])
{
	int i = 0;
	int ret = 0;

	if (argc < 3)
	{
		printf("��������������������һ������ת���ļ������ڶ�����������ļ���, %d\n", argc - 1);
		return -1;
	}

	for (i = 0; i< argc; i++)
	{
		printf("�������: %s\n", argv[i]);
	}

	ret = ChangeFile(argv[1], argv[2]);
	if (0 == ret)
	{
		printf("ת���ɹ�\n", ret); 
	}
	else
	{
		printf("ת��ʧ��, ret = %d\n", ret);
	}
	
  
	getchar();
	return 0;
}

int ChangeFile(const char* pSrc, const char* pDest)
{
	//д�ļ�ģ��
	FILE* fp = fopen(pDest, "wb");
	//----���ļ�ģ��----
	FILE* m_lpReadFile = fopen(pSrc, "rb");
	int n = 0;
	PHEAD pHd = NULL;
	HEAD hd;
	int ch;
	int nCount;
	int num = 0;

	if (NULL == m_lpReadFile || NULL == fp)
	{
		return -1;
	}

	//��ȡ�ļ���С
	fseek(m_lpReadFile, 0L, SEEK_END);
	int len =ftell(m_lpReadFile)+1;
	fseek(m_lpReadFile, 0L, SEEK_SET);


	while (1)
	{
		nCount = ftell(m_lpReadFile);
		if (nCount > len - 2)
		{
			break;
		}

		//��ͷ
		fread(&hd, 1, sizeof(hd), m_lpReadFile);
		char* pData = new char[hd.nLength + 20];
		char* pData1 = new char[hd.nLength + 20];
		memset(pData, 0, hd.nLength + 20);
		memset(pData1, 0, hd.nLength + 20);

		//������ͷ
		HEAD2 hd2;
		hd2.nLength = hd.nLength + 20;
		hd2.nIndex = hd.nIndex;
		hd2.nCommno = 0;
		fwrite(&hd2, sizeof(HEAD2), 1, fp);


		//���ļ�����
		fread((void*)pData, 1, hd.nLength, m_lpReadFile);
		tagESBHead* pHead = (tagESBHead* )pData;
		//printf("num = %, m_iFuncID = %d, m_iPackLen = %d\n",  ++num, pHead->m_iFuncID, pHead->m_iPackLen);
		//����������
		int nHeadLen = sizeof(tagESBHead);
		int nLength = hd.nLength;
		memcpy(pData1, pData, nHeadLen);
		tagESBHead* pHead1 = (tagESBHead* )pData1;
		pHead1->m_iMsgOffset += 20; 
		pHead1->m_iPackLen += 20;
		memcpy(pData1+nHeadLen+20, pData+nHeadLen, nLength-nHeadLen);
		fwrite(pData1, nLength+20, 1, fp);

		//����"\r\n"
		ch = fgetc(m_lpReadFile);
		ch = fgetc(m_lpReadFile);
		//д������
		char ch2[3]="\r\n";
		fwrite(ch2, 2, 1, fp);

		if (pData)
		{
			delete[] pData;
		}

		if (pData1)
		{
			delete[] pData1;
		}
	}

	fclose(m_lpReadFile);
	fclose(fp);
	return 0;

}