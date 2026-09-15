C++ Command-Line Chess Game

A lightweight, terminal-based implementation of Chess built purely on procedural C++ fundamentals without relying on Object-Oriented Programming (OOP) concepts. Developed using simple 2D arrays, functions, control structures, and basic input parsing, this project provides a functional two-player local chess experience directly within an interactive 8x8 ASCII board.

Key Features:

Pure Basics (Non-OOP): Structured entirely using functional decomposition, pass-by-reference logic, and raw 2D arrays (board[8][8]) without classes or dynamic memory allocation.

Interactive ASCII Board: Custom terminal rendering that draws column labels (a–h), row numbers (1–8), and cell borders cleanly.

Algebraic Coordinate Input: Accepts user moves via terminal coordinates (e.g., E 2 E 4) and handles index conversion into zero-indexed array coordinates.

Piece Rules & Collision Checking: Dedicated validation logic for Pawns, Rooks, Knights, Bishops, Queens, and Kings:
* Path Blocking: Ensures non-jumping pieces (Rooks, Bishops, Queens) cannot pass through occupied tiles.
* Pawn Mechanics: Includes single-step forwards, double-step initial pushes, and diagonal capturing rules.
* Ownership Tracking: Uses uppercase letters for Black pieces and lowercase letters for White pieces to regulate turn validity and prevent friendly fire.

Turn Management & Win Detection: Alternates player turns automatically and scans board state after every valid move, ending the game immediately when a King (K / k) is captured.
