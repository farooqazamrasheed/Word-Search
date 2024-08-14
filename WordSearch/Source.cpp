//project no 3
#include<iostream>
#include<fstream>
using namespace std;
void main_menu();
void Sub_main();
void sub_main2();
void resum(char** array, int row, int* col);
bool find(char* arr, int size);
bool diag_wise(char* arr, int size, char** array, int row, int* col);
bool col_wise(char* arr, int size, char** array, int row, int* col);
bool col_rev_wise(char* arr, int size, char** array, int row, int* col);
bool row_wise(char* arr, int size, char** array, int row, int* col);
bool row_rev_wise(char* arr, int size, char** array, int row, int* col);
void User_record_input(char*& arr, int& size);
void Display_high_record();
bool verify(char* arr, int size1);
void save_high_record();
void get_word(char*& arr, int& size);
void display_board(char** arr, int row, int* col);
int* regrowd(int* ptr, int input, int& size);
char** two_D_regrow(char** ptr, int size);
void delete_2d(char** arr, int& size);
char* regrow(char* ptr, char input, int& size);
void read_board(ifstream& fin, char**& array, int& row, int*& len_col);
int life = 0;
int score = 0;
int level = 1;//global variable for level selection
int main()
{
	main_menu();
	return 0;
}
void main_menu()
{
	char choice;
	while (true)
	{
		cout << "				Press n for new game" << endl;
		cout << "				Press r for resume game " << endl;
		cout << "				Press l for Level selection " << endl;
		cout << "				Press h for high score " << endl;
		cout << "				Press e for exit" << endl;
		cout << "				 = ";
		cin >> choice;
		if (choice == 'n' || choice == 'N')
		{
			life = 3;
			char* arr;
			int size = 0;
			User_record_input(arr, size);
			ifstream fin("Board.txt");
			if (!fin.is_open())
			{
				cout << "File of board.txt is not Found !!" << endl;
			}
			else
			{
				char** array;
				int row = 0;
				int* col;
				read_board(fin, array, row, col);
				display_board(array, row, col);
				while (life > 0)
				{
					resum(array, row, col);
				}
				save_high_record();
			}
		}
		else if (choice == 'r' || choice == 'R')
		{
			ifstream fin("Pausedgame.txt");
			if (!fin.is_open())
			{
				cout << "you cannot play resume game" << endl;
			}
			else
			{
				if (life > 0)
				{
					char** array;
					int row = 0;
					int* col;
					read_board(fin, array, row, col);
					display_board(array, row, col);
					while (life > 0)
					{
						resum(array, row, col);
					}
					save_high_record();
				}
				else
				{
					cout << "Please restart the game because life is zero" << endl;
				}
			}
		}
		else if (choice == 'l' || choice == 'L')
		{
			sub_main2();
		}
		else if (choice == 'h' || choice == 'H')
		{
			Display_high_record();
		}
		else if (choice == 'E' || choice == 'e')
		{
			cout << "Thanks for playing !!!" << endl;
			exit(0);
		}
		else
		{
			cout << "Press valid Key !!" << endl;
		}
	}
}
void Sub_main()
{
	char choice;
	while (true)
	{
		cout << "			Press e for exit" << endl;
		cout << "			Press r for resume" << endl;
		cout << " 		= ";
		cin >> choice;
		if (choice == 'E' || choice == 'e')
		{
			cout << "Thanks for playing !!!" << endl;
			exit(0);
		}
		else if (choice == 'r' || choice == 'R')
		{

		}
		else
		{
			cout << "Press valid Key !!" << endl;
		}

	}
}
void sub_main2()
{
	cout << "***********Level Selection*********" << endl << endl;
	while (true)
	{
		cout << "Press 1 for easy " << endl;
		cout << "Press 2 for medium " << endl;
		cout << "Press 3 for difficult " << endl << " = ";
		cin >> level;
		if (level != 1 && level != 2 && level != 3)
		{
			cout << "Press valid key " << endl;
		}
		else
		{
			break;
		}
	}
}
void read_board(ifstream& fin, char**& array, int& row, int*& len_col)
{
	int size1 = 0;
	array = new char*[1];
	array[0] = new char[1];
	char input;
	row = 0;
	len_col = new int[1];
	len_col[row] = 0;
	while (fin.get(input))
	{
		if (int(input) != 10)
		{
			array[row] = regrow(array[row], input, len_col[row]);
		}
		else
		{
			int col = row + 1;
			array = two_D_regrow(array, col);
			len_col = regrowd(len_col, 0, col);
			row++;
		}
	}
}
void display_board(char** arr, int row, int* col)
{
	for (int i = 0; i <= row; i++)
	{
		for (int j = 0; j < col[i]; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << "------------------------------------------------------" << endl;
}
void delete_2d(char** arr, int& size)
{
	for (int i = 0; i < size; i++)
	{
		delete[]arr[i];
		arr[i] = NULL;
	}
	delete[]arr;
	size = 0;
}
int* regrowd(int* ptr, int input, int& size)
{
	int* temp = new int[size + 1];
	for (int i = 0; i < size; i++)
	{
		temp[i] = ptr[i];
	}
	temp[size] = input;
	size++;
	delete[]ptr;
	ptr = NULL;
	return temp;
}
char* regrow(char* ptr, char input, int& size)
{
	char* temp = new char[size + 1];
	for (int i = 0; i < size; i++)
	{
		temp[i] = ptr[i];
	}
	temp[size] = input;
	size++;
	delete[]ptr;
	ptr = NULL;
	return temp;
}
char** two_D_regrow(char** ptr, int size)
{
	char** temp = new char*[size + 1];
	for (int i = 0; i < size; i++)
	{
		temp[i] = ptr[i];
		ptr[i] = NULL;
	}
	temp[size] = new char[1];
	return temp;
}
void User_record_input(char*& arr, int& size)
{
	arr = new char[1];
	size = 0;
	char ch;
	cin.ignore();
	cout << "Enter a User_Name : ";
	while (cin.get(ch))
	{
		if (ch == '\n')
		{
			break;
		}
		else
		{
			arr = regrow(arr, ch, size);
		}
	}
}
void get_word(char*& arr, int& size)
{
	arr = new char[1];
	size = 0;
	char ch;
	cin.ignore();
	cout << "Enter a Word : ";
	while (cin.get(ch))
	{
		if (ch == '\n')
		{
			break;
		}
		else
		{
			arr = regrow(arr, ch, size);
		}
	}
}
void save_high_record()
{
	int* num = new int[5];
	ifstream fin("Highrecord.txt");
	if (!fin.is_open())
	{
		ofstream fout("Highrecord.txt");
		fout << score << endl;
		fout.close();
	}
	else
	{
		for (int i = 0; fin >> num[i]; i++)
		{
			if (score > num[i])
			{
				int temp = num[i];
				num[i] = score;
				score = temp;
			}
		}
		for (int j = 0; j < 5 - 1; j++)
		{
			for (int i = j; i < 5; i++)
			{
				if (num[j] < num[i])
				{
					int temp = num[i];
					num[i] = num[j];
					num[j] = temp;
				}
			}
		}
		fin.close();
		remove("Highrecord.txt");
		ofstream fout("Highrecord.txt");
		for (int i = 0; i < 5; i++)
		{
			fout << num[i] << endl;
		}
		fout.close();
	}
}
void Display_high_record()
{
	int num = 0;
	ifstream fin("Highrecord.txt");
	if (!fin.is_open())
	{
		cout << "File is not Found !!" << endl;
	}
	else
	{
		for (int i = 0; fin >> num; i++)
		{
			cout << i + 1 << ". ";

			cout << num << endl;
		}
		cout << endl;
	}
	fin.close();
}
bool verify(char* arr, int size1)
{
	ifstream fin("dictionary.txt");
	if (!fin.is_open())
	{
		cout << "File is not found !!" << endl;
	}
	else
	{
		char* array = new char[1];
		int size = 0;
		char ch;
		int flag = 0;
		while (fin.get(ch))
		{
			if (ch == '\n')
			{
				if (size1 == size)
				{
					flag = 0;
					for (int i = 0; i < size; i++)
					{
						if (array[i] != arr[i] && array[i] - 32 != arr[i] && array[i] + 32 != arr[i])
						{
							flag = 1;
							break;
						}
					}
					if (flag == 0)
					{
						return true;
					}
				}
				delete[]array;
				array = new char[1];
				size = 0;
			}
			else
			{
				array = regrow(array, ch, size);
			}
		}
	}
	return false;
}
bool row_rev_wise(char* arr, int size, char** array, int row, int* col)
{
	if (arr[0] >= 'a' && arr[0] <= 'z')
	{
		arr[0] -= 32;
	}
	int flag = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = col[i] - 1; j >= 0; j--)
		{
			if (arr[0] == array[i][j])
			{
				flag = 0;
				int o = j;
				for (int k = 0; k <= size; k++, o--)
				{
					if (arr[k] != array[i][o] && arr[k] + 32 != array[i][o] && arr[k] - 32 != array[i][o])
					{
						flag = 1;
						break;
					}
				}
				if (flag == 0)
				{
					cout << "Start at (row " << i << ", col " << o + size << ")" << endl;
					cout << "End at (row " << i << ", col " << o << " ) " << endl;
					return true;
				}
			}
		}
	}
	return false;
}
bool row_wise(char* arr, int size, char** array, int row, int* col)
{
	if (arr[0] >= 'a' && arr[0] <= 'z')
	{
		arr[0] -= 32;
	}
	int flag = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col[i] - 1; j++)
		{
			if (arr[0] == array[i][j])
			{
				flag = 0;
				int o = j;
				for (int k = 0; k < size; k++, o++)
				{
					if (arr[k] != array[i][o] && arr[k] + 32 != array[i][o] && arr[k] - 32 != array[i][o])
					{
						flag = 1;
						break;
					}
				}
				if (flag == 0)
				{
					cout << "Start at (row " << i << ", col " << o - size << ")" << endl;
					cout << "End at (row " << i << ", col " << o - 1 << " ) " << endl;
					return true;
				}
			}
		}

	}
	return false;
}
bool col_rev_wise(char* arr, int size, char** array, int row, int* col)
{
	if (arr[0] >= 'a' && arr[0] <= 'z')
	{
		arr[0] -= 32;
	}
	int flag = 0;
	for (int i = col[0] - 1; i >= 0; i--)
	{
		for (int j = row - 1; j >= 0; j--)
		{
			if (arr[0] == array[j][i])
			{
				flag = 0;
				int o = j;
				for (int k = 0; k < size&&o >= 0; k++, o--)
				{
					if (arr[k] != array[o][i] && arr[k] + 32 != array[o][i] && arr[k] - 32 != array[o][i])
					{
						flag = 1;
						break;
					}
				}
				if (flag == 0)
				{
					cout << "Start at (row " << o + (size) << ", col " << i << ")" << endl;
					cout << "End at (row " << o + 1 << ", col " << i << " ) " << endl;
					return true;
				}
			}
		}
	}
	return false;
}
bool col_wise(char* arr, int size, char** array, int row, int* col)
{
	if (arr[0] >= 'a' && arr[0] <= 'z')
	{
		arr[0] -= 32;
	}
	int flag = 0;
	for (int i = 0; i < col[0]; i++)
	{
		for (int j = 0; j < row - 1; j++)
		{
			if (arr[0] == array[j][i])
			{
				flag = 0;
				int o = j;
				for (int k = 0; k <= size&&o<row; k++, o++)
				{
					if (arr[k] != array[o][i] && arr[k] + 32 != array[o][i] && arr[k] - 32 != array[o][i])
					{
						flag = 1;
						break;
					}
				}
				if (flag == 0)
				{

					cout << "Start at (row " << o - (size) << ", col " << i << ")" << endl;
					cout << "End at (row " << o - 1 << ", col " << i << " ) " << endl;
					return true;
				}
			}
		}

	}
	return false;
}
bool diag_wise(char* arr, int size, char** array, int row, int* col)
{
	int flag = 0;
	if (arr[0] >= 'a' && arr[0] <= 'z')
	{
		arr[0] -= 32;
	}
	for (int i = 0; i < row; i++)//Forward diagonal
	{
		for (int j = 0; j < col[i]; j++)
		{
			if (arr[0] == array[i][j])
			{
				flag = 0;
				int o = j;
				int p = i;
				for (int k = 0; k < size&&o<col[i] && p<row; k++, o++, p++)
				{
					if (arr[k] != array[p][o] && arr[k] + 32 != array[p][o] && arr[k] - 32 != array[p][o])
					{
						flag = 1;
						break;
					}
				}
				if (flag == 0)
				{
					cout << "Start at (row " << p - (size) << ", col " << o - (size) << ")" << endl;
					cout << "End at (row " << p - 1 << ", col " << o - 1 << " ) " << endl;
					return true;
				}
			}
		}
	}
	for (int i = row - 1; i >= 0; i--)//forward but reverse
	{
		for (int j = col[i] - 1; j >= 0; j--)
		{
			if (arr[0] == array[i][j])
			{
				flag = 0;
				int o = j;
				int p = i;
				for (int k = 0; k < size&&o >= 0 && p >= 0; k++, o--, p--)
				{
					if (arr[k] != array[p][o] && arr[k] != array[p][o] + 32 && arr[k] != array[p][o] - 32)
					{
						flag = 1;
						break;
					}
				}
				if (flag == 0)
				{
					cout << "Start at (row " << p + size << ", col " << o + size << ")" << endl;
					cout << "End at (row " << p + 1 << ", col " << o + 1 << " ) " << endl;
					return true;
				}
			}
		}
	}
	for (int i = 0; i < row; i++)//Backward diagnol
	{
		for (int j = col[i] - 1; j >= 0; j--)
		{
			if (arr[0] == array[i][j])
			{
				flag = 0;
				int o = j;
				int p = i;
				for (int k = 0; k < size&&o >= 0 && p<row; k++, o--, p++)
				{
					if (arr[k] != array[p][o] && arr[k] + 32 != array[p][o] && arr[k] - 32 != array[p][o])
					{
						flag = 1;
						break;
					}
				}
				if (flag == 0)
				{
					cout << "Start at (row " << p - (size) << ", col " << o + (size) << ")" << endl;
					cout << "End at (row " << p - 1 << ", col " << o + 1 << " ) " << endl;
					return true;
				}
			}
		}
	}
	for (int i = row - 1; i >= 0; i--)//backward but reverse
	{
		for (int j = 0; j < col[i]; j++)
		{
			if (arr[0] == array[i][j])
			{
				flag = 0;
				int o = j;
				int p = i;
				for (int k = 0; k < size&&o<col[i] && p >= 0; k++, o++, p--)
				{
					if (arr[k] != array[p][o] && arr[k] + 32 != array[p][o] && arr[k] - 32 != array[p][o])
					{
						flag = 1;
						break;
					}
				}
				if (flag == 0)
				{
					cout << "Start at (row " << p + (size) << ", col " << o - (size) << ")" << endl;
					cout << "End at (row " << p + 1 << ", col " << o - 1 << " ) " << endl;
					return true;
				}
			}
		}
	}
	return false;
}
bool find(char* arr, int size)
{
	ifstream fin("Board.txt");
	if (!fin.is_open())
	{
		cout << "File of board.txt is not Found !!" << endl;
	}
	else
	{
		char** array;
		int row = 0;
		int* col;
		read_board(fin, array, row, col);
		if (level == 1)
		{
			bool res = row_wise(arr, size, array, row + 1, col);
			if (res == false)
			{
				res = col_wise(arr, size, array, row + 1, col);
			}
			return res;
		}
		else if (level == 2)
		{
			bool res = row_wise(arr, size, array, row, col);
			if (res == false)
			{
				res = col_wise(arr, size, array, row, col);
				if (res == false)
				{
					res = row_rev_wise(arr, size, array, row, col);
					if (res == false)
					{
						res = col_rev_wise(arr, size, array, row, col);
					}
				}
			}
			return res;
		}
		else if (level == 3)
		{
			bool res = row_wise(arr, size, array, row + 1, col);
			if (res == false)
			{
				res = col_wise(arr, size, array, row + 1, col);
				if (res == false)
				{
					res = row_rev_wise(arr, size, array, row + 1, col);
					if (res == false)
					{
						res = col_rev_wise(arr, size, array, row + 1, col);
						if (res == false)
						{
							res = diag_wise(arr, size, array, row + 1, col);
						}
					}
				}
			}
			return res;
		}
		two_D_regrow(array, row);
		delete[]col;
		delete[]array;
		array = NULL;
		col = NULL;
	}
	return false;
}
void resum(char** array, int row, int* col)
{
	char choice;
	int count = 0;
	cout << "Press P or p for pause the game " << endl;
	cout << "Press w for enter word " << endl << " = ";
	cin >> choice;
	if (choice == 'P' || choice == 'p')
	{
		count = 0;
		ofstream fout("Pausedgame.txt");
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col[i]; j++)
			{
				fout << array[i][j];
			}
			cout << endl;
		}
		fout.close();
		system("Pause");
		while (true)
		{
			cout << "Press e for exit" << endl;
			cout << "Press r for resume " << endl << " = ";
			cin >> choice;
			if (choice == 'e' || choice == 'E')
			{
				exit(0);
			}
			else if (choice == 'R' || choice == 'r')
			{
				resum(array, row, col);
				break;
			}
			else
			{
				cout << "Input invalid" << endl;
			}
		}
	}
	else if (choice == 'W' || choice == 'w')
	{
		char* arr1;
		int size1 = 0;
		get_word(arr1, size1);
		bool res = verify(arr1, size1);
		if (res)
		{
			res = false;
			res = find(arr1, size1);
			if (res == true)
			{
				cout << "Word is found in board congrats" << endl;
				score += 10;
			}
			else
			{
				cout << "Word is not Found un Board Please try again" << endl;
				life--;
			}
		}
		else
		{
			cout << "Word does not Found in dictionary" << endl;
			life--;
		}
	}
	else
	{
		cout << "Input Invalid!!!" << endl;
	}
}
