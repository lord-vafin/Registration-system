#include"Header of Reg.System.h"

void menu()
{
	cout << "\t\t\t\t\t\tDATABASE VAFIN ARTUR"
		<< "\n\t\t\t\t\t\t 1.Sign up"
		<< "\n\t\t\t\t\t\t 2.Sign in"
		<< "\n\t\t\t\t\t\t 3.Admin profile"
		<< "\n\t\t\t\t\t\t 4.Exit";
}

void sign_up(vector <user>& users, const vector<string>& ranks, const string& user_range)
{
	user user_data;
	cout << "Введите ваше имя\n->";
	user_data.name = keyboard(NO_PROTECT);
	cout << "Введите вашу фамилию\n->";
	user_data.surname = keyboard(NO_PROTECT);
	vector<short> numbers;
	for (int i = 1; i < ranks.size(); i++)
	{
		cout << i << '.' << ranks[i] << '\n';
		numbers.push_back(i);
	}
	int number_rank = mygetch("Выберите вашу должность\n", numbers, "Номер вашей должности отсутствует в списке! Выберите еще раз!\n->");
	cout << "Создайте логин\n-> ";
metka:user_data.login = keyboard(NO_PROTECT);
	bool f = true;
	while (1)
	{
		myfor(i, 0,  users.size())
		{
			if (users[i].login == user_data.login)
				f = false;
		}
		if (!f)
		{
			cout << "Пользователь с таким логином уже существует! Создайте другой логин!\n->";
			goto metka;
		}
		else
			break;
	}
	string password1, password2;

password:cout << "\nСоздайте пароль\n->";

	password1 = keyboard(PROTECT);

	cout << "Подтвердите пароль \n->";

	password2 = keyboard(PROTECT);

	if (password1 != password2)
	{
		cout << "Пароли не совпадают!\nПовторите процедуру еще раз!";
		goto password;
	}

	user_data.password = md5(password1);
	ofstream filew;
	short number = 1;
	while (true)
	{
		if (exists(user_range + ranks[number_rank] + "#" + to_string(number) + ".txt"))
		{
			number++;
		}
		else
		{
			user_data.rank = ranks[number_rank];
			user_data.id = to_string(number);
			break;
		}
	}
	users.push_back(user_data);

	write_data(user_data, user_range);


}

void sign_in(const vector <user>& users, bool& successful_sign_in, short& index)
{
	string login, password;
	successful_sign_in = true;
	cout << "Введите логин\n->";
metka: login = keyboard(NO_PROTECT);
	while (1)
	{
		bool search = false;
		myfor(i, 0, users.size())
		{
			if (users[i].login == login)
			{
				index = i;
				search = true;
				break;
			}
		}
		if (!search)
		{
			cout << "Пользователь с введенным логином отутствует!\nВведите логин заново --> ";
			goto metka;
		}
		else
			break;
	}
	cout << "Введите пароль\n->";
	password = keyboard(PROTECT);
	short block = 1;
	while (md5(password) != users[index].password)
	{
		cout << "\nНеверный пароль! Осталось попыток: " << 3 - block << "\nПовторите ввод\n->";
		block++;
		password = keyboard(PROTECT);
		if (block == 3)
		{
			cout << "Вы были выгнаны с сервера, войдите заново\n";
			successful_sign_in = false;
			break;
		}
	}
}

void read_data(vector <user>& users, vector<string>& ranks, const string& user_range, const string& data_range)
{
	users = {};
	ranks = {};
	read_ranks(ranks, data_range);
	read_user_data(users, user_range);
}

void write_data(const user& user_data, const string& user_range)
{
	ofstream filew;

	filew.open(user_range + user_data.rank + '#' + user_data.id + ".txt");//открываем файл для очистки

	filew << "";

	filew << "name:\n" << user_data.name
		<< "\nsurname:\n" << user_data.surname
		<< "\nid:\n" << user_data.id
		<< "\nrank:\n" << user_data.rank
		<< "\nlogin:\n" << user_data.login
		<< "\npassword:\n" << user_data.password;

	filew.close();
}

void my_exit(bool& program, const int& KEY_3)
{
	cout << "Чтобы выйти, нажмие эту клавишу повторно или любую другую для возврата в меню\n";
	if (_getch() == KEY_3)
	{
		program = false;
		cout << "\nВыход ...";
	}
}

