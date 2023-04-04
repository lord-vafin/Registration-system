#include"Header of Reg.System.h"

int main()
{
	SetConsoleCP(1251); SetConsoleOutputCP(1251);

	start();

	string user_range = "data/user_data/";//путь, по которому будут создаваться файлы пользователей
	string data_range = "data/program_data/ranks.txt";//путь, по которому лежат данные для программы

	vector <user> users;
	vector<string> ranks;

	read_data(users, ranks, user_range, data_range);

	bool successful_sign_in = false;
	short key = 0;
	short index;

	bool program = true;
	while (program)
	{
		switch (key)
		{
		case 0:
		{
			menu();

			key = mygetch("\nВыберите номер пункта\nClick --> ", { 0,1,2,3,4 }, "\nНе соответствует номеру пункта меню! Нажмите еще раз!\nClick --> ");

			break;
		}
		case 1:
		{
			sign_up(users, ranks, user_range);

			key = 0;

			break;
		}
		case 2:
		{
			sign_in(users, successful_sign_in, index);

			profile(users, index, successful_sign_in, user_range);

			key = 0;
			break;
		}
		case 3:
		{
			sign_in(users, successful_sign_in, index);

			admin_profile(users, ranks, index, successful_sign_in, user_range, data_range);

			key = 0;
			break;
		}
		case 4:
		{
			my_exit(program, KEY_4);

			key = 0;
			break;
		}
		}
	}
	cout << "\n\nРабота программы успешно завершена!\n\n Спасибо за работу!";

	_getch();
	return 0;
}
