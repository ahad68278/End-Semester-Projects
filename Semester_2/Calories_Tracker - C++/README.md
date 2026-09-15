C++ Console Calorie Tracker

A lightweight, object-oriented terminal application designed to help users manage their daily calorie intake, track progress against fitness goals, and maintain basic file persistence across sessions.

Key Features:

Object-Oriented Architecture: Modular design dividing core responsibilities into dedicated classes:
* User Class: Encapsulates state for the daily target, current intake, and historical calorie counts.
* File Class: Handles local I/O operations and tracks persistent storage states.

Data Persistence: Automatically saves active intake data to a local file (calories.txt) and seamlessly reads previous intake sessions into memory upon request.

Real-Time Intake Tracking: Evaluates daily consumed calories against a user-defined goal and displays structured intake progress directly in the terminal.

