# Demo that can run on any version of Windows
This is a single EXE demo that loads a Windows MetaFile out of a 
resource and displays it along with some text.  It will be improved
later.  When compiled correctly, it can run on any 32-bit version of 
Windows or Windows NT, including Windows 3.1 with the Win32s.

# Creating the Metafile
The metafile must be a proper version.  Windows 3.1 cannot use 
EMF enhanced metafiles - only old WMF metafiles.  And it is picky
about the formatting.  A hacky way to make a satisfactory WMF:

-Open PowerPoint (any version).  Make a new presentation.
-Insert the EMF file into the presentation.
-Copy the EMF file.
-Open ENHMETA.EXE (to get this, google around for ENMETA.EXE - which
  is a self extracting executable that contains the ENHMETA.EXE demo
  and source code)
-Paste the image into ENHMETA.EXE.
-File> Save Regular...
-Save it as a .wmf file.  Use this as a resource.  Windows 3.1 will
  be able to draw it.

# Compiling
To target the Win32s, build using Microsoft Visual C++ 2.0.  (not a joke)

You should be able to simply open the .mak file in Visual C++ 2.0, and
hit build.

Building in the release configuration will yield a smaller file size.

# Thoughts
-It would be nice to compile this with WATCOM as well.
-WMF is the native vector format for Windows, and Microsoft Office, since
  1990. 
-Interestingly, ENHMETA.EXE will run under the Win32s, but it will not
  work, as the Enhanced Metafile functionality does not work under the
  Win32s.  (Windows NT 3.51 can run that program though.)

