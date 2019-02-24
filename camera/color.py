import cv2
import numpy as np
import serial

def mapObjectPosition(x,y):
   print("Object center coordinates at X = {0}, Y = {1}".format(x,y))
   


def main():
   ser = serial.Serial(
              
        port='/dev/serial0',
        baudrate = 115200,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
   )

   #read the picture - 1 means we want the image in BGR
   img = cv2.imread('image.jpg', 1)

   #resize the image to 20% in each axis
   img = cv2.resize(img, (0,0), fx=0.2, fy=0.2)

   #convert to HSV image
   hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

   blue = 0
   green = 0
   red = 255

   color = np.uint8([[[blue, green, red]]])
   hsv_color = cv2.cvtColor(color, cv2.COLOR_BGR2HSV)
   #hue = hsv_color[0][0][0]
   #print(str(hue-10))
   #print(str(hue+10))

   lower_range = np.array([24, 100, 100], dtype=np.uint8)
   upper_range = np.array([44, 255, 255], dtype=np.uint8)

   mask = cv2.inRange(hsv, lower_range, upper_range)
#   mask = cv2.erode(mask, None, iterations=2)
#   mask = cv2.dilate(mask, None, iterations=2)

   cv2.imshow("img", mask)
   cv2.waitKey(0)

   cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
   cnts = cnts[1]
   center = None

   if len(cnts) > 0:
      c = max(cnts, key=cv2.contourArea)
      ((x,y),radius) = cv2.minEnclosingCircle(c)
      M = cv2.moments(c)
      center = (int(M["m10"]/M["m00"]), int(M["m01"]/M["m00"]))

      if radius > 2:
        cv2.circle(img, (int(x), int(y)), int(radius), (0, 255, 255), 2)
        cv2.circle(img, center, 5, (0,0,255), -1)

        mapObjectPosition(int(x), int(y))
        ser.write(str.encode('X = %d'%(x)))

   cv2.imshow("img", img)
   
   while(1):
    k = cv2.waitKey(0)
    if(k==27):
      break

   cv2.destroyAllWindows()


if __name__ == '__main__':
    main()