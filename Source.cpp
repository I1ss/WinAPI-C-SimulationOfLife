#include <Windows.h>
#include <resource.h>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>

namespace life {
	class Animal;
	class Incubator;
	class IncubatorManager;
	double min_distantion(Animal& first, std::shared_ptr<life::Animal>& second);

	class ICommand {
	public:
		virtual bool execute(Animal& yours, std::vector<std::shared_ptr<life::Animal>>& some_p) = 0;
	};

	class IDog : public ICommand {
	public:
		bool execute(Animal& yours, std::vector<std::shared_ptr<life::Animal>>& some_p);
	};

	class ICat : public ICommand {
	public:
		bool execute(Animal& yours, std::vector<std::shared_ptr<life::Animal>>& some_p);
	};

	class IMouse : public ICommand {
	public:
		bool execute(Animal& yours, std::vector<std::shared_ptr<life::Animal>>& some_p);
	};

	class Incubator {
	public:
		virtual double* generate_hp() = 0;
		virtual double* generate_weigth() = 0;
		virtual double* generate_heigth() = 0;
		virtual double* generate_hungry() = 0;
		virtual int* generate_speed() = 0;
		virtual std::string generate_specific() = 0;
		virtual ICommand* generate_Command() = 0;
	};

	class CatIncubator : public Incubator {
	public:
		double* generate_hp() override {
			return new double(75);
		}
		double* generate_weigth() override {
			return new double(8);
		}
		double* generate_heigth() override {
			return new double(40);
		}
		double* generate_hungry() override {
			return new double(0);
		}
		int* generate_speed() override {
			return new int(2);
		}
		std::string generate_specific() override {
			return "Cat";
		}
		ICommand* generate_Command() override {
			return new ICat();
		}
	};

	class DogIncubator : public Incubator {
	public:
		double* generate_hp() override {
			return new double(100);
		}
		double* generate_weigth() override {
			return new double(30);
		}
		double* generate_heigth() override {
			return new double(70);
		}
		double* generate_hungry() override {
			return new double(0);
		}
		int* generate_speed() override {
			return new int(3);
		}
		std::string generate_specific() override {
			return "Dog";
		}
		ICommand* generate_Command() override {
			return new IDog();
		}
	};

	class MouseIncubator : public Incubator {
	public:
		double* generate_hp() override {
			return new double(100);
		}
		double* generate_weigth() override {
			return new double(5);
		}
		double* generate_heigth() override {
			return new double(10);
		}
		double* generate_hungry() override {
			return new double(0);
		}
		int* generate_speed() override {
			return new int(1);
		}
		std::string generate_specific() override {
			return "Mouse";
		}
		ICommand* generate_Command() override {
			return new IMouse();
		}
	};

	class Animal {
	private:
		double* hp;
		double* weigth;
		double* heigth;
		double* hungry;
		int* speed;
		int x = std::rand() % 20 * 30;
		int y = std::rand() % 15 * 30;
		ICommand* sounds;
		Incubator* incubator;
		std::string specific;
	protected:
		void fill_fields() {
			hp = incubator->generate_hp();
			weigth = incubator->generate_weigth();
			heigth = incubator->generate_heigth();
			hungry = incubator->generate_hungry();
			sounds = incubator->generate_Command();
			speed = incubator->generate_speed();
			specific = incubator->generate_specific();
		}
	public:
		Animal() : hp(nullptr), weigth(nullptr), heigth(nullptr), hungry(nullptr), speed(nullptr), x(0), y(0), sounds(nullptr), incubator(nullptr), specific("") {}
		Animal(const Animal& second);
		Animal& operator=(const Animal& second);
		Animal(Incubator* incubator_) : incubator(incubator_) {
			fill_fields();
		}
		inline int get_x() { return x; }
		inline int get_y() { return y; }
		inline double get_hungry() { return *hungry; }
		inline void set_x(int x) { this->x = x; }
		inline void set_y(int y) { this->y = y; }
		inline void complete_hungry(double hungry) { *this->hungry += hungry; }
		std::string get_specific() { return specific; }
		bool do_smth(std::vector<std::shared_ptr<life::Animal>>& some_p) {
			try {
				if (this == nullptr) {
					throw "bad object";
				}
			}
			catch (...) {
				return true;
			}
			for (int i = 0; i < *speed; i++) {
				if (sounds->execute(*this, some_p) == false) {
					return false;
				}
			}
			complete_hungry(1);
			return true;
		}
		~Animal() {
			delete hp;
			delete weigth;
			delete heigth;
			delete hungry;
			delete incubator;
			delete speed;
			delete sounds;
		}
	};

