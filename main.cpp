/*
 * This code is provided as part of "A Practical Introduction to Computer Vision with OpenCV"
 * by Kenneth Dawson-Howe © Wiley & Sons Inc. 2014.  All rights reserved.
 */
#include "Frame.h"

Frame* frame_r1;
Frame* frame_r2;

int main(int argc, const char** argv)
{


#pragma region INIT
	char* file_location = "Media/";
	char* image_files[] = {
		"TrinityRegentHouse.jpg"
    };

	// Load images
	int number_of_images = sizeof(image_files)/sizeof(image_files[0]);
	Mat* image = new Mat[number_of_images];
	for (int file_no=0; (file_no < number_of_images); file_no++)
	{
		string filename(file_location);
		filename.append(image_files[file_no]);
		image[file_no] = imread(filename, -1);
		if (image[file_no].empty())
		{
			cout << "Could not open " << image[file_no] << endl;
			return -1;
		}
	}

	// Load video(s)
	char* video_files[] = { 
		"ObjectAbandonmentAndRemoval1.avi",
		"ObjectAbandonmentAndRemoval2.avi"};
	int number_of_videos = sizeof(video_files)/sizeof(video_files[0]);
	VideoCapture* video = new VideoCapture[number_of_videos];
	for (int video_file_no=0; (video_file_no < number_of_videos); video_file_no++)
	{
		string filename(file_location);
		filename.append(video_files[video_file_no]);
		video[video_file_no].open(filename);
		if( !video[video_file_no].isOpened() )
		{
			cout << "Cannot open video file: " << filename << endl;
			return -1;
		}
	}
#pragma endregion

	Mat default_image = ComputeDefaultImage( image[0] );
	imshow("Welcome",default_image);

//TAKE IN FRAMES
	int num_frames = (int)video[0].get(CV_CAP_PROP_FRAME_COUNT);
	int size = (int)num_frames;
	cout << "frames: " << num_frames << endl;
	Mat current_frame;
	Mat* frames = new Mat[num_frames];
	bool more_frames = video[0].grab();
	int i = 0;
	while(more_frames){
		 video[0].retrieve(frames[i]);
		 i++;
		 more_frames = video[0].grab();
	}
	
//MEDIAN SHIFT 1
	MedianBackground median_background(frames[0], (float) 1.001,8);
	
	Mat median_background_image, median_foreground_image, median_difference;
//MEDIAN SHIFT 2
	MedianBackground median_background_2( frames[0], (float) 1.011,8);
	Mat median_background_image_2, median_foreground_image_2, median_difference_2;
	Mat current_frame_2;
	//imshow("frame 183", frames[183]);
	Mat difference;
	//keep updating current frame loop:
	for(int i = 0; i<185; i++){
	
		
		current_frame = frames[i];
		
		median_background.UpdateBackground(current_frame);
		median_background_image = median_background.GetBackgroundImage();
		
		absdiff(median_background_image,current_frame,median_difference);
		cvtColor(median_difference, median_difference, CV_BGR2GRAY);
		threshold(median_difference,median_difference,30,255,THRESH_BINARY);
		median_foreground_image.setTo(Scalar(0,0,0));
		current_frame.copyTo(median_foreground_image, median_difference);
		
		current_frame_2 = frames[i];
		median_background_2.UpdateBackground( current_frame_2 );
		median_background_image_2 = median_background_2.GetBackgroundImage();
		absdiff(median_background_image_2,current_frame_2,median_difference_2);	
		cvtColor(median_difference_2, median_difference_2, CV_BGR2GRAY);
		threshold(median_difference_2,median_difference_2,30,255,THRESH_BINARY);
		median_foreground_image_2.setTo(Scalar(0,0,0));
		current_frame_2.copyTo(median_foreground_image_2, median_difference_2);
		if((i>170)){
			//imshow("frame %d" + to_string(i), current_frame);
			//imshow("back 1 %d" + to_string(i), median_background.GetBackgroundImage());
			//imshow("fore 1 %d" + to_string(i), median_foreground_image);
			//imshow("diff 1 %d" + to_string(i), median_difference);
			//imshow("back 2 %d" + to_string(i), median_background_2.GetBackgroundImage());
			//imshow("fore 2%d" + to_string(i), median_foreground_image_2);
			//imshow("diff 2 %d" + to_string(i), median_difference_2);
			absdiff(median_background.GetBackgroundImage(), median_background_2.GetBackgroundImage(), difference);
			imshow(to_string(i), difference);
			absdiff(median_difference, median_difference_2, difference);
			imshow("diff diff"+to_string(i), difference);
		}
	}

//COMPARE MEDIANS


	int choice;
	while(true)
	{
		
		choice = cvWaitKey();
		
		
		
	} 
}
