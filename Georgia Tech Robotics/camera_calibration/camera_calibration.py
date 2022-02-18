# https://docs.opencv.org/master/dc/dbb/tutorial_py_calibration.html

import numpy as np
import cv2 as cv
import pickle
import time
import argparse
import yaml

    # height, width, number of channels in image
    # height   = img.shape[0]
    # width    = img.shape[1]
    # channels = img.shape[2]
def reduceSize(img, scale_percent=50):
    width  = int(img.shape[1] * scale_percent / 100)
    height = int(img.shape[0] * scale_percent / 100)
    dim = (width, height)
    return cv.resize(img, dim, interpolation=cv.INTER_AREA)


def calibrateCameraFromVideo(vidPath, squareSizeMeters, resizePercent=100, cameraName=None):
    vidPath = vidPath.replace("/", "\\")
    if cameraName is None:
        cameraName = (vidPath.split("\\")[-1]).split(".")[0]
    folderpath = vidPath.replace(vidPath.split("\\")[-1], "")
    # vidPath    = "C:\\Users\\sctma\\OneDrive - Georgia Institute of Technology\\Georgia Tech\\GTSR\\Underwater Platforms\\Python_Code\\underwater_localization_calibration\\camera_calibration\\calibration_image_samples\\pixel4_video_horizontal\\pixel4_horz_cal_3.mp4"
    # After processing:
    # cameraName = pixel4_horz_cal_3
    # folderpath = C:\Users\sctma\OneDrive - Georgia Institute of Technology\Georgia Tech\GTSR\Underwater Platforms\Python_Code\underwater_localization_calibration\camera_calibration\calibration_image_samples\pixel4_video_horizontal\

    start_time = time.time()

    # Termination criteria:
    # Below is the iteration termination criteria. When this criteria is satisfied, algorithm iteration stops.
    # Actually, it should be a tuple of 3 parameters. They are `( type, max_iter, epsilon )`:
    # Type of termination criteria. It has 3 flags as below:
    # cv.TERM_CRITERIA_EPS                             - stop the algorithm iteration if specified accuracy, epsilon, is reached.
    # cv.TERM_CRITERIA_MAX_ITER                        - stop the algorithm after the specified number of iterations, max_iter.
    # cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER - stop the iteration when any of the above condition is met.
    # max_iter - An integer specifying maximum number of iterations.
    # epsilon  - Required accuracy.
    criteria = (cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER, 30, 0.001)

    # prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
    gridsize = (6, 8)
    objp = np.zeros((gridsize[0]*gridsize[1], 3), np.float32)
    objp[:, :2] = np.mgrid[0:gridsize[1], 0:gridsize[0]].T.reshape(-1, 2)
    objp = objp*squareSizeMeters
    print(objp)

    objpoints = []  # 3d points in real world space.
    imgpoints = []  # 2d points in image plane.
    print("Starting Video Calibration (very high resolution images take too long)")
    print("Reading: ", vidPath)

    cap = cv.VideoCapture(vidPath)
    totalImages = cap.get(cv.CAP_PROP_FRAME_COUNT)
    counter = 0
    imagesNotCounted = 0
    delayBetweenImages = 15
    delayCounter = 0
    while(cap.isOpened()):  # Returns true if video capturing has been initialized already.
        if delayCounter > 0:
            cap.grab()  # Grabs the next frame from video file or capturing device.
            imagesNotCounted += 1
            delayCounter -= 1
            continue
        ret, img = cap.read()  # Grabs, decodes and returns the next video frame.
        if(ret == True and counter < 100):
            if(resizePercent != 100):
                img = reduceSize(img, resizePercent)
            gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

            # Find the chess board corners
            # If desired number of corners are found in the image then ret = true
            ret, corners = cv.findChessboardCorners(gray, (gridsize[1], gridsize[0]), None)

            # If found, add object points, image points (after refining them)
            if ret == True:
                delayCounter = delayBetweenImages
                lastSuccessfulImage = img
                objpoints.append(objp)
                corners2 = cv.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)  # This algorithm is used to refine corner coordinates to subpixel accuracy.
                imgpoints.append(corners)
                # Draw and display the corners
                cv.drawChessboardCorners(img, (gridsize[1], gridsize[0]), corners2, ret)
                cv.imshow('img', img)
                cv.waitKey(1)
                counter += 1
            else:
                imagesNotCounted += 1
            print('\n')
            print("Total Images Processed: ", counter+imagesNotCounted)
            print("Successful: ", counter)
            print("Failed: ", imagesNotCounted)
            percentSoFar = (counter+imagesNotCounted)/totalImages*100
            print("Progress: " + str(int(percentSoFar)) + "%")
            print("Est. Time Left (sec): " +
                    str(int(-(time.time()-start_time) + (time.time()-start_time)*100/percentSoFar)))
        else:
            break
    cap.release()
    cv.destroyAllWindows()
    print("\nStarting mtx and dist calcs (takes a few minutes):")
    ret, mtx, dist, rvecs, tvecs = cv.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)
    img = lastSuccessfulImage
    h, w = img.shape[:2]
    newcameramtx, roi = cv.getOptimalNewCameraMatrix(mtx, dist, (w, h), 1, (w, h))
    # undistort
    dst = cv.undistort(img, mtx, dist, None, newcameramtx)
    # crop the image
    x, y, w, h = roi
    dst = dst[y:y+h, x:x+w]
    mean_error = 0

    # Re-projection error gives a good estimation of just how exact the found parameters are. The closer the re-projection error is to zero, the more accurate the
    # parameters we found are. Given the intrinsic, distortion, rotation and translation matrices, we must first transform the object point to image point
    # using cv.projectPoints(). Then, we can calculate the absolute norm between what we got with our transformation and the corner finding algorithm.
    # To find the average error, we calculate the arithmetical mean of the errors calculated for all the calibration images.
    for i in range(len(objpoints)):
        imgpoints2, _ = cv.projectPoints(objpoints[i], rvecs[i], tvecs[i], mtx, dist)
        error = cv.norm(imgpoints[i], imgpoints2, cv.NORM_L2)/len(imgpoints2)
        mean_error += error

    fileDict = {"mtx": mtx,
                "dist": dist,
                "error": mean_error/len(objpoints),
                "resize": resizePercent}

    fileName = str(cameraName) + "_cam_cal_data_"+ str(resizePercent) + "percent"
    cv.imwrite(folderpath + fileName + ".png", dst)
    save_camera_data(folderpath, fileName, fileDict)
    print("Complete, saved to: " + folderpath + fileName)


