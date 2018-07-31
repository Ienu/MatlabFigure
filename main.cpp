#include <iostream>
#include <string>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main(){
	while(true){
		char filename[1000] = "";
		cin >> filename;
		Mat src = imread(filename);
		int left = src.rows, top = src.cols, bottom = 0, right = 0;
		for(int i = 0; i < src.rows; ++i){
			for(int j = 0; j < src.cols; ++j){
				Vec3b value = src.at<Vec3b>(i, j);
				if(value[0] != 255 || value[1] != 255 || value[2] != 255){
					if(i < top){
						top = i;
					}
					if(i > bottom){
						bottom = i;
					}
					if(j < left){
						left = j;
					}
					if(j > right){
						right = j;
					}
				}
			}
		}
		left = (left >= 3) ? left - 3 : 0;
		top = (top >= 3) ? top - 3 : 0;
		right = (right < src.cols - 3) ? right + 3 : src.cols - 1;
		bottom = (bottom < src.rows - 3) ? bottom + 3 : src.rows - 1;

		Rect rect(left, top, right - left + 1, bottom - top + 1);
		Mat dst = src(rect);

		string str(filename);
		int pos = str.find_last_of('.');
		str[pos + 1] = 'b';
		str[pos + 2] = 'm';
		str[pos + 3] = 'p';
		cout << str << endl;
		imwrite(str.c_str(), dst);

		rectangle(src, Point(left, top), Point(right, bottom), Scalar(0, 0, 255), 2);

		imshow("src", src);
		waitKey(1);
	}
	return 0;
}