void read_ranks(vector<string>& ranks, const string& data_range)
{
	ifstream filer;

	filer.open(data_range);

	string rank;
	while (getline(filer, rank))
	{
		ranks.push_back(rank);
	}
}

void profile(vector <user>& users, const short& index, bool& successful_sign_in, const string& user_range)
{
	if (successful_sign_in)
	{
		cout << "\nHello, " << users[index].name << ' ' << users[index].surname << "\nrank: " << users[index].rank << "\nid: " << users[index].id;

		short key = 0;

		while (successful_sign_in)
		{
			switch (key)
			{
			case 0:
			{
				cout << "\n\tActions: \n"
					<< "\t1.Edit profile"
					<< "\n\t2.Exit to the main menu";

				key = mygetch("\nВыберите пункт меню\nClick-->", { 1,2 }, "\nНе соответствует номеру пункта меню! Нажмите еще раз!\n-->");
				break;
			}
			case 1:
			{
				edit_data(users, index, user_range);

				key = 0;
				break;
			}

			case 2:
			{
				cout << "Exit to the main menu\n";

				successful_sign_in = false;
				break;
			}
			}
		}
	}
}

void admin_profile(vector <user>& users, vector<string>& ranks, const short& index, bool successful_sign_in, const string& user_range, const string& data_range)
{
	if (successful_sign_in && users[index].rank == ranks[0])
	{
		cout << "\nHello, [Admin] " << users[index].name << ' ' << users[index].surname << "\nid: " << users[index].id;

		short key = 0;

		while (successful_sign_in)
		{
			switch (key)
			{
			case 0:
			{
				cout << "\n\tActions: \n"
					<< "\t1.Edit profile\n"
					<< "\t2.Read data\n"
					<< "\t3.Edit user data\n"
					<< "\t4.Delete user\n"
					<< "\t5.Exit to the main menu";

				key = mygetch("\nВыберите пункт меню\nClick-->", { 1,2,3,4,5 }, "\nНе соответствует номеру пункта меню! Нажмите еще раз!\n-->");
				break;
			}
			case 1:
			{
				edit_data(users, index, user_range, true, ranks);

				key = 0;
				break;
			}

			case 2:
			{
				cout << "\nReading data..\n";

				read_data(users, ranks, user_range, data_range);

				cout << "\nData read successful!\n";

				key = 0;
				break;
			}
			case 3:
			{
				for (int i = 1; i < users.size(); i++)
				{
					cout << i << " " << users[i].rank << '#' << users[i].id << ' ' << users[i].surname << ' ' << users[i].name << '\n';
				}
				int edit_index;

				cout << "\nВведите номер профиля для редактирования:\n-> ";

				cin >> edit_index;

				edit_data(users, edit_index, user_range, true, ranks);
			}
			case 4:
			{
				deleting(users, user_range);

				key = 0;
				break;
			}
			case 5:
			{
				cout << "\nExit to the main menu..\n";

				successful_sign_in = false;
				break;
			}

			}
		}
	}
	else
	{
		cout << "\nНе удалось проверить ваши полномочия Администратора\n";
	}
}

void deleting(vector<user>& users, const string& user_range)
{
	for (int i = 1; i < users.size(); i++)
	{
		cout << i << " " << users[i].rank << '#' << users[i].id << ' ' << users[i].surname << ' ' << users[i].name << '\n';
	}

	int number1, number2;

	cout << "\nВведите номер профиля для удаления:\n-> ";
	cin >> number1;

	cout << "Подвердите удаление, повторно введя номер профиля\n->";
	cin >> number2;

	if (number1 == number2 && number1 != 0)
	{
		string rank = users[number1].rank;
		string id = users[number1].id;
		remove(user_range + users[number1].rank + '#' + users[number1].id + ".txt");
		users.erase(users.begin() + number1);
		cout << "Удаление " << rank + '#' + id << " успешно завершено!\n";
	}
	else if (number1 == 0 && number2 == 0)
		cout << "Невозможно удалить профиль Администратора!\n";

}

