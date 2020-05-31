#ifndef SYSTEMSTRUCTURE_HPP
#define SYSTEMSTRUCTURE_HPP

#include "common_headers.hpp"
#include "definitions.hpp"

#include "DetectionSys.hpp"
#include "FrameRate.hpp"
#include "CameraSys.hpp"
#include "RecognitionSys.hpp"
#include "DataIO.hpp"
#include "UserInterface.hpp"

class SystemStructure
{
    public:
        DetectionSys* det;
        RecognitionSys* rec;
        CameraSys* cam;
        DataIO* data;
        UserInterface* interface;

        SystemStructure();
        ~SystemStructure();

};

#endif