	class IncubatorManager {
	public:
		Animal* create_pet(std::string specific) {
			Animal* pet = nullptr;
			Incubator* incubator = nullptr;
			try
			{
				if (specific == "Dog") {
					pet = new Animal(new DogIncubator());
				}
				else if (specific == "Cat") {
					pet = new Animal(new CatIncubator());
				}
				else if (specific == "Mouse") {
					pet = new Animal(new MouseIncubator());
				}
				else {
					throw "Unknown object";
				}
			}
			catch (...)
			{
				MessageBox(nullptr, L"?????? ??? ???????? ????????.", L"??????!", MB_ICONASTERISK);
			}
			return pet;
		}
	};

	Animal::Animal(const Animal& second) {
		this->weigth = second.weigth;
		this->heigth = second.heigth;
		this->hungry = second.hungry;
		this->hp = second.hp;
		this->x = second.x;
		this->y = second.y;
		this->incubator = second.incubator;
		this->sounds = second.sounds;
		this->speed = second.speed;
		this->specific = second.specific;
	}
	Animal& Animal::operator=(const Animal& second) {
		this->weigth = second.weigth;
		this->heigth = second.heigth;
		this->hungry = second.hungry;
		this->hp = second.hp;
		this->x = second.x;
		this->y = second.y;
		this->incubator = second.incubator;
		this->sounds = second.sounds;
		this->speed = second.speed;
		this->specific = second.specific;
		return *this;
	}

	bool IDog::execute(Animal& yours, std::vector<std::shared_ptr<life::Animal>>& some_p) {
		size_t size = some_p.size(), index = 0;
		if (size == 0) {
			return true;
		}
		double length = min_distantion(yours, some_p[0]);
		for (size_t i = 1; i < size; i++) {
			if (min_distantion(yours, some_p[i]) < length) {
				length = min_distantion(yours, some_p[i]);
				index = i;
			}
		}
		if (yours.get_x() != some_p[index]->get_x()) {
			yours.set_x((yours.get_x() > some_p[index]->get_x()) ? yours.get_x() - 30 : yours.get_x() + 30);
		}
		else if (yours.get_y() != some_p[index]->get_y()) {
			yours.set_y((yours.get_y() > some_p[index]->get_y()) ? yours.get_y() - 30 : yours.get_y() + 30);
		}
		else {
			some_p.erase(some_p.begin() + index);
			yours.complete_hungry(-3);
		}
		if (yours.get_hungry() >= 2) {
			return false;
		}
		if (yours.get_x() > 570) { yours.set_x(0); }
		if (yours.get_y() > 420) { yours.set_y(0); }
		if (yours.get_x() < 0) { yours.set_x(570); }
		if (yours.get_y() < 0) { yours.set_y(420); }
		return true;
	}

	bool ICat::execute(Animal& yours, std::vector<std::shared_ptr<life::Animal>>& some_p) {
		size_t size = some_p.size(), index = 0;
		if (size == 0) {
			return true;
		}
		double length = min_distantion(yours, some_p[0]);
		for (size_t i = 1; i < size; i++) {
			if (min_distantion(yours, some_p[i]) < length) {
				length = min_distantion(yours, some_p[i]);
				index = i;
			}
		}
		if (yours.get_x() != some_p[index]->get_x()) {
			yours.set_x((yours.get_x() > some_p[index]->get_x()) ? yours.get_x() - 30 : yours.get_x() + 30);
		}
		else if (yours.get_y() != some_p[index]->get_y()) {
			yours.set_y((yours.get_y() > some_p[index]->get_y()) ? yours.get_y() - 30 : yours.get_y() + 30);
		}
		else {
			some_p.erase(some_p.begin() + index);
			yours.complete_hungry(-3);
		}
		if (yours.get_hungry() >= 3) {
			return false;
		}
		if (yours.get_x() > 570) { yours.set_x(0); }
		if (yours.get_y() > 420) { yours.set_y(0); }
		if (yours.get_x() < 0) { yours.set_x(570); }
		if (yours.get_y() < 0) { yours.set_y(420); }
		return true;
	}

