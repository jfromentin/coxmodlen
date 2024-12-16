import sys
import os

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print("Usage : python generate.py t n k h ")
        print("where : ")
        print(" - t is A, B or D: type of the Coxeter group")
        print(" - n is in [2, 20]: rank of the Coxeter group")
        print(" - k is in [2, 10]: the modulus")
        print(" - h is in [0, k -1]: the remainder")
        exit(0)
    t = sys.argv[1]
    if not t in ['A', 'B', 'D']:
        print("t must be A, B or D")
        exit(0)
    n = int(sys.argv[2])
    if not n in range(2,21):
        print("n must be in [2,20]")
        exit(0)
    k = int(sys.argv[3])
    if not k in range(2,11):
        print("k must be in [2,10]")
        exit(0)
    h = int(sys.argv[4])
    if not h in range(k):
        print("h must be in [0," + repr(k - 1) + "]")
        exit(0)
    print("*********************************************")
    print("* Work on", t+repr(n), "with k =", k, "and h =", h)
    print("*********************************************")
    print("-> write src/config_oar.hpp")
    file = open("src/config_oar.hpp", 'w')
    file.write("static const char T = '" + t + "';\n")
    file.write("static const Int N = " + repr(n) +";\n")
    file.write("static const Int k = " + repr(k) +";\n")
    file.write("static const Int h = " + repr(h) +";\n")
    file.close()
    print(" -> compile coxmodlen_multi")
    os.system('make clean')
    os.system('make bin/coxmodlen_multi')

    if t == 'A':
        pn = n + 1
    else:
        pn = n
    file = open("scripts/coxmodlen.arg", 'w')
    for a in range(pn):
        for b in range(pn):
            if b != a:
                for c in range(pn):
                    if c != a and c != b:
                        file.write(repr(a) + ' ' + repr(b) + ' ' + repr(c) + '\n')
    file.close()
    
