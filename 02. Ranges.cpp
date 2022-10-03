#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <memory>

class Range {
private:

	int from = 0;
	int to = 0;

public:
	Range() {};
	Range(int from, int to) : from(from), to(to){};
	const int getFrom() const { return from; }
	const int getTo() const { return to; }
	bool contains(int value) {
		return from <= value && value <= to;
	}

};

bool inRange(int value, const std::map<int, std::shared_ptr <Range>>& rangeByStart, const std::map<int, std::shared_ptr<Range>>& rangeByEnd) {
	auto fromIt = rangeByStart.upper_bound(value);
	if (fromIt == rangeByStart.begin())
	{
		return false;
	}
	fromIt--;
	auto toIt = rangeByEnd.lower_bound(value);
	if (toIt == rangeByEnd.end())
	{
		return false;
	}

	return fromIt->second == toIt->second;
}

int main() {
	std::cin.sync_with_stdio(false);
	std::cout.sync_with_stdio(false);
	std::map<int, std::shared_ptr<Range>> rangesByFrom;
	std::map<int, std::shared_ptr<Range>> rangesByTo;

	std::string line;
	while (std::getline(std::cin, line)&& line!= ".")
	{
		std::istringstream lineIn(line);
		int from = 0;
		int to = 0;
		lineIn >> from >> to;

		std::shared_ptr<Range> r = std::make_shared<Range>(from, to);
		rangesByFrom[from] = r;
		rangesByTo[to] = r;

	}

	std::ostringstream output;
	while (std::getline(std::cin, line) && line !=".")
	{
		std::istringstream lineIn(line);
		int value = 0;
		lineIn >> value;
		if (inRange(value,rangesByFrom,rangesByTo))
		{
			output << "in";
		}
		else
		{
			output << "out";
		}
		output << std::endl;
	}
	std::cout << output.str() << std::endl;


	return 0;
}