	bool IMouse::execute(Animal& yours, std::vector<std::shared_ptr<life::Animal>>& some_p) {
		size_t size = some_p.size(), index = 0;
		if (size == 0) {
			return true;
		}
		double length = min_distantion(yours, some_p[0]);
		for (size_t i = 1; i < size; i++) {
			if (min_distantion(yours, some_p[i]) < length) {
				length = min_distantion(yours, some_p[i]);
				index = i;
			}
		}
		if (yours.get_x() != some_p[index]->get_x()) {
			yours.set_x((yours.get_x() > some_p[index]->get_x()) ? yours.get_x() - 30 : yours.get_x() + 30);
		}
		else if (yours.get_y() != some_p[index]->get_y()) {
			yours.set_y((yours.get_y() > some_p[index]->get_y()) ? yours.get_y() - 30 : yours.get_y() + 30);
		}
		if (yours.get_hungry() >= 4) {
			return false;
		}
		if (yours.get_x() > 570) { yours.set_x(0); }
		if (yours.get_y() > 420) { yours.set_y(0); }
		if (yours.get_x() < 0) { yours.set_x(570); }
		if (yours.get_y() < 0) { yours.set_y(420); }
		return true;
	}

	double min_distantion(Animal& first, std::shared_ptr<life::Animal>& second) {
		return sqrt(pow((first.get_x() - second->get_x()), 2) + pow((first.get_y() - second->get_y()), 2));
	}
}

std::string random(std::string first, std::string second, std::string third) {
	int temp = rand() % 10;
	if (temp <= 3) {
		return first;
	}
	else if (temp > 3 && temp < 8) {
		return second;
	}
	else {
		return third;
	}
}

void MyMenu(HWND hWnd) {
	HMENU hMainMenu = CreateMenu();
	HMENU hPopMenuFile = CreatePopupMenu();
	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, reinterpret_cast<UINT>(hPopMenuFile), L"???????");
	AppendMenu(hPopMenuFile, MF_STRING, 1, L"????");
	AppendMenu(hPopMenuFile, MF_SEPARATOR, -1, L"");
	AppendMenu(hPopMenuFile, MF_STRING, 2, L"????? ??????? ??????????: L1ss.");
	SetMenu(hWnd, hMainMenu);
	SetMenu(hWnd, hPopMenuFile);
}

DWORD WINAPI thread2(LPVOID hwnd1);
DWORD WINAPI thread3(LPVOID hwnd1);