void edit_data(vector<user>& users, const short& edit_index, const string& user_range, bool admin, const vector<string>& ranks)
{
	bool edit = true;
	int key = 0;
	while (edit)
	{

		switch (key)
		{
		case 0:
		{
			string message = "";
			if (users[edit_index].rank == "admin")
				message = " [only from admin profile]";
			else if (!admin)
				message = " [no rights]";

			cout << "\n1.name\n2.Surname\n3.Rank" << message
				<< "\n4.login\n5.password\n6.exit to profile";

			key = mygetch("\nНажмите номер пункта данных для редактирования\nClick-->", { 0,1,2,3,4,5,6 }, "\nНе соответствует номеру пункта меню! Нажмите еще раз!\n-->");
			break;
		}
		case 1:
		{
			cout << "Введите новое имя пользователя\n-> ";

			users[edit_index].name = keyboard(NO_PROTECT);

			write_data(users[edit_index], user_range);

			key = 0;
			break;
		}
		case 2:
		{
			cout << "Введите новую фамилию пользователя\n-> ";

			users[edit_index].surname = keyboard(NO_PROTECT);

			write_data(users[edit_index], user_range);

			key = 0;
			break;
		}
		case 3:
		{
			if (admin)
			{
				vector<short> numbers;
				myfor(i, 0, ranks.size())
				{
					cout << i + 1 << '.' << ranks[i] << '\n';
					numbers.push_back(i);
				}
				int number_rank = mygetch("Выберите вашу должность\n", numbers, "Номер вашей должности отсутствует в списке! Выберите еще раз!\n->") - 1;
				users[edit_index].rank = ranks[number_rank];
			}
			else if (users[edit_index].rank == "admin")
			{
				cout << "\nВам доступно изменение этого пункта только в профиле Админа!\n";
			}
			else
			{
				cout << "\nУ вас нет прав для изменения этих данных!\n";
			}

			key = 0;
			break;
		}
		case 4:
		{
			cout << "Введите новый логин пользователя\n-> ";

			string login;

		metka:login = keyboard(NO_PROTECT);

			bool search = true;

			while (1)
			{
				myfor(i, 0, users.size())
				{
					if (users[i].login == login && i != edit_index)
						search = false;
				}
				if (!search)
				{
					cout << "Пользователь с таким логином уже существует! Создайте другой логин!\n->";
					goto metka;
				}
				else
					break;
			}
			users[edit_index].login = login;

			write_data(users[edit_index], user_range);

			cout << "\nЛогин успешно изменен!\n";

			key = 0;
			break;
		}
		case 5:
		{
			cout << "Введите старый пароль пользователя\n-> ";

			string password;

			password = keyboard(PROTECT);

			while (md5(password) != users[edit_index].password)
			{
				cout << "Введенный старый пароль неверен! Введите еще раз\n->";
				password = keyboard(PROTECT);
			}
			cout << "Введите новый пароль\n->";

			password = keyboard(PROTECT);

			int block = 1;
			while (md5(password) != users[edit_index].password)
			{
				cout << "\nПароли не совпадают!\nПовторите ввод\n->";
				block++;
				password = keyboard(PROTECT);
			}


			write_data(users[edit_index], user_range);

			cout << "\nПароль успешно изменен!\n";

			key = 0;
			break;
		}
		case 6:
		{
			edit = false;
			break;
		}
		}
	}

}

char first_getch()
{
	int x = _getch();
	if (x == CTRL(c))
		exit(0);
	if (x == 0 || x == 224)
	{
		x = _getch();
		return char(256 + x);
	}
	return char(x);
}

short mygetch(const string& message, const vector<short>& keys, const string& defaultmessage)
{
	cout << message;
	while (true)
	{
		int symbol = first_getch() - '0';
		myfor(i, 0, keys.size())
		{
			if (keys[i] == symbol)
			{
				cout << symbol << '\n';
				return symbol;
			}
		}
		cout << defaultmessage;
	}
}

