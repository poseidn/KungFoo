# -*- coding: utf-8 -*-
import cairo
import pango
import pangocairo
import sys

font_map = pangocairo.cairo_font_map_get_default()
families = font_map.list_families()

for f in font_map.list_families():
    with open("cairo_text_" + f.get_name() + ".png", "wb") as image_file:
        surf = cairo.ImageSurface(cairo.FORMAT_ARGB32, 320, 120)
        context = cairo.Context(surf)
        
        #draw a background rectangle:
        context.rectangle(0,0,320,120)
        context.set_source_rgb(1, 1, 1)
        context.fill()
        
        #get font families:
        

        
        # to see family names:
        #for f in font_map.list_families():
        #    print f.get_name()
        
        #context.set_antialias(cairo.ANTIALIAS_SUBPIXEL)
        
        # Positions drawing origin so that the text desired top-let corner is at 0,0
        context.translate(50,25)
        
        pangocairo_context = pangocairo.CairoContext(context)
        pangocairo_context.set_antialias(cairo.ANTIALIAS_SUBPIXEL)
        

        layout = pangocairo_context.create_layout()
        fontname = f.get_name()
        font = pango.FontDescription(fontname + " 25")
        layout.set_font_description(font)
        
        layout.set_text(u"Travis L.")
        context.set_source_rgb(0, 0, 0)
        pangocairo_context.update_layout(layout)
        pangocairo_context.show_layout(layout)        
        surf.write_to_png(image_file)

   