#ifndef TRACKINGHPP
#define TRACKINGHPP

#include <vector>

class Focus{
	private:
		float mean_x; 
		float mean_y;
		float border;
		float resting_border;
		float resting_center_x;
		float resting_center_y;

	public:

		Focus(Mat& frame, float border=0.1){

		}

		~Focus(){}

		void update(vector<float[4]> bboxes, Mat& frame, double target_ratio=0.55){
			float t_resting_center_x = resting_center_x;
			float t_resting_center_y = resting_center_y;
			if (bboxes.length() > 0){
				mean_x 
			}
		}

		Mat crop(Mat& frame){
			
		}
};


#endif
