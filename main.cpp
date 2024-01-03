#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std::chrono_literals;//1 sec

std::atomic<int> queue = 0;
int max_client = 10;

void client() {

	while (queue.load() < max_client)
	{
		queue.store(++queue, std::memory_order_relaxed);
		std::cout << "\nclient " << queue.load() << "\n";
		std::this_thread::sleep_for(1s);
	}
}

void operationist() {

	while (queue.load() != 0)
	{
		queue.store(--queue, std::memory_order_relaxed);
		std::cout << "\noperationist " << queue.load() << "\n";
		std::this_thread::sleep_for(2s);
	}
}

int main()
{
	std::thread c1(client);
	std::thread o1(operationist);

	if (c1.joinable()) {

		c1.join();
	}

	if (o1.joinable()) {

		o1.join();
	}

	return 0;
}