#include<iostream>
#include<vector>
#include<map>
#include<chrono>


using namespace std::chrono;
struct DurationData
{
	nanoseconds vector;
	nanoseconds map;
};
DurationData CheckDuration(const int precentage);
int main()
{
	for (int precentage = 50; precentage > 0; precentage--)
	{
		DurationData duration_data = CheckDuration(precentage);
		if (duration_data.vector.count() > duration_data.map.count())
		{
			std::cout << "Precentage: " << precentage << std::endl;
			std::cout << "Vector duration: " << duration_data.vector.count() << std::endl;
			std::cout << "Map duration:    " << duration_data.map.count() << std::endl;
			break;
		}
	}
}

DurationData CheckDuration(const int precentage)
{
	const int size = 100000;
	int array[size];
	std::vector<int> vec;
	std::map<int, int> map;
	for (int i = 0; i < size; i++)
	{
		if (i < ((size / 100) * precentage))
		{
			array[i] = 1;
		} else
		{
			array[i] = 0;
		}
	}
	//vector duration
	auto vector_start = std::chrono::high_resolution_clock::now();
	for (int elem : array)
	{
		vec.push_back(elem);
	}
	auto vector_stop = std::chrono::high_resolution_clock::now();
	auto vector_duration = duration_cast<nanoseconds>(vector_stop - vector_start);

	//map duration
	auto map_start = std::chrono::high_resolution_clock::now();
	for (int elem : array)
	{
		if (elem)
		{
			map.insert({ 1,elem });
		}
	}
	auto map_stop = std::chrono::high_resolution_clock::now();
	auto map_duration = duration_cast<nanoseconds>(map_stop - map_start);
	return { vector_duration,map_duration };
}


