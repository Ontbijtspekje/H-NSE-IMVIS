#include "Parameters.h"
#include "opencv2/highgui.hpp"
#include <opencv2/videoio.hpp>  // Nodig om camera te kunnen gebruiken
#include "Histogram.h"
#include "Contrast.h"
#include "Mirror.h"
#include "Invert.h"
#include "Zoom.h"
#include "Hoogdoorlaat.h"
#include "Smoothing.h"
#include "Mediaan.h"
#include "Threshold.h"
#include "XOR.h"
#include "GatenTeller.h"
#include <iostream>


using namespace cv;
using namespace std;

// Hieronder (na de demo) per opdracht een functie, zie de main() onderaan voor de indeling.

int demo_met_camera() { // -1. Puur voor de demo, met histogram. Deze functie is geen onderdeel van de opdrachten.
    String destination_window = "Camerabeeld";
    Mat frame;
    cout << "Open camera... Onderstaande Debug INFO kun je negeren.\n" << endl;
    VideoCapture capture(0); // open de eerste camera die ik tegenkom (of vul zelf een nr in (>0))
    if (!capture.isOpened())
    {
        cerr << "FOUT: Kan camera capture niet starten. Is camera aangesloten?" << endl;
        return 1;
    }

    capture >> frame; // lees het volgende beeld van de camera
    Histogram histogram("Histogram src", frame);

    cout << "\nCamerabeeld info; breedte: " << capture.get(CAP_PROP_FRAME_WIDTH);
    cout << ", hoogte: " << capture.get(CAP_PROP_FRAME_HEIGHT);
    cout << ", Beelden per seconde: " << capture.get(CAP_PROP_FPS) << endl;
    cout << "Je kunt zelf een plaatje opslaan (zorg zelf in de code dat het pad klopt):" << endl;
    cout << "\tDruk 'g' voor *.pgm (grijswaarden)" << endl;
    cout << "\tDruk 'p' voor *.ppm (kleur)" << endl;
    cout << "\tDruk 'j' voor *.jpg (kleur)" << endl;
    cout << endl << "Om te stoppen: zorg dat een grafisch window geselecteerd is en druk 'ESC' om te stoppen." << endl;
    
    namedWindow(destination_window, WINDOW_AUTOSIZE);
    imshow(destination_window, frame);
    moveWindow(destination_window, 0, 0); // Plaatje naar linksboven verplaatsen
    moveWindow("Histogram src", 89, 513); // Histogram onder plaatje schuiven

    while (1) {
        capture >> frame; // lees het volgende beeld van de camera
        if (frame.empty())
        {
            cerr << "FOUT: Kan geen beelden van camera ontvangen." << endl;
            break;
        }
        else {
            imshow(destination_window, frame); // Dit is het enige dat je nodig hebt. De namedWindow() en moveWindow() hierboven mag je weglaten.
        }
        int key = waitKey(1); // wacht 1 mSec tot toets ingedrukt is. 0 = altijd wachten.
        if (key == 'g') { // *.pgm plaatje opslaan; grijswaarden
            Mat gray_image; 
            cvtColor(frame, gray_image, COLOR_RGB2GRAY); // Converteer (kleuren) bronplaatje naar 8 bits per pixel grijswaarden plaatje.
            vector<int> compression_params;
            compression_params.push_back(IMWRITE_PXM_BINARY); // https://en.wikipedia.org/wiki/Netpbm
            compression_params.push_back(1); // 0 => grijswaarden dus *.pgm, 1 => kleurenplaatje dus *.ppm
            imwrite("C://temp//capture.pgm", gray_image); // de bestandsextensie zegt nu niks over de inhoud dus zorg dat deze klopt
        }
        if (key == 'p') {// *.ppm plaatje opslaan; kleur
            vector<int> compression_params;
            compression_params.push_back(IMWRITE_PXM_BINARY);
            compression_params.push_back(1);
            imwrite("C://temp//capture.ppm", frame);
        }
        if (key == 'j') { // *.jpg plaatje opslaan; kleur
            imwrite("C://temp//capture.jpg", frame); // The function imwrite saves the image to the specified file. The image format is chosen based on the filename extension (see cv::imread for the list of extensions).
        }
        if (key == 27) // ESC toets, dus stoppen
            return 0;
        histogram.update();
    }
    return 0;
}

