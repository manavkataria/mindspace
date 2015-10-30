#include "kinect_gl.h"
//#include <fstream>

extern void kinect_GL_glue(int diff_x, int diff_y, int diff_z);
GLubyte * z32 = new GLubyte[640 * 480 * 4];


#define DEPTH_BG_KILL_LOW	220
#define DEPTH_BG_KILL_HIGH	255
#define DEPTH_MAX			255
using namespace cv;
using namespace std;
Mat img(480,640,CV_8U);
CvMat cvimg;
CBlobResult hand;
IplImage iplhand;
CBlob hand_blob;
//extern ofstream debugfile;
unsigned int x_center=0,y_center=0, y_prev=0, x_prev=0, depth_prev=0, depth=0;
int diff_x=0, diff_y=0, diff_z=0;
const int KinectGL::WIDTH(640);
const int KinectGL::HEIGHT(480);

//RGB: 
/* 
void KinectGL::renderRGB()
{
	rgb->update();
	rgb->render();	
} */

void
KinectGL::renderZ()
{
	z->update();
	z->render();
}

bool
KinectGL::start()
{
	//RGB: rgb = new KinectTextureGL(640, 480, 3, GL_BGR_EXT);
	z = new KinectTextureGL(640, 480, 3, GL_RGB);

	return Kinect::start();
}


void 
KinectGL::update()
{
	if (initialized)
	{
		//RGB: GetNUICameraColorFrameRGB24(camera, (PBYTE)rgb->data, 500);
		GetNUICameraDepthFrameCorrected8(camera, (PBYTE)z32, 500);

		//	debugfile << "Update: " <<endl;
		
		unsigned int v;
		int i,j,a;

		x_prev = x_center;
		y_prev = y_center;
		depth_prev = depth;

		for (i=0; i<480; i++){
			for(j=0; j<640; j++){

				a = (640*i+j) * 3;				
				v = DEPTH_MAX - z32[(640*i+j)];
				
				if ( (v>=DEPTH_BG_KILL_LOW) && (v<=DEPTH_BG_KILL_HIGH) ) {
					v = 0;
				}

				z->data[a] = v; 
				z->data[a + 1] = v; 
				z->data[a + 2] = v;

				//TODO: Use Hashdefine
				if (v>140 && v<250)
					img.at<uchar>(i,j)=255;
				else
					img.at<uchar>(i,j)=0;
				
			}
			//debugfile << "z32:[" << i << "]" << "=" << 
				//(unsigned int)z32[i] << endl;			
		}
	
		//TODO: Remove converstion if required
		//conversion from mat to iplimage
		iplhand=img;	
		hand=CBlobResult(&iplhand,NULL,0);
		//hand.Filter( hand, B_EXCLUDE, CBlobGetArea(), B_LESS, 500);
		
		if (hand.GetNumBlobs()!=0)
		{
			//cout<<hand.GetNumBlobs()<<" ";
			hand.GetNthBlob(CBlobGetArea(),0,hand_blob);	
			x_center=int((hand_blob.MaxX()+ hand_blob.MinX())/2);	
			y_center=int((hand_blob.MaxY()+ hand_blob.MinY())/2);		
		} else {
			x_center=x_prev;
			y_center=y_prev;
		}
		
		//temp: depth from grayscale
		depth = z->data[(640*y_center+x_center) * 3];
		diff_z = depth - depth_prev;

		diff_x = x_center - x_prev;	
		diff_y = y_center - y_prev;	
			
		kinect_GL_glue(diff_x, diff_y, diff_z);
			
		//cvimg=img;
		imshow("abc",img);
		waitKey(2);
		//diff_x=min_loc_x-min_prev_x;
		//diff_y=min_loc_y-min_prev_y;
		//cout<<"x_diff: "<<diff_x<<" y_diff: "<<diff_y<<endl;
		//cout<<"x_diff: "<<x_center<<" y_diff: "<<y_center<<endl;
		//if(diff_y>0) cout<<"Positive  ";
		//else if(diff_y<0) cout<<"Negative  ";

	}
}

KinectGL::KinectGL()
{

}

KinectGL::~KinectGL()
{
	//RGB: delete rgb;
	delete z;
}