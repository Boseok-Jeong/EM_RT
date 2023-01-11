
// GDI_OUTView.cpp: CGDIOUTView 클래스의 구현
//

//#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GDI_OUT.h"
#endif

#include "GDI_OUTDoc.h"
#include "GDI_OUTView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDIOUTView

IMPLEMENT_DYNCREATE(CGDIOUTView, CView)

BEGIN_MESSAGE_MAP(CGDIOUTView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CGDIOUTView 생성/소멸

CGDIOUTView::CGDIOUTView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGDIOUTView::~CGDIOUTView()
{
}

BOOL CGDIOUTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGDIOUTView 그리기

void CGDIOUTView::OnDraw(CDC* pDC)
{
	CGDIOUTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	
	Graphics graphics(pDC->m_hDC);
	Image image(rt_name.c_str());
	int width = image.GetWidth();
	int height = image.GetHeight();

	graphics.DrawImage(&image, 10, 10, width, height);
}


// CGDIOUTView 인쇄

BOOL CGDIOUTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGDIOUTView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGDIOUTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGDIOUTView 진단

#ifdef _DEBUG
void CGDIOUTView::AssertValid() const
{
	CView::AssertValid();
}

void CGDIOUTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDIOUTDoc* CGDIOUTView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIOUTDoc)));
	return (CGDIOUTDoc*)m_pDocument;
}
#endif //_DEBUG


// CGDIOUTView 메시지 처리기
