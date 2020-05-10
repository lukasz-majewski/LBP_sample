#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <string> 
#include "local_binary_pattern.h"
#include <fstream>

#include <filesystem>
namespace fs = std::experimental::filesystem;

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
	enum Foo {
		One = 1,
		Two = 2,
		Three = 3,
		Four = 4,
		Five = 5,
		Six = 6,
		Last
	};
	std::ofstream myfile;
	myfile.open("lbp_eval18.csv");
	myfile << "File,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26\n";
	string filename;
	int n = 36;

	std::string path = "C:/Users/majewski.ZIPANGU/Desktop/cpp_lbp/out/";
	for (const auto& dir_entry : fs::directory_iterator(path)) {
		const std::string ff = dir_entry.path().string();

		cout << ff << endl;
		string filename = ff;
		const size_t last_slash_idx = filename.find_last_of("\\/");
		if (std::string::npos != last_slash_idx)
		{
			filename.erase(0, last_slash_idx + 1);
			cout << filename << endl;

			for (int i = 0; i < n; ++i) {
				Foo foo = static_cast<Foo>(i);
				std::string s = std::to_string(i);
				cout << "file :" + s + " ";
				string file = path + filename + "/" + filename + "_frame_" + s + ".0.jpg";
				cout << "--file :" + file;
				Mat image = imread(file, IMREAD_GRAYSCALE);

				if (image.empty())
				{
					cout << "no image" << endl;
					return -1;
				}

				cv::resize(image, image, cv::Size(200, 200));

				///////////////////////////////////
				//cv::Mat lbp_hist;
				cv::Mat lbp_hist_18;
				cv::Mat lbp_hist_216;
				cv::Mat lbp_hist_324;
				compute_LBP_1_8_hist(image, lbp_hist_18);
				cout << "lbp18: " << lbp_hist_18 << endl;
				//compute_LBP_2_16_hist(image, lbp_hist_216);
				//cout << "lbp216: " << lbp_hist_216 << endl;
				//compute_LBP_3_24_hist(image, lbp_hist_324);
				//cout << "lbp324: " << lbp_hist_324 << endl;
				////////////////////////////////////////////

				Mat lbp_image;
				LBP(image, lbp_image);


				int bt = cv::getTickCount();
				uniform_pattern(image, lbp_image);
				int et = cv::getTickCount();
				double t = (et - bt)*1000.0 / cv::getTickFrequency();
				printf("uniform_pattern : t = %d ms\n", (int)t);
				//myfile << "1_8" << "," << lbp_hist_18 << endl;
				//myfile << "2_16" << "," << lbp_hist_216 << endl;
				myfile << filename << "," << lbp_hist_18 << endl;
				//myfile << "time" << "," << (int)t << endl;

	}

		}
		
	}
	myfile.close();
	return 0;
}

