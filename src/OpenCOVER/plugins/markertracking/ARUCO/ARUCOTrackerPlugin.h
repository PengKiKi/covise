/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

#ifndef _ARUCO_PLUGIN_H
#define _ARUCO_PLUGIN_H
/****************************************************************************\ 
**                                                            (C)2001 HLRS  **
**                                                                          **
** Description: ARUCO Plugin                                                **
**                                                                          **
**                                                                          **
** Author: U.Woessner		                                                **
**                                                                          **
** History:  								                                **
** Mar-16  v1	    				       		                            **
**                                                                          **
**                                                                          **
\****************************************************************************/
#include <cover/coVRPluginSupport.h>
#include <cover/coVRCollaboration.h>
#include <cover/ARToolKit.h>
#include <cover/coTabletUI.h>
#include <cover/coVRPlugin.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/aruco.hpp>

using namespace covise;
using namespace opencover;

class ARUCOPlugin : public coVRPlugin, public ARToolKitInterface, public coTUIListener
{
public:
    ARUCOPlugin();
    virtual ~ARUCOPlugin();

    // this will be called in PreFrame
    virtual bool init();
    virtual void preFrame();

private:
    coTUIToggleButton *arDebugButton;
    coTUIButton *arSettingsButton;
    coTUIToggleButton *calibrateButton;
    coTUIToggleButton *visualizeButton;
    coTUIToggleButton *detectAdditional;
    coTUIToggleButton *useSFM;

    coTUILabel *calibrateLabel;
    bool doCalibrate;
    bool calibrated;
    int calibCount;

    coTUISlider *bitrateSlider;

    //void captureRightVideo();
    int msgQueue;
    unsigned char *dataPtr;
    int xsize, ysize;
    int thresh;
    int marker_num;
    bool flipBufferH;
    bool flipBufferV;
    //ARMarkerInfo    *markerInfo;
    osg::Matrix OpenGLToOSGMatrix;
    osg::Matrix OSGToOpenGLMatrix;
    
    std::vector< int > ids;
    std::vector< std::vector< cv::Point2f > > corners, rejected;
    std::vector< cv::Vec3d > rvecs, tvecs;

    void adjustScreen();
    virtual void tabletEvent(coTUIElement *tUIItem);
    virtual void tabletPressEvent(coTUIElement *tUIItem);
    virtual int loadPattern(const char *);
    virtual osg::Matrix getMat(int pattID, double pattCenter[2], double pattSize, double pattTrans[3][4]);
    virtual bool isVisible(int);
    virtual void updateMarkerParams();
    std::string calibrationFilename;
    cv::VideoCapture inputVideo;
    
    cv::Ptr<cv::aruco::Dictionary> dictionary;
    cv::Ptr<cv::aruco::DetectorParameters> detectorParams;
    cv::Mat camMatrix;
    cv::Mat distCoeffs;
    cv::Mat image;
    cv::Mat imageCopy;
    float markerLength;


private:
    coVRCollaboration::SyncMode syncmode;
    
void estimatePoseSingleMarker(cv::InputArrayOfArrays _corners,
                               cv::InputArray _cameraMatrix, cv::InputArray _distCoeffs,
                               cv::OutputArrayOfArrays _rvecs, cv::OutputArrayOfArrays _tvecs);
};
#endif
