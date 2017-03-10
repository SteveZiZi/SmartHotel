#pragma once
#include <vector>

// CPictureEx

class CPictureEx : public CStatic
{
public:

	struct TFrame  // 保存信号框架信息
	{
		IPicture *m_pPicture; // 指向绘画接口 
		SIZE m_frameSize;
		SIZE m_frameOffset;
		UINT m_nDelay; // 延时1/100s
		UINT m_nDisposal; // 处理方法
	};

#pragma pack(1) // 数据对齐方式

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

	enum LSDPackedValues //逻辑也描述打包文件值
	{
		LSD_PACKED_GLOBALCT,
		LSD_PACKED_CRESOLUTION,
		LSD_PACKED_SORT,
		LSD_PACKED_GLOBALCTSIZE
	};

	enum IDPackedValues // 图像描述打包属性值
	{
		ID_PACKED_LOCALCT,
		ID_PACKED_INTERLACE,
		ID_PACKED_SORT,
		ID_PACKED_LOCALCTSIZE
	};

	struct TGIFHeader
	{
		char m_cSignature[3]; // 唯一的GIF数据流
		char m_cVersion[3]; // 版本信息
	};

	struct TGIFLSDescriptor // 逻辑屏描述
	{
		WORD m_wWidth; // 逻辑屏宽
		WORD m_wHeight; // 逻辑屏高
		unsigned char m_cPacked; // 打包文件
		unsigned char m_cBkIndex; // 背景填充色
		unsigned char m_cPixelAspect; // 
		inline int GetPackedValue(enum LSDPackedValues value);
	};

	struct TGIFAppExtension // 应用扩展包
	{
		unsigned char m_cExtIntroducer; // 扩展介绍
		unsigned char m_cExtLabel; // 应用扩展label
		unsigned char m_cBlockSize; // 填充值
		char m_cAppIdentifier[8]; // 应用标识
		char m_cAppAuth[3]; // 应用验证码
	};

	struct TGIFControlExt // 图像控制扩展块
	{
		unsigned char m_cExtIntroducer; // 扩展描述
		unsigned char m_cControLabel; // 控制扩展label
		unsigned char m_cBlockSize; // 填充的值
		unsigned char m_cPacked; // 打包文件
		WORD m_wDelayTime; // 延时时间
		unsigned char m_cTColorIndex; // 传输颜色索引
		unsigned char m_cBlockTerm; // 
		inline int GetPackedValue(enum ControlExtValues value);
	};

	struct TGIFCommentExt // 通用扩展块
	{
		unsigned char m_cExtIntroducer; // 扩展介绍
		unsigned char m_cCommentLabel; // 通用扩展label
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
	void Stop(); // 停止动画
	void UnLoad();  // 停止动画，释放资源

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