int lab1_opdracht1a_beeld_spiegelen() { // 1. Spiegelen 
    Mat src, dst;

    String source_window = "Originele plaatje";         // Mag je weglaten, alleen imshow("naam",src) is voldoende. Dit maakt het mooier.
    String destination_window = "Horizontaal gespiegeld"; //horizontaal ipv verticaal

    /* Hieronder: plaatje inlezen met imread(). De paden moet er zo uitzien: "C://mijnMap//subMap//bestand.pgm"
    Vergeet de optie IMREAD_GRAYSCALE niet als je een grijswaardenplaatje inleest.
    Met IMREAD_GRAYSCALE krijg je 1 byte per pixel, als je het vergeet krijg je 3 bytes per pixel en dan zie je maar 1/3 van je bronplaatje terug!! */

    src = imread("C://Users//ybdol//Desktop//IMVIS//lab1//file1.pgm", IMREAD_GRAYSCALE);
    namedWindow(source_window, WINDOW_AUTOSIZE); // Mag je weglaten, alleen imshow("naam",src) is voldoende.
    imshow(source_window, src); // Originele plaatje laten zien.

    int HEIGHT = src.rows;
    int WIDTH = src.cols;
    int temp = 0;

    dst = Mat::ones(HEIGHT, WIDTH, CV_8U) * 0;   // Maak een nieuw plaatje van hetzelfde type als src, gevuld met 1 * 0 (dus nullen, dus zwart)
    
    Mirror spiegel(src, dst);
    spiegel.process();

    namedWindow(destination_window, WINDOW_AUTOSIZE); // Mag je weglaten, alleen imshow("naam",src) is voldoende.
    imshow(destination_window, dst); // Bestemmingsplaatje laten zien.

    // Plaatjes netjes positioneren (mag je weglaten, alleen imshow() is voldoende)
    moveWindow(source_window, 0, 0); // Plaatje naar linksboven verplaatsen
    moveWindow(destination_window, WIDTH, 0); // Plaatje rechts naast de andere plaatsen

    waitKey(0); // Wachten tot een toets gedrukt wordt...
    return 0;
}

int lab1_opdracht1b_grijswaarden_inverteren() { // 2. Zwart en wit tinten inverteren
    Mat src, dst;

    String source_window = "Originele plaatje";        
    String destination_window = "Geinventeerd plaatje"; 

    src = imread("C://Users//ybdol//Desktop//IMVIS//lab1//file1.pgm", IMREAD_GRAYSCALE);
    namedWindow(source_window, WINDOW_AUTOSIZE); 
    imshow(source_window, src); 

    int HEIGHT = src.rows;
    int WIDTH = src.cols;
    int temp = 0;

    dst = Mat::ones(HEIGHT, WIDTH, CV_8U) * 0;   

    Invert inventeer(src, dst);
    inventeer.process();

    namedWindow(destination_window, WINDOW_AUTOSIZE); 
    imshow(destination_window, dst); 

    moveWindow(source_window, 0, 0); 
    moveWindow(destination_window, WIDTH, 0);

    waitKey(0); // Wachten tot een toets gedrukt wordt...
    return 0;
}

int lab1_opdracht2_contrast_stretch() { // 3. Contrast aanpassen

    Mat src, dst;

    String source_window = "Originele plaatje";
    String destination_window = "Verbeterd contrast";

    src = imread("C://Users//ybdol//Desktop//IMVIS//lab1//donker.pgm", IMREAD_GRAYSCALE);
    namedWindow(source_window, WINDOW_AUTOSIZE);
    imshow(source_window, src);

    int HEIGHT = src.rows;
    int WIDTH = src.cols;
    int temp = 0;
    Histogram histo( "grijswaarde", src);

    dst = Mat::ones(HEIGHT, WIDTH, CV_8U) * 0;

    Contrast contrast(src, dst);
    contrast.process();

    namedWindow(destination_window, WINDOW_AUTOSIZE);
    imshow(destination_window, dst);

    moveWindow(source_window, 0, 0);
    moveWindow(destination_window, WIDTH, 0);
    
     Histogram histo2("grijswaarde2", dst);

    while (1) {
        int key = waitKey(1); //wacht voor 1 ms anders crasht het programma
        if (key == 27) { // als esc, dan sluit het programma af   
            return 0;
        }
        histo.update(); //update de histogram waardes
        histo2.update();
    }
}

