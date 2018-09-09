#include "qmlapplication.h"

int main(int argc, char **argv) {

    auto app = new QmlApplication(argc, argv);
    return app->exec();
}
