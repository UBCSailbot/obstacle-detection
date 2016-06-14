//
// Created by denis on 09/06/16.
//

#ifndef OBSTACLE_DETECTION_IMAGESTREAMCAMERADATAADAPTER_H
#define OBSTACLE_DETECTION_IMAGESTREAMCAMERADATAADAPTER_H


#include <io/ImageStream.h>
#include "CameraDataStream.h"

/*
 * This class is meant to provide and interface the new CameraDataStream and the old ImageStream interface
 */
class ImageStreamCameraDataAdapter : public CameraDataStream {
public:
    virtual std::vector<CameraData> nextImage() override;

    virtual bool hasNext() const override;

    ImageStreamCameraDataAdapter(ImageStream *imageStream, bool doubleUp);

    virtual ~ImageStreamCameraDataAdapter();

private:
    ImageStream *_imageStream;

    bool _doubleUp;

};

#endif //OBSTACLE_DETECTION_IMAGESTREAMCAMERADATAADAPTER_H