int lab2_opdracht2_zoomen() { // 4. Zoomen
    Mat src, dst;

    String source_window = "Originele plaatje";
    String destination_window = "Gezoomed plaatje";

    src = imread("C://Users//ybdol//Desktop//IMVIS//lab2//rijswijk.jpg", IMREAD_GRAYSCALE);
    namedWindow(source_window, WINDOW_AUTOSIZE);
    imshow(source_window, src);

    int HEIGHT = src.rows;
    int WIDTH = src.cols;
    int temp = 0;

    dst = Mat::ones(HEIGHT, WIDTH, CV_8U) * 0;

    Zoom zoom(src, dst);
    zoom.process(2);                // onder 1 voor uitzoomen, boven 1 om in te zoomen bv 0.5 zoom out 2 zoom in

    int zoomHEIGHT = dst.rows;
    int zoomWIDTH = dst.cols;


    namedWindow(destination_window, WINDOW_AUTOSIZE);
    cv::resizeWindow(destination_window, 640, 480);
    imshow(destination_window, dst);

    moveWindow(source_window, 0, 0);
    moveWindow(destination_window, WIDTH, 0);

    waitKey(0); // Wachten tot een toets gedrukt wordt...
    return 0;
}

int lab2_opdracht2b_roteren() { // 5. Roteren
    return 0;
}

int lab2_opdracht3_affien_mysterie() { // 6. Mysterieuze affiene transformatie
    return 0;
}

int lab3_opdracht1_hoogdoorlaat() { // 7. Hoogdoorlaat filter
    Mat src, dst;

    String source_window = "Originele plaatje";         
    String destination_window = "Hoogdoorlaat"; 

    src = imread("C://Users//ybdol//Desktop//IMVIS//lab3//joint.jpg", IMREAD_GRAYSCALE);
    imshow(source_window, src); // Originele plaatje laten zien.

    int HEIGHT = src.rows;
    int WIDTH = src.cols;
    int temp = 0;

    dst = Mat::ones(HEIGHT, WIDTH, CV_8U) * 0;   // Maak een nieuw plaatje van hetzelfde type als src, gevuld met 1 * 0 (dus nullen, dus zwart)

    Hoogdoorlaat filter(src, dst);
    filter.process();

    imshow(destination_window, dst); // Bestemmingsplaatje laten zien.

    moveWindow(source_window, 0, 0); // Plaatje naar linksboven verplaatsen
    moveWindow(destination_window, WIDTH, 0); // Plaatje rechts naast de andere plaatsen

    waitKey(0); // Wachten tot een toets gedrukt wordt...
    return 0;
}


int lab3_opdracht2a_laagdoorlaat() { // 8. Laagdoorlaat filter
    
    return 0;
}

int lab3_opdracht2b_mediaan() {
    Mat src, dst_mediaan, dst_smooth;
    String source_window = "Originele plaatje";
    String destination_window = "Mediaan";
    String smoothfilter_window = "Smoothfilter";

    src = imread("C://Users//ybdol//Desktop//IMVIS//lab3//whalesp.jpg", IMREAD_GRAYSCALE);
    imshow(source_window, src); // Originele plaatje laten zien.

    int HEIGHT = src.rows;
    int WIDTH = src.cols;

    dst_mediaan = Mat::ones(HEIGHT, WIDTH, CV_8U) * 0;
    dst_smooth = Mat::ones(HEIGHT, WIDTH, CV_8U) * 0;

    Mediaan mediaan_filter(src, dst_mediaan);
    mediaan_filter.process();

    imshow(destination_window, dst_mediaan); // Bestemmingsplaatje laten zien.

    // Smooth filter
    Smoothing smooth_filter(src, dst_smooth);
    smooth_filter.process();

    imshow(smoothfilter_window, dst_smooth); // Smoothfilter plaatje laten zien

    moveWindow(source_window, 0, 0); // Plaatje naar linksboven verplaatsen
    moveWindow(destination_window, WIDTH, 0); // Plaatje rechts naast de andere plaatsen
    moveWindow(smoothfilter_window, WIDTH, HEIGHT + 50); // Smoothfilter plaatje onder de bestemmingsplaatje plaatsen

    waitKey(0); // Wachten tot een toets gedrukt wordt...

    return 0;
}