void read_user_data(vector<user>& users, const string& user_range)
{
	vector<string> user_files = get_files(user_range);
	user user_data;
	ifstream filer;
	string garbage;
	myfor(i, 0, user_files.size())
	{
			filer.open(user_files[i]);
			getline(filer, garbage);
			getline(filer, user_data.name);
			getline(filer, garbage);
			getline(filer, user_data.surname);
			getline(filer, garbage);
			getline(filer, user_data.id);
			getline(filer, garbage);
			getline(filer, user_data.rank);
			getline(filer, garbage);
			getline(filer, user_data.login);
			getline(filer, garbage);
			getline(filer, user_data.password);

			filer.close();
			users.push_back(user_data);
	}
}

string keyboard(const enum intype& type)
{
	string pas_sword = "";
	char symbol;
	while (1)
	{
		symbol = _getch();
		if (symbol == char(13))
			break;
		switch (symbol)
		{
		case char(0):
		case char(224):
		{
			_getch();
			break;
		}
		case CTRL(c):
		{
			exit(0);
			break;
		}
		case char(8) :
		{
			if(pas_sword.size()>0)
			{
				pas_sword.pop_back();
				cout << "\b \b";
			}
			break;
		}
		default:
		{
			pas_sword += symbol;
			if (type == PROTECT)
				cout << '*';
			else if (type == NO_PROTECT)
				cout << symbol;
			break;
		}
		}
	}
	cout << '\n';
	return pas_sword;
}

vector<string> get_files(const string& path)
{
	vector<string> paths;
	for (const auto& entry : directory_iterator(path))
		paths.push_back(entry.path().string());
	
	return paths;
}


void start()
{
	string text;
	ofstream filew;
	string main_path = "data/";
	create_directory(main_path);
	string user_path = "user_data/";
	string admin = "admin#1.txt";

	create_directory(main_path + user_path);
	if (!exists(main_path + user_path + admin))
	{
		filew.open(main_path + user_path + admin);
		text = "name :\nAdmin\nsurname:\nAdminbl4\nid:\n1\nrank:\nadmin\nlogin:\nAdmin\npassword:\n" + md5("Admin");
		filew << text;
		filew.close();
	}
	string data_path = "program_data/";
	string ranks = "ranks.txt";
	create_directory(main_path + data_path);
	if (!exists(main_path + data_path + ranks))
	{
		filew.open(main_path + data_path + ranks);
		text = "admin\nuser";
		filew << text;
		filew.close();
	}
}

//by OpenAI
string md5(const string& str)
{
	typedef unsigned char uint8;
	typedef unsigned int uint32;

	const uint8* data = reinterpret_cast<const uint8*>(str.c_str());
	const size_t len = str.size();

	const size_t blockSize = 64;
	const size_t numBlocks = ((len + 8) / blockSize) + 1;
	const size_t totalLen = numBlocks * blockSize;

	uint8* input = new uint8[totalLen];
	memcpy(input, data, len);
	input[len] = 0x80;
	uint32* dwordInput = reinterpret_cast<uint32*>(input);
	dwordInput[totalLen / 4 - 2] = len * 8;

	uint32 s[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
	};

	uint32 K[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};

	uint32 h[4] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };

	for (size_t i = 0; i < numBlocks; ++i)
	{
		uint32 M[16];
		memcpy(M, input + i * blockSize, blockSize);

		uint32 a = h[0];
		uint32 b = h[1];
		uint32 c = h[2];
		uint32 d = h[3];

		for (size_t j = 0; j < 64; ++j)
		{
			uint32 F;
			uint32 g;

			if (j < 16)
			{
				F = (b & c) | ((~b) & d);
				g = j;
			}
			else if (j < 32)
			{
				F = (d & b) | ((~d) & c);
				g = (5 * j + 1) % 16;
			}
			else if (j < 48)
			{
				F = b ^ c ^ d;
				g = (3 * j + 5) % 16;
			}
			else
			{
				F = c ^ (b | (~d));
				g = (7 * j) % 16;
			}

			uint32 tmp = d;
			d = c;
			c = b;
			b = b + ((a + F + K[j] + M[g]) << s[j]);
			a = tmp;
		}

		h[0] += a;
		h[1] += b;
		h[2] += c;
		h[3] += d;
	}

	std::stringstream ss;
	ss << std::hex << std::setfill('0');
	for (size_t i = 0; i < 4; ++i)
		ss << std::setw(8) << (h[i] & 0xffffffff);

	std::string result = ss.str();
	delete[] input;
	return result;
}