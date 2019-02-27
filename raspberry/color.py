import cv2
import numpy as np
import time
from picamera.array import PiRGBArray
from picamera import PiCamera

class Camera:
    def __init__(self):
        self.cam = PiCamera()
        time.sleep(0.1)
    def snapshot(self):
        #read the picture
        self.cam.capture('foo1.jpg',resize=(518,418))
   #img = rawCapture.array

   
        img = cv2.imread('foo1.jpg', 1)
#        cv2.imshow("Image", img)
#        cv2.waitKey(0)

   #convert to HSV image
        hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
   
   #we use yellow color to identify the device
        lower_range = np.array([24, 100, 100], dtype=np.uint8)
        upper_range = np.array([44, 255, 255], dtype=np.uint8)

        mask = cv2.inRange(hsv, lower_range, upper_range)
#   mask = cv2.erode(mask, None, iterations=2)
#   mask = cv2.dilate(mask, None, iterations=2)
#        cv2.imshow("Img1", mask)
#        cv2.waitKey(0)
        cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        cnts = cnts[1]
        center = None

        if len(cnts) > 0:
            c = max(cnts, key=cv2.contourArea)
            ((x,y),radius) = cv2.minEnclosingCircle(c)
            M = cv2.moments(c)
            if M["m00"] == 0:
                return -2,-2
            center = (int(M["m10"]/M["m00"]), int(M["m01"]/M["m00"]))

            if radius > 0:
                cv2.circle(img, (int(x), int(y)), int(radius), (0, 255, 255), 2)
                cv2.circle(img, center, 5, (0,0,255), -1)      
                return int(x), int(y)
                #return x, y
   
        return -1,-1