int lab4_opdracht3_mieren() { // 10. Mier(en)

    /*
   1.gevonden mier opgeslagen in map imvis op bureaublad, threshold en calculator gebruikt
   2. drempelwaarde 100, mieren goed zichtbaar
        thresholding, xor in calculator,despeckle
    
    */

    //------------------------------------------------------------------ants1
    int thresholdValue;
    cout << "wat is de drempelwaarde? ";
    cin >> thresholdValue;
    
    Mat src, dst;

    String source_window = "Originele plaatje";
    String destination_window = "binary";

    src = imread("C://Users//ybdol//Desktop//IMVIS//lab4//ants1.pgm", IMREAD_GRAYSCALE);
    imshow(source_window, src); // Originele plaatje laten zien.

    int HEIGHT = src.rows;
    int WIDTH = src.cols;
    int temp = 0;

    dst = Mat::ones(HEIGHT, WIDTH, CV_8U) * 0;   // Maak een nieuw plaatje van hetzelfde type als src, gevuld met 1 * 0 (dus nullen, dus zwart)
    
    Threshold thres(src, dst);
    thres.process(thresholdValue);

    imshow(destination_window, dst); // Bestemmingsplaatje laten zien.

    moveWindow(source_window, 0, 0); // Plaatje naar linksboven verplaatsen
    moveWindow(destination_window, WIDTH, 0); // Plaatje rechts naast de andere plaatsen

    //------------------------------------------------------------------ ants2

    Mat src2, dst2;

    String source2_window = "Originele plaatje 2";
    String destination2_window = "binary2";

    src2 = imread("C://Users//ybdol//Desktop//IMVIS//lab4//ants2.pgm", IMREAD_GRAYSCALE);
    imshow(source2_window, src2); // Originele plaatje laten zien.
    
    int HEIGHT2 = src2.rows;
    int WIDTH2 = src2.cols;
    int temp2 = 0;

    dst2 = Mat::ones(HEIGHT2, WIDTH2, CV_8U) * 0;   // Maak een nieuw plaatje van hetzelfde type als src, gevuld met 1 * 0 (dus nullen, dus zwart)

    Threshold thres2(src2, dst2);
    thres2.process(thresholdValue);

    imshow(destination2_window, dst2); // Bestemmingsplaatje laten zien.
    //------------------------------------------------------------ XOR

    Mat xor_dst;
    string xor_window = "xor";
    xor_dst = Mat::ones(HEIGHT2, WIDTH2, CV_8U) * 0; 
    XOR verschil(dst, dst2, xor_dst);
    verschil.process();

    imshow(xor_window, xor_dst); // Bestemmingsplaatje laten zien.


    waitKey(0); // Wachten tot een toets gedrukt wordt...
    return 0;
 
}

int lab5_opdracht1_gaten_tellen() { // 11. Gaten tellen1

    Mat src, dst;

    String source_window = "Originele plaatje";
   
    src = imread("C://Users//ybdol//Desktop//IMVIS//lab5//chassis1.pgm", IMREAD_GRAYSCALE);
    imshow(source_window, src); // Originele plaatje laten zien.

    int HEIGHT = src.rows;
    int WIDTH = src.cols;
    int temp = 0;

    GatenTeller gatenTeller(src);
    gatenTeller.tellen();
    //cout << "Hoeveelheid gaten = " << aantalGaten << endl;

    moveWindow(source_window, 0, 0); // Plaatje naar linksboven verplaatsen
    //moveWindow(destination_window, WIDTH, 0); // Plaatje rechts naast de andere plaatsen

    waitKey(0); // Wachten tot een toets gedrukt wordt...
    return 0;
}

