#pragma once

class Generator {
public:
	std::vector<int> Data;

	// заполняет вектор элементами по возрастанию от begin до num
	void DataAscend(int begin = 0, int num);

	// заполняет вектор num случайными элементами, в диапазоне от low до high
	void DataRandom(int num, int low, int high);

	// разбивает вектор размером num на fract частей и заполняет их четными\нечетными числами (чередуя). increase выбирает идут они
	// по возрастанию или по убыванию
	void DataOddEven(int num, int fract=2, bool increase=true);

	// заполняет вектор прыгающими данными (increase выбирает уменьшается разрыв или увеличивается(изначально уменьшается))
	void DataJump(int num, bool increase=false);

	// Заполняет вектор граничными значениями
	void DataEdge();

	// Заполняет вектор возрастающими значениями в количестве десять в степени power_of_ten
	void DataStress(int power_of_ten);
};

