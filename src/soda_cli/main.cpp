#include <QCoreApplication>
#include <string>
#include <opencv2/highgui.hpp>

#include "framegrabber.hpp"

using namespace soda;

int main(int argc, char **argv) {

    QCoreApplication app(argc, argv);

    app.addLibraryPath(QCoreApplication::applicationDirPath() + "/../lib");

    auto framegrabber = new FrameGrabber();
    framegrabber->open(0);
//    framegrabber->start();

    std::string winname;
    cv::namedWindow(winname);
    Image currentImage;
    Image displayImage;
    while(true){
        app.sendPostedEvents();
        framegrabber->get_image(currentImage);
        if(!currentImage.is_empty())
        {
            currentImage.bgr_to_rgb(displayImage);
            currentImage.show_in(winname);
            cv::waitKey(1);
        }
    }

    return 0;
}
