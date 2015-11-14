# Program: marker_a4.py
# Proyect: encuadro - Facultad de Ingenier - UDELAR
# Author: Martin Etchart - mrtn.etchart@gmail.com.
#
# Description:
# Python script to render blender model providing pose (rotation, translation), fov
# and image dimensions.
#
# Hosted on:
# http://code.google.com/p/encuadro/
#
# Usage:
# blender -b marker_a4.blend --python "marker_a4.py" -o //<filename> -F JPEG -x 1 -f 1
#
# More info:
# http://code.google.com/p/encuadro/wiki/Rendering


import bpy
import sys
import math

####################################
# OPTIONAL ARGUMENT PARSING WITH LIBRARY. DONT WORK
#
#import argparse
#
#parser = argparse.ArgumentParser(description='Python script to render blender model #providing pose (rotation, translation), fov and image dimensions.')
#
#parser.add_argument('-rot', action="store", dest="r")
#parser.add_argument('-tra', action="store", dest="t")
#parser.add_argument('-fov', action="store", dest="fov", type=float)
####################################

####################################
# OPTIONAL ARGUMENT PARSING BY ME. DONT WORK
#
#i = 4
#while (i<len(sys.argv)):
#       if (sys.argv[i]=="-tra"):
#               i+=1
#               tx = float(sys.argv[i])
#               i+=1
#               ty = float(sys.argv[i])
#               i+=1
#               tz = float(sys.argv[i])
#               print "TRA"    
#       elif (sys.argv[i]=="-rot"):
#               i+=1
#               rx = float(sys.argv[i])
#               i+=1
#               ry = float(sys.argv[i])
#               i+=1
#               rz = float(sys.argv[i])
#               print "ERRE"    
#       elif (sys.argv[i]=="-fov"):
#               i+=1
#               fov = float(sys.argv[i])
#       elif (sys.argv[i]=="-o"):
#               print "OOO"
#               break          
#       i+=1
####################################
print ( sys.argv )

# find the requsted angle
camAngle = None
for ag in sys.argv:
    if ag[:12] == "--cam-angle=":
        camAngle = float ( ag[12:] )
       
if camAngle == None:
    print ( "Cam angle not set" )
    sys.exit(0)
else:
    print ( "Cam angle is " + str( camAngle ) )


pi = 3.1415

scene = bpy.data.scenes["Scene"]
#camera = bpy.data.scenes["Camera"]

# Set render resolution
#scene.render.resolution_x = width
#scene.render.resolution_y = height

# Set camera fov in degrees
#scene.camera.data.angle = fov*(pi/180.0)

# Set camera rotation in euler angles
scene.camera.rotation_mode = 'XYZ'
#scene.camera.rotation_euler[0] = rx*(pi/180.0)
#scene.camera.rotation_euler[1] = ry*(pi/180.0)
# this is the angle
rotationInRad = ( camAngle/180.0) * pi


scene.camera.rotation_euler[2] = rotationInRad


print ( "Initial cam location ( " + str( scene.camera.location.x) + "|" + 
                                    str( scene.camera.location.y) + "|" + 
                                    str( scene.camera.location.z) + ")" )

distanceToCenter = scene.camera.location.y
print ( "Using " + str ( distanceToCenter ) + " as distance to center ")

yPart = math.cos ( - rotationInRad ) * distanceToCenter
xPart = math.sin ( - rotationInRad ) * distanceToCenter


# Set camera translation
scene.camera.location.x = xPart
scene.camera.location.y = yPart
#scene.camera.location.z = tz

print ( "New location (" + str( xPart ) + " | " + str( yPart ) + ")")

