#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

std::mutex mtx;
std::condition_variable cv;

int num = 1;
int maxNum = 100;

void printOdd(bool flag) {
	while (num < maxNum) {
		std::unique_lock<mutex> lock(mtx);
		cv.wait(lock, [&]() { return (num % 2); });
		cout << num << " ";
		num++;
		cv.notify_all();
		lock.unlock();	
	}
}

void printEven(bool flag) {
	while (num <= maxNum) {
		std::unique_lock<mutex> lock(mtx);
		cv.wait(lock, [&]() { return ((num % 2) == 0); });
		cout << num << " ";
		num++;
		cv.notify_all();
		lock.unlock();
	}
}

int main() {
	thread t1(printOdd, true);
	thread t2(printEven, false);

	t1.join();
	t2.join();

}