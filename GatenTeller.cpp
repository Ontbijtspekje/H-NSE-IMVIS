#include "GatenTeller.h"
using namespace cv;
using namespace std;
#include <iostream>

GatenTeller::GatenTeller(Mat& src) {
    this->src = src;
    HEIGHT = src.rows;
    WIDTH = src.cols;
    dst = Mat::ones(HEIGHT, WIDTH, CV_8U) * 255; // Initialize dst with all pixels set to 255
    
}

void GatenTeller::tellen()
{
    int aantalGaten = 0;
    int innercorner = 0;
    int outercorner = 0;

    for (int h = 1; h < HEIGHT - 1; h++){
        for (int w = 1; w < WIDTH - 1; w++){  //loopen door afbeeldingpixels
            int wittepixels = 0; //wittepixels voor deze positie
           
            for (int i = -1; i < 1; i++){
               for (int j = -1; j < 1; j++){  // 2x2 matrix om te kijken naar de pixels 
                    if (src.at<uchar>(h + i, w + j) > 0) 
                        wittepixels++;
               }
            }
            //sheets3 slide 56:
            //wanneer er 1 pixel wit is en niet meer is het een buitenhoek van een wit vlak
            // wanneer er 3 pixels wit zijn is het een binnenhoek 
            if (wittepixels == 3)  // 3 witte pixels dus een binnenhoek
                innercorner++;
            if (wittepixels == 1) // 1 witte pixel is buitenhoek
                outercorner++;
        }
    }
    //gaten = ( #buitenhoeken - #binnenhoeken ) / 4 (sheets3 slide 59)
    aantalGaten = (outercorner - innercorner) / 4;  //een figuur bestaat uit 4 hoeken
    cout << "Hoeveelheid gaten = "  << aantalGaten << endl;
}

int GatenTeller::process() {
    int h, w;
    
    //vult destination met wit
    for (h = 0; h < HEIGHT; h++) {  //   for (h=0; h<HEIGHT; h++) 
        for (w = 0; w < WIDTH; w++) {           //         for(w=0; w<WIDTH; w++){
            dst.at<uchar>(h, w) = 255;  //Out->Content [h][w]=255;
        }
    }

    Label = 0;
    //loop door pixels
    for (h = 0; h < HEIGHT; h++) {  //   for (h=0; h<HEIGHT; h++) {
        for (w = 0; w < WIDTH; w++) {   // for(w=0; w<WIDTH; w++){
            //checked of h,w al gelabeld is en of de label niet overflowed wordt.
            if ((labelPixel(h, w) != 0) && (Label < 254)) { //if((labelPixel(h, w)!=0)&&(Label<254)) 
                Label++; //            Label++;
            }
        }
    }
    return Label;
}

uint8_t GatenTeller::labelPixel(int h, int w) {
    if (src.at<uchar>(h, w) == 255 && dst.at<uchar>(h, w) == 255 ) {  //  if((In->Content[h][w]==0)&&(Out->Content[h][w]==255)){
        //geeft pixel label
        dst.at<uchar>(h, w) = Label;    //Out->Content[h][w]=Label;
        //8 connected buren 
        for (int i = -1; i < 2; i++) { //for (i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) { //    for(j=-1; j<2; j++){  
                if (((i != 0) || (j != 0)) && (h + i >= 0) && (h + i < HEIGHT) && (w + j >= 0) && (w + j < WIDTH)) {
                    // if(((i!=0)||(j!=0))&&(h+i>=0)&&          (h+i<HEIGHT)&&(w+j>=0)&&(w+j<WIDTH)){
                       labelPixel(h + i, w + j);              //labelPixel(h + i, w + j);   labelt de aangrenzende pixels.
                }
            }
        }
        return 255; //gelabeld
    }
    return 0; //voldoet niet om gelabeld te worden
}
