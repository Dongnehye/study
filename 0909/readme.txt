���� ��ư Ŭ������ �� ����.

���ӽ��۽� ������ ����

1. ��Ʈ�� z Undo redo �ǵ����� �ǵ����⵵��α␒���� ����.

save , load

���� ���̾�α� ����.

OPENFILENAME ����ü ����

char str[256];
char lpstrFile[] = "";

ZeroMemory(&OFN,sizeof(OPENFILENAME));
OFN.IStructSize = sizeof((OPENFILENAME));
OFN.hwndOwner = hWnd;
OFN.lpstrFilter = "Every File(".")\0*.*\0Text File\0*.*\0*.txt;*.ini\0";
OFN.lpstrFile = lpstrFile; ������ �̸��� �´�.

OFN.nMaxFile = 256;
OFN.lpstrInitialDir = "c:\\";

if(GetOpenFileName(&OFN) != 0)
{
	sprintf(str, "%s ������ �����߽��ϴ�.", OFN.lpstrFile);
	MessageBox(hWnd,str,"���� ���� ����", MB_OK);
}