// lab_6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <algorithm>
using namespace std;

class MArray
{
	int MAX = 100;
	unsigned char* arr;
	int len;
public:
	MArray() : len(0), arr(NULL) {
	};
	MArray(int n) : len(n) {
		arr = new unsigned char[n];
		for (int i = 0; i < n; i++) {
			arr[i] = 0;
		}
	}
	MArray(unsigned char* s) {
		for (int16_t i = 0; s[i] != '\0'; i++) {
			this->len++;
		}
		len++;
		this->arr = new unsigned char[len];
		for (int16_t i = 0; i < len; i++) {
			this->arr[i] = s[i];
		}
	}
	int length() { return len; }

	unsigned char& operator[](const int i) {
		unsigned char ch = '\0';
		if (i < 0 || i > MAX) return ch;
		return arr[i];
	}

	unsigned char* getArr() {
		return arr;
	}

	friend ostream& operator<<(ostream& out, MArray& a);

	virtual MArray& operator+(MArray& in_arr)
	{
		int size = max(this->length(), in_arr.length());
		MArray* buffer = new MArray(size);
		int rank_overflow = 0;
		for (int i = 0; i < size; i++)
		{
			int current_rank_value = rank_overflow;
			if (i < this->length())
			{
				current_rank_value += getArr()[i];
			}

			if (i < in_arr.length())
			{
				current_rank_value += in_arr.getArr()[i];
			}

			int write_rank_value = current_rank_value % 10;
			rank_overflow = current_rank_value / 10;
			buffer->getArr()[i] = write_rank_value;
		}

		if (rank_overflow != 0) //осталось несложенное число
		{
			unsigned char* src = buffer->arr;
			buffer->len++;
			buffer->arr = new unsigned char[buffer->len];
			for (int i = 0; i < buffer->len; i++)
			{
				buffer->arr[i] = src[i];
			}
			buffer->arr[len - 1] = rank_overflow;
		}
		return *buffer;
	}
};

ostream& operator<<(ostream& out, MArray& a) {
	for (int i = 0; i < a.len; i++) {
		if (i + 1 == a.len) {
			out << (int)a.arr[i] << endl;
		}
		else {
			out << (int)a.arr[i] << ", ";
		}
	}
	return out;
}

class Decimal : public MArray {
	char sign;
public:
	Decimal() : MArray() {
	};
	Decimal(int sign,int n) : MArray(n) {
	};
	Decimal(const MArray& arr) : MArray(arr) {
	};
	Decimal(char sign, unsigned char* arr) : MArray(arr) {
		this->sign = sign;
	}
	MArray& operator+(MArray& in_arr) override {
		unsigned char * src = this->getArr();
		int max_len = max(this->length(), in_arr.length());
		Decimal ret(sign,max_len);

		int min_len = min(this->length(), in_arr.length());
		if (sign == '-') {
			for (int i = 0; i < max_len; i++) {
				int sum = getArr()[i] - in_arr.getArr()[i] + ret[i];
			}
		}
		else {
			for (int i = 0; i < max_len; i++)
			{
				if (i <= min_len) {
					int sum = getArr()[i] + in_arr.getArr()[i] + ret[i];
					if (sum > 9) {
						ret[i] = sum % 10;
						ret[i + 1] = 1;
					}
					else {
						ret[i] = sum;
					}
				}
				else {
					ret[i] = ((min_len == this->length()) ? in_arr.getArr()[i] : getArr()[i]);
				}
			}
		}
		return ret;
	}

};

class String: public MArray {
public: 
	String() : MArray() {
	};
	String(int n) : MArray(n) {
	};
	String(unsigned char* s) : MArray(s) {};

	virtual MArray& operator+(MArray& in_arr) override {
		int length = this->length() + in_arr.length() - 1;
		String ret(length);

		for (int i = 0; i < this->length() - 1; i++) {
			ret[i] = this->getArr()[i];
		}
		for (int i = this->length() - 1; i < length; i++) {
			ret[i] = in_arr.getArr()[i - this->length() + 1];
		}
		return ret;
	}
	friend ostream& operator<<(ostream& out, String& a);
};
ostream& operator<<(ostream& out, String& a) {
	for (int i = 0; i < a.length(); i++) {
		if (i + 1 == a.length()) {
			out << a.getArr()[i] << endl;
		}
		else {
			out << a.getArr()[i] << ", ";
		}
	}
	return out;
}
int main()
{
	unsigned char* str = new unsigned char[5];
	for (int i = 0; i < 4; i++) {
		cin >> str[i];
	}
	str[4] = '\0';
	String s(str);
	String s_2(s);
	String res;
    MArray& obj = res;
	obj= s +s_2;
	cout << res;
	delete[] str;;

	Decimal d;
	Decimal d1('+',4);
	Decimal d2('-',4);
	for (int i = 0; i < d1.length(); i++)
	{
		int a = 0;
		cin >> a;
		d1[i] = a;
	}
	for (int i = 0; i < d2.length(); i++)
	{
		int a = 0;
		cin >> a;
		d2[i] = a;
	}
	if (d.sign = '-'){
		Decimal newD = d1 - d2;
		cout << newD;
	}
	else {
		Decimal newD = d1 + d2;
		cout << newD;
	}
	

}