int lab5_opdracht2_labellen() { // 12. Gaten tellen2 - verbeterd
    Mat src, dst;

    String source_window = "Originele plaatje";
   
    src = imread("C://Users//ybdol//Desktop//IMVIS//lab5//chassis2.pgm", IMREAD_GRAYSCALE);
    imshow(source_window, src); // Originele plaatje laten zien.

    int HEIGHT = src.rows;
    int WIDTH = src.cols;
    int temp = 0;
    dst = Mat::ones(HEIGHT, WIDTH, CV_8U) * 0;

    GatenTeller gatenTeller(src);
 
    int gaten2 = gatenTeller.process(); 
    cout << "Hoeveelheid gaten: " << gaten2 << endl;

    moveWindow(source_window, 0, 0); // Plaatje naar linksboven verplaatsen

    waitKey(0); // Wachten tot een toets gedrukt wordt...
    return 0;
}

int main(int argc, const char** argv){

    int optie, ret;
    do {
        system("Color 0A"); // groene tekst (A) op zwarte achtergrond (0)
        //system("Color %"); // laat alle mogelijke kleuren zien
        cout << "H-NSE-IMVIS   -   Maak een keuze (geef nummer + druk Enter)" << endl;
        cout << "-1: Demo met camera en histogram" << endl;
        cout << " 1: Lab 1 Opdracht 1a - Spiegelen" << endl;
        cout << " 2: Lab 1 Opdracht 1b - Inverteren" << endl;
        cout << " 3: Lab 1 Opdracht 2  - Contrast aanpassen" << endl;
        cout << " 4: Lab 2 Opdracht 2  - Affien: Zoomen" << endl;
        cout << " 5: Lab 2 Opdracht 2b - Affien: Roteren" << endl;
        cout << " 6: Lab 2 Opdracht 3  - Mysterieuze affiene transformatie - LET OP! : TOETSVRAGEN!" << endl;
        cout << " 7: Lab 3 Opdracht 1  - Hoogdoorlaat filter" << endl;
        cout << " 8: Lab 3 Opdracht 2a - Laagdoorlaat filter" << endl;
        cout << " 9: Lab 3 Opdracht 2b - Mediaan filter" << endl;
        cout << "10: Lab 4 Opdracht 3  - Mier(en)" << endl;
        cout << "11: Lab 5 Opdracht 1  - Gaten tellen1" << endl;
        cout << "12: Lab 5 Opdracht 2  - Gaten tellen2 - verbeterd" << endl;
        cout << endl << "Maak een keuze (0 = stoppen): ";
        cin >> optie;

        switch (optie) {
        case -1: ret = demo_met_camera(); break;
        case 0: ret = 0; break;
        case 1: ret = lab1_opdracht1a_beeld_spiegelen(); break;
        case 2: ret = lab1_opdracht1b_grijswaarden_inverteren(); break;
        case 3: ret = lab1_opdracht2_contrast_stretch(); break;
        case 4: ret = lab2_opdracht2_zoomen(); break;
        case 5: ret = lab2_opdracht2b_roteren(); break;
        case 6: ret = lab2_opdracht3_affien_mysterie(); break;
        case 7: ret = lab3_opdracht1_hoogdoorlaat(); break;
        case 8: ret = lab3_opdracht2a_laagdoorlaat(); break;
        case 9: ret = lab3_opdracht2b_mediaan(); break;
        case 10: ret = lab4_opdracht3_mieren(); break;
        case 11: ret = lab5_opdracht1_gaten_tellen(); break;
        case 12: ret = lab5_opdracht2_labellen(); break;
        }

        if (ret != 0) return ret;
        destroyAllWindows();    // Alle openstaande imshow() vensters sluiten
    } while (optie != 0);
    return 0;
}

