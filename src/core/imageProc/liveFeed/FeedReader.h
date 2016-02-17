//
// Created by denis on 06/02/16.
//

#ifndef OBSTACLE_DETECTION_LIVEFEEDERRECORD_H
#define OBSTACLE_DETECTION_LIVEFEEDERRECORD_H

/*
 * This class provides an implementation as a generic class  that
 * can read a blocking image stream. The methods startRecording, stopRecording,
 * and beforeCapture need to be implemented before using this class.
 */
class FeedReader {
public:
    FeedReader(ImageStream *stream) : stream(stream) { }

    virtual void record();


protected:
    virtual void startRecording();
    virtual void stopRecording();
    virtual void beforeCapture();
    virtual void onImageRead(Image16bit image);
private:
    ImageStream *stream;

    bool shouldRecord = true;

};

#endif //OBSTACLE_DETECTION_LIVEFEEDERRECORD_H