class MyApp {
private:
	friend DWORD WINAPI thread2(LPVOID hwnd1);
	friend DWORD WINAPI thread3(LPVOID hwnd1);
	std::vector<std::shared_ptr<life::Animal>> cats, dogs, mouses;
	HWND a_hWnd, start_hWnd, generate_hWnd, clear_hWnd, stop_hWnd, * s_hWnds;
	HANDLE threadF, threadS;
	int const width = 800, heigth = 650;
	bool flag = true;
	void create_wnd(LPCWSTR name) {
		WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = nullptr;
		wc.hbrBackground = reinterpret_cast<HBRUSH>(CreateSolidBrush(RGB(230, 230, 250)));
		wc.lpszClassName = name;
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.lpszMenuName = nullptr;
		wc.hIcon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_ICON1));
		wc.hIconSm = wc.hIcon;
		wc.lpfnWndProc = get_ptr;
		wc.style = CS_VREDRAW | CS_HREDRAW;
		if (!RegisterClassEx(&wc)) {
			throw "smth bad";
		}
		RECT wnd_r{ 0, 0, width, heigth };
		AdjustWindowRect(&wnd_r, WS_OVERLAPPEDWINDOW, FALSE);
		a_hWnd = CreateWindow(name, L"???????", WS_SYSMENU | WS_DLGFRAME | WS_MINIMIZEBOX | WS_MAXIMIZE, (GetSystemMetrics(SM_CXSCREEN) - wnd_r.right) / 2,
			(GetSystemMetrics(SM_CYSCREEN) - wnd_r.bottom) / 2, width, heigth, nullptr, nullptr, nullptr, this);
		MyMenu(a_hWnd);
		create_native();
	}
	void create_native() {
		s_hWnds = new HWND[3];
		start_hWnd = CreateWindow(L"Button", L"??????!", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 10, 80, 30, a_hWnd, reinterpret_cast<HMENU>(3), nullptr, nullptr);
		generate_hWnd = CreateWindow(L"Button", L"???????? ??????!", WS_CHILD | WS_VISIBLE | WS_BORDER, 100, 10, 150, 30, a_hWnd, reinterpret_cast<HMENU>(4), nullptr, nullptr);
		clear_hWnd = CreateWindow(L"Button", L"????????!", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 50, 80, 30, a_hWnd, reinterpret_cast<HMENU>(5), nullptr, nullptr);
		stop_hWnd = CreateWindow(L"Button", L"????!", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_DISABLED, 10, 90, 80, 30, a_hWnd, reinterpret_cast<HMENU>(6), nullptr, nullptr);
	}
	static LRESULT CALLBACK get_ptr(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		static MyApp* self = nullptr;
		if (uMsg == WM_CREATE) {
			self = (MyApp*)((CREATESTRUCT*)lParam)->lpCreateParams;
			self->a_hWnd = hWnd;
		}
		if (self == nullptr) {
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		return self->wnd_proc(hWnd, uMsg, wParam, lParam);
	}
	LRESULT CALLBACK wnd_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if (uMsg == WM_DESTROY) {
			ExitProcess(EXIT_FAILURE);
		}
		else if (uMsg == WM_COMMAND) {
			if (LOWORD(wParam) == 1) {
				MessageBox(nullptr, L"????? ???? ??? ??????? ???????????. ??? ??????? ????????? ????? ? ????????, ??????? ? ??????!", L"??????????", MB_OK);
			}
			else if (LOWORD(wParam) == 2) {
				MessageBox(nullptr, L"lebedewgeorg@yandex.ru", L"???????? ?????", MB_OK);
			}
			else if (LOWORD(wParam) == 3) {
				threadF = CreateThread(NULL, 0, thread2, reinterpret_cast<LPVOID>(this), 0, NULL);
				EnableWindow(start_hWnd, FALSE);
				EnableWindow(stop_hWnd, TRUE);
			}
			else if (LOWORD(wParam) == 4) {
				generate();
				EnableWindow(generate_hWnd, FALSE);
				threadS = CreateThread(NULL, 0, thread3, reinterpret_cast<LPVOID>(this), 0, NULL);
				InvalidateRect(a_hWnd, nullptr, FALSE);
			}
			else if (LOWORD(wParam) == 5) {
				cats.clear();
				dogs.clear();
				mouses.clear();
				InvalidateRect(a_hWnd, nullptr, FALSE);
			}
			else if (LOWORD(wParam) == 6) {
				flag = false;
			}
		}
		else if (uMsg == WM_PAINT) {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(a_hWnd, &ps);
			HPEN hPen = CreatePen(2, 2, RGB(0, 0, 0));
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0)), hCat = CreateSolidBrush(RGB(255, 0, 0)), hDog = CreateSolidBrush(RGB(0, 0, 255)), hMouse = CreateSolidBrush(RGB(111, 111, 77));
			SelectObject(hdc, hPen);
			Rectangle(hdc, 100, 75, 700, 525);
			RECT wnd_r{ 101, 76, 698, 523 };
			FillRect(hdc, &wnd_r, hBrush);
			for (size_t i = 100; i < 700; i += 30) {
				MoveToEx(hdc, i, 75, nullptr);
				LineTo(hdc, i, 525);
			}
			for (size_t i = 75; i < 525; i += 30) {
				MoveToEx(hdc, 100, i, nullptr);
				LineTo(hdc, 700, i);
			}
			for (size_t i = 0; i < cats.size(); i++) {
				Rectangle(hdc, 100 + cats[i]->get_x(), 75 + cats[i]->get_y(), 100 + cats[i]->get_x() + 30, 75 + cats[i]->get_y() + 30);
				RECT wnd_t{ 100 + cats[i]->get_x() + 1, 75 + cats[i]->get_y() + 1, 100 + cats[i]->get_x() + 29, 75 + cats[i]->get_y() + 29 };
				FillRect(hdc, &wnd_t, hCat);
			}
			for (size_t i = 0; i < dogs.size(); i++) {
				Rectangle(hdc, 100 + dogs[i]->get_x(), 75 + dogs[i]->get_y(), 100 + dogs[i]->get_x() + 30, 75 + dogs[i]->get_y() + 30);
				RECT wnd_t{ 100 + dogs[i]->get_x() + 1, 75 + dogs[i]->get_y() + 1, 100 + dogs[i]->get_x() + 29, 75 + dogs[i]->get_y() + 29 };
				FillRect(hdc, &wnd_t, hDog);
			}
			for (size_t i = 0; i < mouses.size(); i++) {
				Rectangle(hdc, 100 + mouses[i]->get_x(), 75 + mouses[i]->get_y(), 100 + mouses[i]->get_x() + 30, 75 + mouses[i]->get_y() + 30);
				RECT wnd_t{ 100 + mouses[i]->get_x() + 1, 75 + mouses[i]->get_y() + 1, 100 + mouses[i]->get_x() + 29, 75 + mouses[i]->get_y() + 29 };
				FillRect(hdc, &wnd_t, hMouse);
			}
			if (s_hWnds[0] != nullptr) {
				DestroyWindow(s_hWnds[0]);
			}
			std::wstring temp = L"?????????? ?????: " + std::to_wstring(dogs.size());
			s_hWnds[0] = CreateWindow(L"Static", temp.c_str(), WS_BORDER | WS_VISIBLE | WS_CHILD, 260, 10, 165, 35, a_hWnd, nullptr, nullptr, nullptr);
			if (s_hWnds[1] != nullptr) {
				DestroyWindow(s_hWnds[1]);
			}
			if (s_hWnds[2] != nullptr) {
				DestroyWindow(s_hWnds[2]);
			}
			temp = L"?????????? ?????: " + std::to_wstring(cats.size());
			s_hWnds[1] = CreateWindow(L"Static", temp.c_str(), WS_BORDER | WS_VISIBLE | WS_CHILD, 435, 10, 165, 35, a_hWnd, nullptr, nullptr, nullptr);
			temp = L"?????????? ?????: " + std::to_wstring(mouses.size());
			s_hWnds[2] = CreateWindow(L"Static", temp.c_str(), WS_BORDER | WS_VISIBLE | WS_CHILD, 610, 10, 165, 35, a_hWnd, nullptr, nullptr, nullptr);
			temp.clear();
			DeleteObject(hPen);
			DeleteObject(hBrush);
			DeleteObject(hCat);
			DeleteObject(hDog);
			DeleteObject(hMouse);
			EndPaint(a_hWnd, &ps);
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	void work(std::vector<std::shared_ptr<life::Animal>>& petsf, std::vector<std::shared_ptr<life::Animal>>& petss) {
		for (int i = 0; i < petsf.size(); i++) {
			if (petsf[i]->do_smth(petss) == false) {
				petsf.erase(petsf.begin() + i);
			}
		}
	}
	int Run() {
		MSG msg;
		ShowWindow(a_hWnd, SW_SHOWDEFAULT);
		UpdateWindow(a_hWnd);
		while (GetMessage(&msg, nullptr, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return static_cast<int>(msg.wParam);
	}
	void generate() {
		life::IncubatorManager* inc = new life::IncubatorManager();
		int size = 25;
		std::vector<std::shared_ptr<life::Animal>> pets;
		pets.resize(size);
		for (int i = 0; i < size; i++) {
			std::string type = random("Dog", "Cat", "Mouse");
			pets[i] = static_cast<std::shared_ptr<life::Animal>>(inc->create_pet(type));
			if (type == "Cat") {
				cats.push_back(pets[i]);
			}
			else if (type == "Dog") {
				dogs.push_back(pets[i]);
			}
			else {
				mouses.push_back(pets[i]);
			}
		}
	}

public:
	MyApp() {
		std::wstring name = std::to_wstring(rand() % 1000000 - 1000000);
		create_wnd(name.c_str());
		generate();
		Run();
	}
};

DWORD WINAPI thread3(LPVOID hwnd1) {
	MyApp* self = reinterpret_cast<MyApp*>(hwnd1);
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	EnableWindow(self->generate_hWnd, TRUE);
	return 0;
}

DWORD WINAPI thread2(LPVOID hwnd1) {
	MyApp* self = reinterpret_cast<MyApp*>(hwnd1);
	while (true) {
		if ((self->dogs.size() + self->cats.size() + self->mouses.size()) > 256) {
			MessageBox(nullptr, L"?????????? ???????????? ?????????? ????????, ?????????????? ???? ??????????????! ????????????? ???????????? '????????'!", L"??????????????", MB_OK);
			break;
		}
		self->work(self->cats, self->mouses);
		self->work(self->dogs, self->cats);
		self->work(self->mouses, self->dogs);
		InvalidateRect(self->a_hWnd, nullptr, FALSE);
		UpdateWindow(self->a_hWnd);
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		if (self->cats.size() < 4 || self->dogs.size() < 4) {
			self->generate();
		}
		if (self->flag == false) {
			break;
		}
	}
	InvalidateRect(self->a_hWnd, nullptr, FALSE);
	EnableWindow(self->start_hWnd, TRUE);
	EnableWindow(self->stop_hWnd, FALSE);
	self->flag = true;
	return 0;
}

int wWinMain(HINSTANCE hInstace, HINSTANCE, PWSTR lpszCmdLine, int CmdShow) {
	MyApp temp;
	return 0;
}
