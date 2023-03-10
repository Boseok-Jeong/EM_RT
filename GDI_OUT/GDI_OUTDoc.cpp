
// GDI_OUTDoc.cpp: CGDIOUTDoc 클래스의 구현
//

//#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GDI_OUT.h"
#endif

#include "GDI_OUTDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#include "RT/rt_core.h"
#include "io_wrap.h"

using namespace std;

wstring rt_name = L"out_file.jpg";

// CGDIOUTDoc

IMPLEMENT_DYNCREATE(CGDIOUTDoc, CDocument)

BEGIN_MESSAGE_MAP(CGDIOUTDoc, CDocument)
	ON_COMMAND(20, &CGDIOUTDoc::OnExeRT)
//	ON_COMMAND(ID_EXE_RT, &CGDIOUTDoc::OnExeRt)
ON_COMMAND(ID_EXE_RT, &CGDIOUTDoc::OnExeRT)
END_MESSAGE_MAP()


// CGDIOUTDoc 생성/소멸

CGDIOUTDoc::CGDIOUTDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.



}

CGDIOUTDoc::~CGDIOUTDoc()
{
}

BOOL CGDIOUTDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.


	return TRUE;
}




// CGDIOUTDoc serialization

void CGDIOUTDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CGDIOUTDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CGDIOUTDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGDIOUTDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGDIOUTDoc 진단

#ifdef _DEBUG
void CGDIOUTDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGDIOUTDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGDIOUTDoc 명령


void CGDIOUTDoc::OnExeRT()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	RT_PARAM* pRtParam = new RT_PARAM;
	//pRtParam->fname = _wcsdup(rt_name.c_str());
	pRtParam->fname = (wchar_t*)rt_name.c_str();
	pRtParam->hWnd = AfxGetMainWnd()->m_hWnd;

	CWinThread* pThread = ::AfxBeginThread(MFC_RT_CORE, pRtParam);
	//rt_core(rt_name);

	//UpdateAllViews(NULL);
}
