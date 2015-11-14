# -*- coding: utf-8 -*-
import cairo
import pango
import pangocairo
import sys

## use liberation mono

font_map = pangocairo.cairo_font_map_get_default()
families = font_map.list_families()

oversamplingFactor = 4
# percent 15
borderSpacing = 0.15

outWidth = 512 * oversamplingFactor
outHeight = 512 * oversamplingFactor

colCount = 16
rowCount = 16

# percent
shiftY = -0.1
sizeX = outWidth / colCount
sizeY = outHeight / rowCount

surf = cairo.ImageSurface(cairo.FORMAT_ARGB32, outWidth, outHeight)
context = cairo.Context(surf)

#draw a background rectangle:
#context.rectangle(0,0,outWidth,outHeight)
#context.set_source_rgb(1, 1, 1)
#context.fill()

fontname = "Liberation Mono"


for iChar in range ( 0, 255):

    pangocairo_context = pangocairo.CairoContext(context)
    pangocairo_context.set_antialias(cairo.ANTIALIAS_SUBPIXEL)

    layout = pangocairo_context.create_layout()
    font = pango.FontDescription(fontname + " " + str( 25 * oversamplingFactor * ( 1 - borderSpacing )))
    layout.set_font_description(font)
    
    context.save()
    
    spacingX = sizeX * borderSpacing
    spacingY = sizeY * borderSpacing + sizeY * shiftY
    
    context.translate( ( iChar % colCount ) * sizeX + spacingX, ( iChar / colCount ) * sizeY + spacingY )
    layout.set_text( chr(iChar) )
    context.set_source_rgb(0, 0, 0)
    
    pangocairo_context.update_layout(layout)
    pangocairo_context.show_layout(layout)        
    
    context.restore()
    
    #pass

with open("textChars.png", "wb") as image_file:
    surf.write_to_png(image_file)


   