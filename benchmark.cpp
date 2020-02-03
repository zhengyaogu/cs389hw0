#include <iostream>
#include <vector>
#include <random>
#include <stdlib.h>
#include <chrono>
#include <numeric>
#include <string>
#include <memory>

// Create a list of 'size' floating point numbers in the range [-bound, bound]
std::shared_ptr<std::vector<double>> generate_random_list(size_t size, double bound)
{
	std::shared_ptr<std::vector<double>> floats (new std::vector<double>(size, 0.0));
	for (int i = 0; i < size; ++i)
	{
    	std::mt19937 gen(size);
		std::uniform_real_distribution<> dis(-1.0, 1.0);
		double number = dis(gen);
		floats->at(i) = (number);
	}
	return floats;
}

void update_coords(std::shared_ptr<std::vector<double>> xs_ptr,
				   std::shared_ptr<std::vector<double>> ys_ptr,
				   std::shared_ptr<std::vector<double>> zs_ptr,
				   std::shared_ptr<std::vector<double>> vx_ptr,
				   std::shared_ptr<std::vector<double>> vy_ptr,
				   std::shared_ptr<std::vector<double>> vz_ptr)
{
	for (int i = 0; i < xs_ptr->size(); ++i)
	{
		xs_ptr->operator[](i) = xs_ptr->operator[](i) + vx_ptr->operator[](i);
		ys_ptr->operator[](i)= ys_ptr->operator[](i)+ vy_ptr->operator[](i);
        zs_ptr->operator[](i) = zs_ptr->operator[](i) + vz_ptr->operator[](i);
	}
}

bool is_numeric(char* s)
{
	for (char* it = s; *it; ++it)
	{
		if (!isdigit(*it)) { return false;}
	}
	return true;
}

int main(int argc, char **argv)
{
	try
	{
		if (argc != 3) {throw -1;}
	}
	catch (int e)
	{
		std::cout << "You should pass 2 arguments to this executable.";
		return -1;
	}

	auto size_str = argv[1];
	auto iters_str = argv[2];

	try
	{
		if (!is_numeric(size_str) || !is_numeric(iters_str)) { throw -1;}
	}
	catch (int e)
	{
		std::cout << "input argument not nonnegative numeric";
		return -1;
	}
	
	unsigned int size_uint = atoi(size_str);
	unsigned int iters_uint = atoi(iters_str);
	
	// for the type of the following pointers, see generate_random_list
	auto xs_ptr = generate_random_list(size_uint, 1000.);
	auto ys_ptr = generate_random_list(size_uint, 1000.);
	auto zs_ptr = generate_random_list(size_uint, 1000.);
	auto vx_ptr = generate_random_list(size_uint, 1.);
	auto vy_ptr = generate_random_list(size_uint, 1.);
	auto vz_ptr = generate_random_list(size_uint, 1.);

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < iters_uint; ++i)
	{
		update_coords(xs_ptr, ys_ptr, zs_ptr, vx_ptr, vy_ptr, vz_ptr);
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

	auto chksum = std::accumulate(xs_ptr->begin(), xs_ptr->end(), 0) +
				    std::accumulate(ys_ptr->begin(), ys_ptr->end(), 0) +
					std::accumulate(zs_ptr->begin(), zs_ptr->end(), 0);
	std::cout << "Mean time per coordinate: " << std::to_string(duration.count() / (size_uint * iters_uint)) << "ns\n";
	std::cout << "Final checksum is: " << std::to_string(chksum) << "\n";
	
	return 0;
}

