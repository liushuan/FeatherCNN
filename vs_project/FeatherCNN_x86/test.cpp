#include <iostream>
#include <net.h>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{
	int times = 10;

	feather::Net<float> forward_net(1, DeviceType::CPU);
	forward_net.InitFromPath("mobilenet_v1.feathermodel");

	float *input = new float[224 * 224 * 3];
	for (int i = 0; i < 224 * 224 * 3; i++)
		input[i] = 0.5f;

	auto time_3 = system_clock::now();
	for (int i = 0; i < times; i++)
		forward_net.Forward(input);
	auto time_4 = system_clock::now();

	float *arr = new float[1000];
	forward_net.ExtractBlob(arr, "fc7");

	for (int i = 0; i < 1000; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	auto duration_feather = duration_cast<microseconds>(time_4 - time_3);
	cout << "feather time: " << double(duration_feather.count()) / 1000 / times << "ms" << endl;

    return 0;
}
