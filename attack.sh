echo "compile code"

gcc -o dnsdosAttack attack.c

echo "compiled"

echo "send rqquest to 10.0.2.6 dns server"

sudo ./dnsdosAttack www.buet.ac.bd 10.0.2.6

echo "sending request"