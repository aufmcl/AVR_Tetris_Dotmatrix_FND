# Tetris_Dotmatrix_FND
 With joysticks, it controls the blocks seen in the dot matrix, and shows scores on Windows.


## Preparation
 1. Install the Fritzing program. (Required to open Circuit_diagram.fzz)
 2. Construct the circuit by referring to the Circuit_diagram.fzz file on the aduino UNO board.
 3. Upload the Tetris_Dotmatrix_LCD.ino file.
 4. Run Tetris_ScoreBoard.exe located in the path "Tetris_Dotmatrix\Tetris_ScoreBoard_WPF\bin".
 5. Set Baud rate to 9600, select Aduino COM port.
 6. Press the reset button on the Aduino board to start the game.
 
## How to play
* Control the falling block through the joystick.
  * Right : Move Block One Right-way to the right
  * Left: One block to the left
  * Down: Move the block down one block
  * Up: Rotate Block Right
* The line disappears when the block is filled by six dots.
* Game over when the block fills up to the top


### H/W
* Board : Arduino UNO, Bread borad
* MCU : Atemga 328 in Arduino UNO
* Dot matrix : 10888BS
* Joystick : HW-504
* Charater LCD : 2 * 16 Character LCD with I2C Module
