#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define ATTRIBUTE 3
#define MAXSIZE 256
/*
struct data
{
	int Index		//인덱스
	char[256] Name	//이름
	int Atk			//공격력
};
*/

int GetAttributeWitdh(string Colum[])
{
	//witdh.
	int witdh = 0;
	string temp = Colum[0];
	while (true)
	{
		if (temp.find(',') != -1)
		{
			temp.erase(0, temp.find(',') + 1);
			++witdh;
		}
		else
		{
			++witdh;
			break;
		}
	}
	return witdh;
}
// ATTRIBUTE 다음에 컬럼을 가져올 때에는 ATTRIBUTE 다음 값을 받으면 얻을 수 있음.
void subStrColum(string attribute[], string Colum[], int width)
{
	string temp = Colum[0];
	int height = 0;
	int count = 0;
	while (true)
	{
		if (count == ATTRIBUTE * width)
			break;
		if (temp.find(',') != -1)
		{
			attribute[count] = temp.substr(0, temp.find(','));
			temp.erase(0, temp.find(',') + 1);
		}
		else
		{
			++height;
			attribute[count] = temp;
			temp = Colum[height];
		}
		++count;
	}
}

void swapAttributeDatatype(string attribute[], int width)
{
	// swap.
	int count = 0;
	while (true)
	{
		if (count == ATTRIBUTE)
			break;

		swap(attribute[count], attribute[width + count]);

		++count;
	}
}

bool outDrawFile(string attribute[], int width)
{
	//draw
	ofstream outfile("struct.h", ios::out);
	if (!outfile.bad())
	{
		outfile << "struct data" << endl;
		outfile << "{" << endl;
		for (int i = 0; i < width; ++i)
		{
			outfile << '\t' << attribute[i] << ' ' << attribute[i + width] << "\t" << "//" <<
				attribute[i + (width * 2)] << endl;
		}
		outfile << "}" << endl;

	}
	else
	{
		outfile.close();
		return false;
	}

	outfile.close();
	return true;
}
bool inOpenFile(string Colum[])
{
	ifstream inFile("data.csv");
	char szBuffer[MAXSIZE];
	int count = 0;
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			if (count == ATTRIBUTE)
			{
				break;
			}
			inFile.getline(szBuffer, sizeof(szBuffer), '\n');

			Colum[count] = szBuffer;
			++count;
		}
	}
	else
	{
		return false;
	}
	inFile.close();
	return true;
}

int main()
{
	string attribute[MAXSIZE];
	string Colum[MAXSIZE];

	int Colum_width = 0;

	if (!inOpenFile(Colum))
	{
		cout << "파일 읽기 에러" << endl;
		return 0;
	}

	Colum_width = GetAttributeWitdh(Colum);
	subStrColum(attribute, Colum, Colum_width);
	swapAttributeDatatype(attribute, Colum_width);

	if (!outDrawFile(attribute, Colum_width))
	{
		cout << "파일 저장 에러" << endl;
	}

	return 0;
}