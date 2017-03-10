#pragma once
#include <vector>

// CPictureEx

class CPictureEx : public CStatic
{
public:

	struct TFrame  // �����źſ����Ϣ
	{
		IPicture *m_pPicture; // ָ��滭�ӿ� 
		SIZE m_frameSize;
		SIZE m_frameOffset;
		UINT m_nDelay; // ��ʱ1/100s
		UINT m_nDisposal; // ������
	};

#pragma pack(1) // ���ݶ��뷽ʽ

	enum GIFBlockTypes
	{
		BLOCK_UNKNOWN,
		BLOCK_APPEXT,
		BLOCK_COMMEXT,
		BLOCK_CONTROLEXT,
		BLOCK_PLAINTEXT,
		BLOCK_IMAGE,
		BLOCK_TRAILER
	};

	enum ControlExtValues
	{
		GCX_PACKED_DISPOSAL,
		GCX_PACKED_USERINPUT,
		GCX_PACKED_TRANSPCOLOR
	};

	enum LSDPackedValues //�߼�Ҳ��������ļ�ֵ
	{
		LSD_PACKED_GLOBALCT,
		LSD_PACKED_CRESOLUTION,
		LSD_PACKED_SORT,
		LSD_PACKED_GLOBALCTSIZE
	};

	enum IDPackedValues // ͼ�������������ֵ
	{
		ID_PACKED_LOCALCT,
		ID_PACKED_INTERLACE,
		ID_PACKED_SORT,
		ID_PACKED_LOCALCTSIZE
	};

	struct TGIFHeader
	{
		char m_cSignature[3]; // Ψһ��GIF������
		char m_cVersion[3]; // �汾��Ϣ
	};

	struct TGIFLSDescriptor // �߼�������
	{
		WORD m_wWidth; // �߼�����
		WORD m_wHeight; // �߼�����
		unsigned char m_cPacked; // ����ļ�
		unsigned char m_cBkIndex; // �������ɫ
		unsigned char m_cPixelAspect; // 
		inline int GetPackedValue(enum LSDPackedValues value);
	};

	struct TGIFAppExtension // Ӧ����չ��
	{
		unsigned char m_cExtIntroducer; // ��չ����
		unsigned char m_cExtLabel; // Ӧ����չlabel
		unsigned char m_cBlockSize; // ���ֵ
		char m_cAppIdentifier[8]; // Ӧ�ñ�ʶ
		char m_cAppAuth[3]; // Ӧ����֤��
	};

	struct TGIFControlExt // ͼ�������չ��
	{
		unsigned char m_cExtIntroducer; // ��չ����
		unsigned char m_cControLabel; // ������չlabel
		unsigned char m_cBlockSize; // ����ֵ
		unsigned char m_cPacked; // ����ļ�
		WORD m_wDelayTime; // ��ʱʱ��
		unsigned char m_cTColorIndex; // ������ɫ����
		unsigned char m_cBlockTerm; // 
		inline int GetPackedValue(enum ControlExtValues value);
	};

	struct TGIFCommentExt // ͨ����չ��
	{
		unsigned char m_cExtIntroducer; // ��չ����
		unsigned char m_cCommentLabel; // ͨ����չlabel
	};

	struct TGIFPlainTextExt // 
	{
		unsigned char m_cExtIntroducer;
		unsigned char m_cPlainTextLabel;
		unsigned char m_cBlockSize;
		WORD m_wLeftPos;
		WORD m_wTopPos;
		WORD m_wGridWidth;
		WORD m_wGridHeight;
		unsigned char m_cCellWidth;
		unsigned char m_cCellHeight;
		unsigned char m_cFgColor;
		unsigned char m_cBkColor;
	};

	struct TGIFImageDescriptor 
	{
		unsigned char m_cImageSeparator;
		WORD m_wLeftPos;
		WORD m_wTopPos;
		WORD m_wWidth;
		WORD m_wHeight;
		unsigned char m_cPacked;
		inline int GetPackedValue(enum IDPackedValues value);
	};

#pragma pack()

public:
	BOOL GetPaintRect(RECT *lpRect);
	BOOL SetPaintRect(const RECT *lpRect);
	CPictureEx();
	virtual ~CPictureEx();
	void Stop(); // ֹͣ����
	void UnLoad();  // ֹͣ�������ͷ���Դ

	BOOL IsGIF() const;
	BOOL IsPlaying() const;
	BOOL IsAnimatedGIF() const;
	SIZE GetSize() const;
	int GetFrameCount() const;
	COLORREF GetBkColor() const;
	void SetBkColor(COLORREF clr);

	BOOL Draw();
	BOOL Load(LPCTSTR szFileName);
	BOOL Load(HGLOBAL hGlobal,DWORD dwSize);
	BOOL Load(LPCTSTR szResourceName,LPCTSTR szResourceType);

protected:
#ifdef GIF_TRACING
	void EnumGIFBlocks();
	void WriteFataOnDisk(CString szFileName,HGLOBAL hData,DWORD dwSize);
#endif

	RECT m_PaintRect;
	SIZE m_PictureSize;
	COLORREF m_clrBackground;
	UINT m_nCurrFrame;
	UINT m_nDataSize;
	UINT m_nCurrOffset;
	UINT m_nGlobalCTSize;
	BOOL m_bIsGIF;
	BOOL m_bIsPlaying;
	volatile BOOL m_bExitThread;
	BOOL m_bIsInitialized;
	HDC m_hMemDC;

	HDC m_hDispMemDC;
	HBITMAP m_hDispMemBM;
	HBITMAP m_hDispOldBM;

	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	HANDLE m_hThread;
	HANDLE m_hExitEvent;
	IPicture * m_pPicture;
	TGIFHeader * m_pGIFHeader;
	unsigned char * m_pRawData;
	TGIFLSDescriptor *m_pGIFLSDescriptor;
	std::vector<TFrame> m_arrFrames;

	void ThreadAnimation();
	static UINT WINAPI _ThreadAnimation(LPVOID pParam);

	int GetNextBlockLen() const;
	BOOL SkipNextBlock();
	BOOL SkipNextGraphicBlock();
	BOOL PrepareDC(int nWidth,int nHeight);
	void ResetDataPointer();
	enum GIFBlockTypes GetNextBlock() const;
	UINT GetSubBlocksLen(UINT nStartingOffset) const;
	HGLOBAL GetNextGraphicBlock(UINT * pBlockLen,UINT *pDelay,
		SIZE *pBlockSize,SIZE *pBlockOffset,UINT *pDisposal);

	afx_msg void OnDestroy();
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};


