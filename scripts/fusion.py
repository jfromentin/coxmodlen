import sys

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print("Usage : python fusion.py t n k h ")
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

    output_dir = "/nfs/home/lmpa/jfromentin/git/coxmodlen/output"

    if t == 'A':
        pn = n + 1
    else:
        pn = n
        
    total = 0
    res = [0] * 1024
    max_size = 0
    for a in range(pn):
        for b in range(n):
            if b != a:
                for c in range(pn):
                    if c != a and c != b:
                        filename = output_dir + '/' + t +  repr(n) + "_for_" + repr(k) + "_" + repr(h) + "_with_" + repr(a) + "_" + repr(b) +"_" + repr(c)
                        print(filename)
                        file = open(filename, 'r')
                        lines = file.readlines()
                        if lines[0][0] != t:
                            print("Problem with type in", filename)
                            exit(0)
                        if int(lines[0][1:]) != n:
                            print("Problem with rank in", filename)
                            exit(0)
                        data = lines[1][:-1].split(' ')
                        if int(data[0]) != k:
                            print("Problem with modulus in", filename)
                            exit(0)
                        if int(data[1]) != h:
                            print("Problam with remainder in", filename)
                            exit(0)
                        data = lines[2][:-1].split(' ')
                        if int(data[0]) != a:
                            print("Problam with a in", filename)
                            exit(0)
                        if int(data[1]) != b:
                            print("Problam with b in", filename)
                            exit(0)
                        if int(data[2]) != c:
                            print("Problam with c in", filename)
                            exit(0)
                        size = int(lines[3])
                        max_size = max(max_size, size)
                        for i in range(size):
                            nb = int(lines[i + 5][:-1])
                            res[i] += nb
                            total += nb
                            file.close()
    file = open("/nfs/home/lmpa/jfromentin/git/coxmodlen/results/res_" + t + repr(n) + "_for_" + repr(k) + "_" + repr(h) + ".txt", 'w')
    file.write("Coxeter group: " + t + repr(n) + "\n")
    file.write("Modulus: " + repr(k) + "\n")
    file.write("Remainder: " + repr(h) + "\n")
    file.write("Total: " + repr(total) + "\n\n")
    file.write(repr(res[:max_size]) + "\n\n")
    for i in range(max_size):
        file.write(repr(res[i]) + "\n")
    file.close()
    
