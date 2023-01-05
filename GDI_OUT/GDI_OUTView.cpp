
// GDI_OUTView.cpp: CGDIOUTView 클래스의 구현
//

#include "pch.h"
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
	const auto aspect_ratio = 1.0 / 1.0;
	const int image_width = 600;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// 화면 DC와 호환성 있는 메모리 DC를 만듦
	CDC BufferDC;
	BufferDC.CreateCompatibleDC(pDC);

	// 화면 DC와 호환성 있는 메모리 비트맵을 만듦
	CBitmap bmpBuffer;
	bmpBuffer.CreateCompatibleBitmap(pDC, image_width, image_height);

	// 메모리 DC에 메모리 비트맵을 선택
	CBitmap* pOldBitmap = (CBitmap*)BufferDC.SelectObject(&bmpBuffer);

	// 메모리 DC에 그림을 그림
	BufferDC.Rectangle(0, 0, 200, 200);
	BufferDC.Rectangle(10, 10, 100, 100);
	BufferDC.Ellipse(70, 70, 180, 180);
	BufferDC.SetPixel(100, 100, 0x010f0f);

	// 메모리 비트맵에 그려진 내용을 화면으로 전송
	pDC->BitBlt(0, 0, image_width, image_height, &BufferDC, 0, 0, SRCCOPY);

	// DC 복원
	BufferDC.SelectObject(pOldBitmap);

	//Graphics graphics(pDC->m_hDC);
	//Pen pen(Color(255, 0, 0, 0), 3);

	//graphics.DrawLine(&pen, 50, 50, 500, 50);
	//graphics.DrawRectangle(&pen, 50, 100, 200, 100);
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
