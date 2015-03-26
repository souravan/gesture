Gesture Recognition
===================

An Application written in C++ for windows operating system using OpenCV capable of recognising gestures and
executing the command associated with that gesture.

The video input is fed into the system and then it is converted to HSV. We then use a bright
coloured object ( such that it does not resembels to other colors in the surrounding ) and set up its threshold to track its movement . The path made by the object (gesture) is then matched with the
set of predefined gestures and the associated keystroke is performed.