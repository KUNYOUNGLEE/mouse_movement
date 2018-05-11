// mouse_movement.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

vector<string> get_arguments(int argc, char **argv)
{
	vector<string> arguments;

	for (int i = 0; i < argc; ++i)
	{
		arguments.push_back(string(argv[i]));
	}
	return arguments;
}

int calc_distance(int pre_x, int pre_y, int cur_x, int cur_y)
{
	return sqrt(pow(pre_x - cur_x, 2) + pow(pre_y - cur_y, 2));
}

int main(int argc, char **argv)
{
	vector<string> arguments = get_arguments(argc, argv);
	vector<string> names;
	//vector<string> arguments;
	names.push_back("temp");
	//arguments.push_back("mouse_movement.exe");
	//arguments.push_back("D:\\recording\\1.complete\\박지해2_2018-04-27-17-15\\2018-04-27-17-15.csv");
	//arguments.push_back("D:\\recording\\1.complete\\강은희1_2018-04-27-17-56\\2018-04-27-17-56.csv");
	//arguments.push_back("D:\\recording\\1.complete\\김수완1_2018-04-27-20-01\\2018-04-27-20-01.csv");


	// no arguments: output usage
	if (arguments.size() == 1)
	{
		cout << "입력 인수에 분석하고자할 .csv 파일을 입력!(경영학과 마우스 행동 분석)" << endl;
		return 0;
	}

	for (int i = 1; i < arguments.size(); i++)
	{
		string temp = arguments[i];
		int location = 0;
		for (int j = 0; j < 3; j++)
		{
			location = temp.find("\\");
			temp.erase(0, location + 1);
		}
		temp.assign(temp, 0, 7);
		names.push_back(temp);
	}

	string line;
	int line_num = 0;
	ofstream output_File("mouse_movement.csv");
	output_File << "name" << ',' << "total_distance" << ',' << "totaltime" << ',' << "distance/time" << ',' << "click" << endl;
	int totaltime = 0;

	for (int i = 1; i < arguments.size(); i++)
	{
		cout << arguments[i].c_str() << endl;
		line_num = 0;

		ifstream ReadFile(arguments[i]);
		float totaltime = 0.0;

		while (!ReadFile.eof()) {
			getline(ReadFile, line);
			line_num++;
			//cout << line_num << endl;
		}

		ReadFile.close();

		ReadFile.open(arguments[i]);

		//위에서 두번째까지는 환경정보가 쓰여있으므로 읽고 버린다.
		getline(ReadFile, line);
		getline(ReadFile, line);

		int pre_x = 0;
		int pre_y = 0;
		int cur_x = 0;
		int cur_y = 0;
		int cur_distance = 0;
		int click = 0;
		long long total_distance = 0;

		getline(ReadFile, line);
		std::stringstream oneline(line);
		string item;
		getline(oneline, item, ',');
		//cout << "x: " << stoi(item);
		pre_x = stoi(item);
		getline(oneline, item, ',');
		//cout << "y: " << stoi(item) << endl;
		pre_y = stoi(item);
		
		for (int i = 1; i < line_num - 4; i++)
		{
			getline(ReadFile, line);
			oneline.str(line);
			getline(oneline, item, ',');
			//cout <<"x: "<< stoi(item);
			cur_x = stoi(item);
			getline(oneline, item, ',');
			cur_y = stoi(item);
			//cout <<"y: "<< stoi(item) << endl;
			getline(oneline, item, ',');
			totaltime = stof(item);
			cur_distance = calc_distance(pre_x, pre_y, cur_x, cur_y);
			pre_x = cur_x;
			pre_y = cur_y;
			total_distance = total_distance + cur_distance;
		}

		getline(ReadFile, line);
		oneline.str(line);
		getline(oneline, item, ',');
		getline(oneline, item, ',');
		click = stoi(item);

		cout << total_distance << endl;

		output_File << names[i] << ',' << total_distance << ',' << totaltime << ',' << (float)total_distance/totaltime << ',' << click << endl;

		ReadFile.close();
	}

	output_File.close();

    return 0;
}