def save_camera_data(folderpath, fileName, obj):
    with open(folderpath + fileName + '.txt', 'w') as f:
        for key in obj.keys():
            f.write(str(key) + ':')
            f.write(str(obj[key])+'\n')
            print(str(key) + ': ' + str(obj[key])+'\n')
    with open(folderpath + fileName + ".pkl", 'wb') as f:
        pickle.dump(obj, f, pickle.HIGHEST_PROTOCOL)


if __name__ == "__main__":
    # videopath = "C:\\Users\\sctma\\OneDrive - Georgia Institute of Technology\\Georgia Tech\\GTSR\\Underwater Platforms\\Python_Code\\underwater_localization_calibration\\camera_calibration\\calibration_image_samples\\pixel4_video_horizontal\\pixel4_horz_cal_3.mp4"
    # resizePercent = 25
    # calibrateCameraFromVideo(videopath, resizePercent)

    parser = argparse.ArgumentParser(description='This program generates camera calibration data from a video file')
    parser.add_argument("-v", "--video_data_file_path", type=str,   help="Filepath to the input video file", required=True)
    parser.add_argument("-s", "--square_side_meters",   type=float, help="Square side length (meters)",      required=True)
    parser.add_argument("-r", "--resize_percent",       type=int,   help="Resize percent (1-100)",           required=False)
    args = vars(parser.parse_args())

    # guarantee resize percent is between 1-100
    resizePercent = min(max(1, args['resize_percent']), 100)
    calibrateCameraFromVideo(args['video_data_file_path'], args['square_side_meters'], args['resize_percent'])