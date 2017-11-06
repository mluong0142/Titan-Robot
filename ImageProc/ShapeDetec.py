#!/usr/bin/python

import numpy as np
import cv2
import os
import errno


cam = cv2.VideoCapture(1)
_,im = cam.read() # captures image
cv2.imwrite("triangle1.png",im) # writes image test.bmp to disk


img = cv2.imread('/home/avinash/ImagePackage/triangle1.png')#import the image
blurred = cv2.pyrMeanShiftFiltering(img,31,91)# gets rid of noise
gray = cv2.cvtColor(blurred,cv2.COLOR_BGR2GRAY)#changes the image to grayscale
ret,thresh = cv2.threshold(gray,0,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)# Takes the image and makes it black and white


cv2.imwrite("Test.png",thresh)#write the fitered image out
_,contours,_ = cv2.findContours(thresh,cv2.RETR_LIST,cv2.CHAIN_APPROX_NONE)
epsilon = 0.1 * cv2.arcLength(contours[0], True)
approx = cv2.approxPolyDP(contours[0], epsilon, True)
edges = len(approx)#calculate the number of edges
WritePath = "/home/avinash/ImagePackage/shape"
try:
    fifo=os.open(WritePath,os.O_WRONLY)
except OSError, e:
    print "cannot open fifo" % e
else:
    os.write(fifo,str(edges))
    os.close(fifo)












        




