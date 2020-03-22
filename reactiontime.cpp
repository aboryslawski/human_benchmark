#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string.h>
using namespace std;


int main(int, char**)
{
    XColor c;
    Display *d = XOpenDisplay((char *) NULL);
    int x=1500;  // Pixel x 
    int y=540;  // Pixel y
    int desiredColour = 0;
    XImage *image;
    Window root = DefaultRootWindow(d);
    XWarpPointer(d, None, root, 0, 0, 0, 0, x, y);
    XEvent event;
    memset(&event, 0x00, sizeof(event));
    event.type = ButtonPress;
    event.xbutton.button = Button1;
    event.xbutton.same_screen = True;
    XQueryPointer(d, RootWindow(d, DefaultScreen(d)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    event.xbutton.subwindow = event.xbutton.window;
    event.type = ButtonPress;
    
    while (desiredColour != 222){
	    image = XGetImage (d, XRootWindow (d, XDefaultScreen (d)), x, y, 1, 1, AllPlanes, XYPixmap);
	    c.pixel = XGetPixel (image, 0, 0);
	    XFree (image);
	    XQueryColor (d, XDefaultColormap(d, XDefaultScreen (d)), &c);
	    desiredColour = c.green/256;
    }
    XSendEvent(d, PointerWindow, True, 0xfff, &event);
    event.type = ButtonRelease;
    event.xbutton.state = 0x100;
    XSendEvent(d, PointerWindow, True, 0xfff, &event);
    XFlush(d);
    XCloseDisplay(d);

    return 0;
}
