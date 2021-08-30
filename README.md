# BATKIT-v1.0
The BATKIT has all arguments that are in BATBOX and also many other new arguments to make console GUI MODE.
BATKIT COMMAND

     BATKIT is an external command that allows using console graphicaly, but 
     not only. It enables also user interractions such as mouse.

     For example, BATKIT allows console cursor position to be changed, change 
     loccally console's colors, or even get user mouse inputs.

SYNOPSIS

         BATKIT [/d Text] [/g X Y] [/c Color] [/m] [/k] [k_] [/a Character] [/w 
      Duration] [/s File] [/o OffsetX OffsetY] [/h Mode] [/p Mode] [/t get title]
      [/cs cursor size] [/n prints new line] [/l Prints length of given string]
       [/ad prints ascii code of character given] [/q Disable or enable quick edit mode]
       [/m[_]  Prints hover info]



     Allows user to manage console.
        - /cs - Change cursor size from 0 to 100. 
        batkit /cs 50 then cursor will be half.
          
        - /q - Enable or disable quick edit mode. 
         for example.
         batkit /q 0 means off the quick edit mode.

         batkit /q 1 means on the quick edit mode.
         
        - /n - Print's a new line.
        
        - /l - Return the length of string
  
        - /ad - Prints the ascii code of characters given.

        - /t Get the title of window and print it.
 
        - /D : Prints text. 

        - /G : Changes cursor position.
          .

        - /C : Changes console's color . 
          

        - /M : Get a user click. 

        - /m_ : - Prints the hover info. 

        - /K[_] : Get a user keystroke.Without blocking or wait.

        - /A : Prints character associated with a code. See BATKIT (/a) (-> 
          ``_BATKIT/ascii'') . 
  

        - /W : Make a delay.


        - /S : Plays a .WAV file. 
         

        - /O : Moves origin of console. This command is usefull to make 
          sprites via BATKIT.

        - /H : Hides or show the console's cursor. 

        - /P : Changes the console's window mode.


NOTES

     You can mix several options on only one BATKIT command line, as shown by 
     ....

     Thus, the following script:

         BATKIT /g 10 10
         BATKIT /d "Hello world"
         BATKIT /g 0 0

     Can be shortened like this:

         BATKIT /g 10 10 /d "Hello world" /g 0 0


LICENSE

     BATKIT is a free software distributed under GNU GENERAL PUBLIC LICENSE 
     VERSION 1.0.

AUTHOR

     BATKIT has been written by SHOAIB HASSAN. The project is no more develloped 
     actually.

