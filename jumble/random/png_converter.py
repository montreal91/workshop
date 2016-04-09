
import os, sys
from PIL import Image

for infile in sys.argv[1:]:
    f, e = os.path.splitext( infile )
    outfile = f + ".png"
    if infile != outfile:
        try:
            Image.open(infile).save(outfile)
        except IOError:
            print("Cannot convert")
