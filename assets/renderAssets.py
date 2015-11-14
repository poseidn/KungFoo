import shutil
import os
import sys
import shutil

modelsPath = "models/"
tmpPath = "tmpout/"
finalPath = "../ingame_assets/images/"

blenderBin = "~/apps/blender/blender"


def isNameInWildcard (wildcard, name):
    return name.startswith (wildcard)

def renderStatic (staticConfigList, wildcard):
    
    for staticConfig in staticConfigList:
        name = staticConfig[0]
        if not isNameInWildcard(wildcard, name):
            continue
        
        filename = name + ".blend"
        finalFileName = finalPath + name + ".png"
        
        bldrCommand = blenderBin + " --background " + modelsPath + filename + \
                  " --render-output " + tmpPath + name + " --render-frame 0"
        print ( "Running " + bldrCommand )
        os.system (bldrCommand)
        
        shutil.move(tmpPath + name + "0000.png" , finalFileName)

def renderModel (modelConfig, wildcard):
    name = modelConfig[0]
    if not isNameInWildcard(wildcard, name):
        return
    
    filename = modelConfig[1]
    poses = modelConfig[2]
    
    print ( "Rendering model " + name + " from filename " + filename )
    print ( " -> Doing " + str(len (poses)) + " poses" )
    
    # clear tmp folder
    os.system ("rm -f " + tmpPath + "*")
    
    # add up the needed frames
    # maxFrames = 0
    # for p in poses:
        #    maxFrames = reduce(lambda x, y: x[1]+y[1], poses, 0)
    #    maxFrames += p[1]
    # print " -> Rendering " + str(maxFrames) + " frames"
    
    
    # curFrame = 1
    
    for pose in poses:
        fileNameList = []
        poseName = pose[0]
        poseStartFrames = pose[1]
        poseFrames = pose[2]
        poseCameraLocations = pose[3]
        
        #        finalFileNameTmp = tmpPath
        
        for location in poseCameraLocations:        
            if len(poseCameraLocations) > 1 :
                locationName = tmpPath + name + str(location)
                finalFileName = finalPath + name + "_" + poseName + "_" + str(location) + ".png"
            else:
                # no came locations neede
                locationName = tmpPath + name
                finalFileName = finalPath + name + "_" + poseName + ".png"
            print ( "Rendering to " + locationName )
        
            # run blender and render everything in one go
            bldrCommand = blenderBin + " --background " + modelsPath + filename + \
                          " --python placeCam.py " + \
                          " --render-output " + tmpPath + name + " --frame-start " + str(poseStartFrames) + \
                          " --frame-end " + str(poseStartFrames + poseFrames - 1) + \
                          " --render-anim --render-format PNG" + \
                          " --verbose 0 -- --cam-angle=" + str(location)
            os.system (bldrCommand)
            print (bldrCommand)
            picNum = poseStartFrames
            fileNameList = []
            for fr in range (0, poseFrames):                
                fileNameList += [ tmpPath + name + ("%04d" % picNum) + ".png" ]
                picNum += 1
                
           
            print ( "Stiching images " + str (fileNameList) + " to " + finalFileName )
            # curFrame += poseFrames
        
            # montage player10001.png player10002.png -tile x10x1 -geometry +0+0 out.png
            mntgCommand = "montage " + reduce(lambda x, y: x + " " + y , fileNameList) + \
                            " -background none -tile x20x1 -geometry +0+0 " + finalFileName
            os.system (mntgCommand)
#    for 

#wildcard = ["player, enemy"
wildcard = ""

staticItems = [["wall_wood_front1"], ["wall_wood_side1"]]

renderStatic(staticItems, wildcard)
# sys.exit(0)
# looking up is 0, then clockwise, 1,2,3,..,7

playerFrameCount = 8
playerOneFrame = 1

defaultCameraLocations = range (0, 360, 45)
# defaultCameraLocations = [0,45]

for playerNum in range(1,5):
    playerRender = ("player" + str(playerNum), "player" + str(playerNum) + ".blend",
                    [   ("walk", 8, playerFrameCount, defaultCameraLocations),
                        ("stand", 0, playerFrameCount, defaultCameraLocations),
                        ("kick", 18, playerFrameCount, defaultCameraLocations),
                        ("jump", 30, playerFrameCount, defaultCameraLocations),
                        ("biking", 40, playerFrameCount, defaultCameraLocations)
                                    ])
    #renderModel(playerRender, wildcard)


enemy1Render = ("enemy1", "enemy1.blend",
                [   ("walk", 8, playerFrameCount, defaultCameraLocations),
                    ("stand", 0, playerFrameCount, defaultCameraLocations),
                    ("kick", 18, playerFrameCount, defaultCameraLocations),
                    ("jump", 30, playerFrameCount, defaultCameraLocations),
                    ("hit", 40, playerFrameCount, defaultCameraLocations),
                    ("dead", 50, playerOneFrame, defaultCameraLocations)
                                ])                                

#renderModel( enemy1Render, wildcard )

enemy2Render = ("enemy2", "enemy2.blend",
                [   ("walk", 8, playerFrameCount, defaultCameraLocations),
                    ("stand", 0, playerFrameCount, defaultCameraLocations),
                    ("kick", 18, playerFrameCount, defaultCameraLocations),
                    ("jump", 30, playerFrameCount, defaultCameraLocations),
                    ("hit", 40, playerFrameCount, defaultCameraLocations),
                    ("dead", 50, playerOneFrame, defaultCameraLocations)
                                ])

renderModel( enemy2Render, wildcard )

