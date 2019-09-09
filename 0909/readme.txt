라디오 버튼 클릭으로 블럭 결정.

게임시작시 기지는 고정

1. 컨트롤 z Undo redo 되돌리기 되돌리기도디로기릳릳리 스택.

save , load

파일 다이얼로그 띄우기.

OPENFILENAME 구조체 세팅

char str[256];
char lpstrFile[] = "";

ZeroMemory(&OFN,sizeof(OPENFILENAME));
OFN.IStructSize = sizeof((OPENFILENAME));
OFN.hwndOwner = hWnd;
OFN.lpstrFilter = "Every File(".")\0*.*\0Text File\0*.*\0*.txt;*.ini\0";
OFN.lpstrFile = lpstrFile; 파일이 이름이 온다.

OFN.nMaxFile = 256;
OFN.lpstrInitialDir = "c:\\";

if(GetOpenFileName(&OFN) != 0)
{
	sprintf(str, "%s 파일을 선택했습니다.", OFN.lpstrFile);
	MessageBox(hWnd,str,"파일 열기 성공", MB_OK);
}