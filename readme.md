example of serial communication (roughly example.py):  
read the status by sending a newline  
'\n'  
arduino responds with a json string  
'{"analogs":[568,525,483,452,423,406,415,392,372,365,361,348,356,360],"digitals":[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],"outputs":[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]}\n'  
set the outputs low:  
'[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]\n'  
  
the arduino parses the characters  '1', '0', ',', '\n' and '?'. All other characters are ignored.
